#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define GPIO_BASE	0x3F200000
#define GPFSEL1		0x04
#define GPSET0		0x1C
#define GPCLR0		0x28

#define MEM_DEV		"/dev/mem"

int main()
{
	int fd = open(MEM_DEV, O_RDWR | O_SYNC);
	if(fd < 0) {
		printf("error : cant open [%s]\n", MEM_DEV);
		exit(-1);
	}

	char *gpio_memory_map = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);

	if(gpio_memory_map == MAP_FAILED) {
		printf("error : mmap failed\n");
		exit(-1);
	}

	volatile unsigned int *gpio = (volatile unsigned int *)gpio_memory_map;
	gpio[GPFSEL1/4] |= (1 << 24) | (1 << 21);

	while(1)
	{
		printf("LED ON!\n");
		gpio[GPSET0/4] |= (1 << 18);
		gpio[GPCLR0/4] |= (1 << 17);
		sleep(1);

		printf("LED OFF!\n");
		gpio[GPCLR0/4] |= (1 << 18);
		gpio[GPSET0/4] |= (1 << 17);
		sleep(1);
	}
	
	munmap(gpio_memory_map, 4096);
	close(fd);

	return 0;
}


