#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define GPIO_BASE		0x3F200000
#define GPIO_PWM		0x3F20C000
#define CLK_BASE		0x3F101000

#define GPFSEL0			(0x00 / 4)	// 0 ~ 9
#define GPFSEL1			(0x04 / 4)	// 10 ~ 19
#define GPFSEL2			(0x08 / 4)	// 20 ~ 29
#define GPFSEL3			(0x0C / 4)	// 30 ~ 39
#define GPFSEL4			(0x10 / 4)	// 40 ~ 49
#define GPFSEL5			(0x14 / 4)	// 50 ~ 54

#define GPINPUT			0
#define GPOUTPUT		1
#define GPFUNC0			4
#define GPFUNC1			5
#define GPFUNC2			6
#define GPFUNC3			7
#define GPFUNC4			3
#define GPFUNC5			2

#define PIN0			0
#define PIN1			3
#define PIN2			6
#define PIN3			9
#define PIN4			12
#define PIN5			15
#define PIN6			18
#define PIN7			21	
#define PIN8			24
#define PIN9			27

#define GPSET0			(0x1C / 4)
#define GPSET1			(0x20 / 4)
#define GPCLR0			(0x28 / 4)
#define GPCLR1			(0x2C / 4)

#define PWMCTL			(0x00 / 4)
#define PWMSTA			(0x04 / 4)
#define PWMDMAC			(0x08 / 4)
#define PWMRNG1			(0x10 / 4)
#define PWMDAT1			(0x14 / 4)

#define CLKCTL			(0xA0 / 4)
#define CLKDIV			(0xA4 / 4)

#define MEM_DEV		"/dev/mem"

void msleep(unsigned int millis);

int main()
{
	/* open memory device */
	int fd = open(MEM_DEV, O_RDWR | O_SYNC);
	if(fd < 0) {
		printf("error : cant open [%s]\n", MEM_DEV);
		exit(-1);
	}

	/* get gpio base memory */
	char *gpio_base_map = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, 
										MAP_SHARED, fd, GPIO_BASE);

	if(gpio_base_map == MAP_FAILED) {
		printf("error : mmap failed\n");
		exit(-1);
	}

	/* get gpio pwm memory */
	char *gpio_pwm_map = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, 
										MAP_SHARED, fd, GPIO_PWM);

	if(gpio_pwm_map == MAP_FAILED) {
		printf("error : mmap failed\n");
		exit(-1);
	}

	/* get clock base memory */
	char *clk_base_map = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, 
										MAP_SHARED, fd, CLK_BASE);

	if(clk_base_map == MAP_FAILED) {
		printf("error : mmap failed\n");
		exit(-1);
	}

	/* set the 32bit */
	volatile unsigned int *gpio = (volatile unsigned int *)gpio_base_map;
	volatile unsigned int *pwm = (volatile unsigned int *)gpio_pwm_map;
	volatile unsigned int *clk = (volatile unsigned int *)clk_base_map;

	//set gpio 18, alt function 5 (pwm0)
	gpio[GPFSEL1] = GPFUNC5 << PIN8;

	//set gpio pwm clock
	clk[CLKCTL] = (0x5A << 24) | 0x1;
	msleep(100);
	while(1)
	{
		if(clk[CLKCTL] & 0x80 != 0)
			break;
		msleep(1);
	}
	clk[CLKDIV] = (0x5A << 24) | (16 << 12);
	clk[CLKCTL] = (0x5A << 24) | 0x11;

	//set mode
	unsigned int temp_reg = 0;
	temp_reg = pwm[PWMCTL];
	temp_reg = temp_reg | 0x0080;
	temp_reg = temp_reg | 0x0001;
	pwm[PWMCTL] = temp_reg;

	//set range
	pwm[PWMRNG1] = 1024;

	int direction = 1;
	int data = 1;
	int cnt = 0;

	while(1)
	{
		if(data == 1) {
			direction = 1;
			++cnt;
		} else if(data == 1023) {
			direction = -1;
			++cnt;
		}

		if(cnt == 100)
			break;

		data = data + direction;

		pwm[PWMDAT1] = data;
		msleep(1);
	}

	munmap(gpio_base_map, 4096);
	munmap(gpio_pwm_map, 4096);
	close(fd);

	return 0;
}

void msleep(unsigned int millis)
{
	struct timespec sleeper;

	sleeper.tv_sec = (time_t)(millis / 1000);
	sleeper.tv_nsec = (time_t)(millis % 1000) * 1000000;
	nanosleep(&sleeper, NULL);
}
