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


#define max 100 
#define chardriver_file "/dev/chardriver_null"

int main()
{
int fd; 
int choice=0,length=0;
char data_to_driver[max],data_from_driver[max];
fd=open(chardriver_file,O_RDWR);


printf("\nenter the choice:\n1.write\n2.read\nCTRL+c to stop\n=");
scanf("%d\n",&choice); /**remember to use \n with scanf to avoid error in fgets */
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

}

