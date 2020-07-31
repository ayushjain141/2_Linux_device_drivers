
/**
 gpio_test.c  /// with threaded interrupt 
 * @author Derek Molloy
 * @date   19 April 2015
 * @brief  A kernel module for controlling a GPIO LED/button pair. The device mounts devices via
 * sysfs /sys/class/gpio/gpio115 and gpio49. Therefore, this test LKM circuit assumes that an LED
 * is attached to GPIO 49 which is on P9_23 and the button is attached to GPIO 115 on P9_27. There
 * is no requirement for a custom overlay, as the pins are in their default mux mode states.
 * @see http://www.derekmolloy.ie/
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>                 // Required for the GPIO functions
#include <linux/interrupt.h>            // Required for the IRQ code

#include <linux/kobject.h>    // Using kobjects for the sysfs bindings
#include <linux/kthread.h>    // Using kthreads for the flashing functionality
#include <linux/delay.h>      // Using this header for the msleep() function


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Derek Molloy");
MODULE_DESCRIPTION("A Button/LED test driver for the BBB");
MODULE_VERSION("0.1");

static unsigned int gpioLED = 49;       ///< hard coding the LED gpio for this example to P9_23 (GPIO49)
static unsigned int gpioButton = 115;   ///< hard coding the button gpio for this example to P9_27 (GPIO115)
static unsigned int irqNumber;          ///< Used to share the IRQ number within this file
static unsigned int numberPresses = 0;  ///< For information, store the number of button presses
static bool	    ledOn = 0;          ///< Is the LED on or off? Used to invert its state (off by default)
static bool 	    button_value = 0;	
static bool         button_flag  = 0;
static dev_t gpio_devt;
/// Function prototype for the custom IRQ handler function -- see below for the implementation
static irqreturn_t ebbgpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irqreturn_t ebbgpio_threaded_irq_function(int irq, void *dev_id);

/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point. In this example this
 *  function sets up the GPIOs and the IRQ
 *  @return returns 0 if successful
 */
static int __init ebbgpio_init(void){
   int result = 0;
   printk(KERN_INFO "GPIO_TEST: Initializing the GPIO_TEST LKM\n");
   // Is the GPIO a valid GPIO number (e.g., the BBB has 4x32 but not all available)
   if (!gpio_is_valid(gpioLED)){
      printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
      return -ENODEV;
   }
   // Going to set up the LED. It is a GPIO in output mode and will be on by default
   ledOn = 0; // true
   gpio_request(gpioLED, "sysfs");          // gpioLED is hardcoded to 49, request it
   gpio_direction_output(gpioLED, ledOn);   // Set the gpio to be in output mode and on
// gpio_set_value(gpioLED, ledOn);          // Not required as set by line above (here for reference)
   gpio_export(gpioLED, false);             // Causes gpio49 to appear in /sys/class/gpio
			                    // the bool argument prevents the direction from being changed
   gpio_request(gpioButton, "sysfs");       // Set up the gpioButton
   gpio_direction_input(gpioButton);        // Set the button GPIO to be an input
   gpio_set_debounce(gpioButton, 500);      // Debounce the button with a delay of 200ms
   gpio_export(gpioButton, false);          // Causes gpio115 to appear in /sys/class/gpio
			                    // the bool argument prevents the direction from being changed
   // Perform a quick test to see that the button is working as expected on LKM load
   printk(KERN_INFO "GPIO_TEST: The button state is currently: %d\n", gpio_get_value(gpioButton));

   // GPIO numbers and IRQ numbers are not the same! This function performs the mapping for us
   irqNumber = gpio_to_irq(gpioButton);
   printk(KERN_INFO "GPIO_TEST: The button is mapped to IRQ: %d\n", irqNumber);

/** This next call requests an interrupt line, this is a simple irq

   result = request_irq(irqNumber,             // The interrupt number requested
                        (irq_handler_t) ebbgpio_irq_handler, // The pointer to the handler function below
                        IRQF_TRIGGER_RISING,   // Interrupt on rising edge (button press, not release)
                        "ebb_gpio_handler",    // Used in /proc/interrupts to identify the owner
                        NULL);                 // The *dev_id for shared interrupt lines, NULL is okay
*/

//===========================================================================================

/** this is a threaded interrupt request */ 	
result = request_threaded_irq(irqNumber, (irq_handler_t)ebbgpio_irq_handler, ebbgpio_threaded_irq_function, IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW | IRQF_ONESHOT, "ebbgpio" ,NULL);  // this works becoz of IRQF_ONESHOT flag testing of flags necessary


//============================================================================================
   printk(KERN_INFO "GPIO_TEST: The interrupt request result is: %d\n", result);
   return result;

}

