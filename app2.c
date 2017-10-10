#include <stdio.h>
#include<fcntl.h>

int main()
{
	int fd;
	int a;
	char buff[15];
	fd = open("/dev/mydev_dynamic",O_RDWR);
	write(fd,"Krnl_Program",12);
	close(fd);
	return 0;

}

