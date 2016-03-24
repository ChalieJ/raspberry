#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MEM_DEV     "/dev/mem"

#define GPIO_BASE       0x3F200000
#define GPIO_PWM        0x3F20C000
#define CLK_BASE        0x3F101000

/* define for gpio alternate function */
#define GPFSEL0         (0x00 / 4)  // 0 ~ 9
#define GPFSEL1         (0x04 / 4)  // 10 ~ 19
#define GPFSEL2         (0x08 / 4)  // 20 ~ 29
#define GPFSEL3         (0x0C / 4)  // 30 ~ 39
#define GPFSEL4         (0x10 / 4)  // 40 ~ 49
#define GPFSEL5         (0x14 / 4)  // 50 ~ 54

/* define for gpio function select */
#define PIN0            0
#define PIN1            3
#define PIN2            6
#define PIN3            9
#define PIN4            12
#define PIN5            15
#define PIN6            18
#define PIN7            21
#define PIN8            24
#define PIN9            27

/* define for gpio input/output */
#define GPSET0          (0x1C / 4)
#define GPSET1          (0x20 / 4)
#define GPCLR0          (0x28 / 4)
#define GPCLR1          (0x2C / 4)

#define EN              16
#define RW              17
#define RS              18
#define D0              19
#define D1              20
#define D2              21
#define D3              22
#define D4              23
#define D5              24
#define D6              25
#define D7              26

/* LCD instruction */
#define LCD_CLR		0x01
#define	LCD_HOME	0x02
#define LCD_ENT		0x06
#define LCD_DSP		0x0F
#define	LCD_CUR		0x14
#define LCD_FUNC	0x38

void lcd_init(void);
void lcd_on(void);
void lcd_clr(void);
unsigned char lcd_busy_check();
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_close();

void msleep(unsigned int millis);
void usleep(unsigned int micros);

/* global */
volatile unsigned int *gpio;
int fd;

int main()
{
    lcd_init();

	lcd_data('A');
	lcd_data('A');
	lcd_data('A');
	lcd_data('A');
	lcd_data('A');
	lcd_data('A');
	lcd_data('A');

	while(1);

	lcd_close();

    return 0;
}

void lcd_close()
{
	munmap((void *)gpio, 4096);
	close(fd);
}

/*
 * Function : LCD initialize
 * Description
 * 1. GPIO mapping
 * 2. GPIO output setting (Function select)
 * 3. LCD initialize command send
 */
void lcd_init()
{
    //DB0~7 : gpio 19,20,21,22,23,24,25,26
    //RS    : gpio 18
    //RW    : gpio 17
    //E     : gpio 16
    fd = open(MEM_DEV, O_RDWR | O_SYNC);
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

    gpio = (volatile unsigned int *)gpio_base_map;
	
    /* function select for gpio output */
    gpio[GPFSEL1] = (1 << PIN6) | (1 << PIN7) | (1 << PIN8) | (1 << PIN9);
    gpio[GPFSEL2] = (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) |
                    (1 << PIN4) | (1 << PIN5) | (1 << PIN6);

    lcd_on();
    lcd_clr();

#if 0 //GPIO output test : OK
    gpio[GPFSEL1] = (1 << PIN6) | (1 << PIN7) | (1 << PIN8) | (1 << PIN9);
    gpio[GPFSEL2] = (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) |
                    (1 << PIN4) | (1 << PIN5) | (1 << PIN6);
	while(1)
	{
    	gpio[GPSET0] |= (1 << EN) | (1 << RW) | (1 << RS) | (0xFF << D0);
		msleep(1000);
    	gpio[GPCLR0] |= (1 << EN) | (1 << RW) | (1 << RS) | (0xFF << D0);
		msleep(1000);
	}
#endif
}

void lcd_on()
{
	printf("lcd_on() start\n");
#if 0 /* wowcat src */
	lcd_cmd(LCD_FUNC);
	lcd_cmd(LCD_DSP);
	lcd_cmd(LCD_ENT);
	lcd_cmd(LCD_CUR);
	lcd_cmd(LCD_CLR);
	lcd_cmd(LCD_HOME);
	msleep(2);
#else
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
	msleep(2);
#endif
}

void lcd_clr()
{
	printf("lcd_clr() start\n");
    lcd_cmd(LCD_CLR);
    msleep(1);
    lcd_cmd(LCD_HOME);
    msleep(1);
}

unsigned char lcd_busy_check()
{
	usleep(200);
	usleep(200);
	usleep(200);
	usleep(200);
	usleep(200);
	usleep(200);
	usleep(200);

	return 0;
}

void lcd_cmd(unsigned char data)
{
	printf("lcd_cmd() start %02X\n", data);
	while(lcd_busy_check()) {};

    gpio[GPCLR0] |= (1 << EN) | (1 << RW) | (1 << RS);
	usleep(2);
    gpio[GPSET0] |= (data << D0);
    usleep(50);
    gpio[GPSET0] |= (1 << EN);
    usleep(20);
    gpio[GPCLR0] |= (1 << EN);
    usleep(50);
}

void lcd_data(unsigned char data)
{
    //check delay
	printf("lcd_data() start %02X\n", data);
	while(lcd_busy_check()) {};
    gpio[GPCLR0] |= (1 << EN) | (1 << RW);
    gpio[GPSET0] |= (1 << RS);
	usleep(2);
    gpio[GPSET0] |= (data << D0);
    usleep(50);
    gpio[GPSET0] |= (1 << EN);
    usleep(20);
    gpio[GPCLR0] |= (1 << EN);
    usleep(50);
}

void msleep(unsigned int millis)
{
    struct timespec sleeper;

    sleeper.tv_sec = (time_t)(millis / 1000);
    sleeper.tv_nsec = (time_t)(millis % 1000) * 1000000;
    nanosleep(&sleeper, NULL);
}

void usleep(unsigned int micros)
{
    struct timespec sleeper;

    sleeper.tv_sec = (time_t)(micros / 1000);
    sleeper.tv_nsec = (time_t)(micros % 1000) * 1000;
    nanosleep(&sleeper, NULL);
}