/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required. Used to release the
 *  GPIOs and display cleanup messages.
 */
static void __exit ebbgpio_exit(void){
   printk(KERN_INFO "GPIO_TEST: The button state is currently: %d\n", gpio_get_value(gpioButton));
   printk(KERN_INFO "GPIO_TEST: The button was pressed %d times\n", numberPresses);
   gpio_set_value(gpioLED, 0);              // Turn the LED off, makes it clear the device was unloaded
   gpio_unexport(gpioLED);                  // Unexport the LED GPIO
   free_irq(irqNumber, NULL);               // Free the IRQ number, no *dev_id required in this case
   gpio_unexport(gpioButton);               // Unexport the Button GPIO
   gpio_free(gpioLED);                      // Free the LED GPIO
   gpio_free(gpioButton);                   // Free the Button GPIO
   printk(KERN_INFO "GPIO_TEST: Goodbye from the LKM!\n");
}

/** @brief The GPIO IRQ Handler function
 *  This function is a custom interrupt handler that is attached to the GPIO above. The same interrupt
 *  handler cannot be invoked concurrently as the interrupt line is masked out until the function is complete.
 *  This function is static as it should not be invoked directly from outside of this file.
 *  @param irq    the IRQ number that is associated with the GPIO -- useful for logging.
 *  @param dev_id the *dev_id that is provided -- can be used to identify which device caused the interrupt
 *  Not used in this example as NULL is passed.
 *  @param regs   h/w specific register values -- only really ever used for debugging.
 *  return returns IRQ_HANDLED if successful -- should return IRQ_NONE otherwise.
 */

//========================================================================

static irqreturn_t ebbgpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs){
   ledOn = 0;                          // keep the led initially 0
   gpio_set_value(gpioLED, ledOn);     // Set the physical LED accordingly
   printk(KERN_INFO "GPIO_TEST: Interrupt! (button state is %d)\n", gpio_get_value(gpioButton));
   numberPresses++;                    // Global counter, will be outputted when the module is unloaded
   return  IRQ_WAKE_THREAD;      // wake the irq_thread   
}

/// NOTE : 
/** MANUAL TURNOFF of LED  
* for automatic shutoff remove the if and else condition
* for manual shutoff a (bool) button_flag is used and no other isr used separately for turnoff.
* since the below handler is bottom half and in process context and hence
* waiting loops are avoided for button press detection rather flags are used
* hence both turnoff and turnon performable using only single interrupt handler. 	
*/

static  irqreturn_t ebbgpio_threaded_irq_function(int irq, void *dev_id){

if(button_flag==0)
	{
	ledOn=0;
	gpio_set_value(gpioLED, ledOn);	//Set the physical LED accordingly
	msleep(2000); 			//reliable and non interruptble as per the - https://www.kernel.org/doc/html/latest/timers/timers-howto.html	
	ledOn=1;
	gpio_set_value(gpioLED, ledOn); // Set the physical LED accordingly
	printk(KERN_INFO "LED on\n");
	button_flag = 1;
	return IRQ_HANDLED;
	}

else if(button_flag == 1) 
       		{
		printk(KERN_INFO "LED off\n");
		msleep(1000);                   // this is just for debouncing for error by human button user (ex: long press)
		ledOn=0;
		gpio_set_value(gpioLED, ledOn); // Set the physical LED accordingly
		button_flag=0;
		return  IRQ_HANDLED;
		}
	
} 
//========================================================================

/// This next calls are  mandatory -- they identify the initialization function
/// and the cleanup function (as above).

module_init(ebbgpio_init);
module_exit(ebbgpio_exit);

