#include<stdio.h>
#include<fcntl.h>
#define ADD 0x1
#define SUB 0x2
#define MUL 0x3
#define UNKNOWN 0x4

struct foo{
        int a;
        int b;
        int c;
};
int main()
{
	struct foo f;
	int fd;
	int a;
	char buff[15];
	fd = open("/dev/mydev_dynamic", O_RDWR);
	//if(fd != -1){
		//printf("\nsss  %d ",fd);
	//	return 0;
	//}
	write(fd, "Hello_Deepak",12);
	a = read(fd, buff, 20);
	if(a < 0){
		printf("reading error");
		return 0;
	}
	printf("%s",buff);
	//f.a = 15;
	//f.b = 10;
	//ioctl(fd, ADD, &f);
	//printf("\n Add : %d \n", f.c);
	//ioctl(fd, SUB, &f);
	//printf("\n Sub : %d \n", f.c);
	//ioctl(fd, MUL, &f);
	//printf("\n mul : %d \n", f.c);
	//ioctl(fd, UNKNOWN, &f);
	//printf("\n Unknown : %d \n", f.c);
	close(fd);
	return 0;
}
