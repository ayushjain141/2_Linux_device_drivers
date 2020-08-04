/**======================
 * include files
=======================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <linux/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



#define max 100 
#define chardriver_file "/dev/rpr0521_chardriver_null"

int main()
{
int fd; 
int choice=0,length=0;
char data_to_driver[max],data_from_driver[max];

char als_addr_buffer[1]={0x46};

uint16_t data[2];
int i=0,res=0;


fd=open(chardriver_file,O_RDWR);

printf("\n=============\n");

while (1)
{
write(fd, als_addr_buffer, 1);
char read_buffer[2];
read(fd, read_buffer,2);
res=(int)( (read_buffer[1]<<8)|(read_buffer[0])) ;  
printf("%d\n",res); 
}

/////
/*
printf("\nenter the choice:\n1.write\n2.read\nCTRL+c to stop\n=");
scanf("%d\n",&choice); //remember to use \n with scanf to avoid error in fgets 
sleep(1); 
printf("\nWrite=\n");
fgets(data_to_driver, max, stdin);
//gets(*data_to_driver);
length = strlen(data_to_driver);
data_to_driver[length-1] = '\0';
write(fd, data_to_driver, length);
read(fd, data_from_driver, max);
printf("\n%s\n",data_from_driver);	
close(fd);
*/
/////



}

