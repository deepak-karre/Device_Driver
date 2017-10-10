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
	read(fd,buff,20);
	write(fd, "HELLO_WORLD",12);
	a = read(fd, buff, 20);
	if(a < 0){
		printf("reading error");
		return 0;
	}
	printf("%s",buff);
	close(fd);
	return 0;
}
