#include <stdio.h>

#define MEM_DEV     "/dev/mem"

#define GPIO_BASE       0x3F200000
#define GPIO_PWM        0x3F20C000
#define CLK_BASE        0x3F101000

#define GPFSEL0         (0x00 / 4)  // 0 ~ 9
#define GPFSEL1         (0x04 / 4)  // 10 ~ 19
#define GPFSEL2         (0x08 / 4)  // 20 ~ 29
#define GPFSEL3         (0x0C / 4)  // 30 ~ 39
#define GPFSEL4         (0x10 / 4)  // 40 ~ 49
#define GPFSEL5         (0x14 / 4)  // 50 ~ 54


#define GPSET0          (0x1C / 4)
#define GPSET1          (0x20 / 4)
#define GPCLR0          (0x28 / 4)
#define GPCLR1          (0x2C / 4)

#define E           16
#define RW          17
#define RS          18
#define D0          19
#define D1          20
#define D2          21
#define D3          22
#define D4          23
#define D5          24
#define D6          25
#define D7          26

void lcd_init(void);
void lcd_on(void);
void lcd_clr(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);

int main()
{
    lcd_init();

    return 0;
}

void lcd_init()
{
    //DB0~7 : gpio 19,20,21,22,23,24,25,26
    //RS    : gpio 18
    //RW    : gpio 17
    //E     : gpio 16
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

    volatile unsigned int *gpio = (volatile unsigned int *)gpio_memory_map;
    /* function select for gpio output */
    gpio[GPFSEL1/4] |= (1 << E) | (1 << RW) | (1 << RS) | (1 << D0) |
        (1 << D1) | (1 << D2) | (1 << D3) | (1 << D4) |
        (1 << D5) | (1 << D6) | (1 << D7);

    lcd_on();
    lcd_clr();

}

void lcd_on()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void lcd_clr()
{
    lcd_cmd(1);
    msleep(1);
    lcd_cmd(2);
    msleep(1);
}

void lcd_cmd(unsigned char data)
{
    //check delay
    gpio[GPCLR0] |= (1 << E) | (1 << RS);
    usleep(1);
    gpio[GPSET0] |= (data << D0);
    usleep(50);
    gpio[GPSET0] |= (data << E);
    usleep(20);
    gpio[GPCLR0] |= (data << E);
    usleep(50);
}

void lcd_data(unsigned char data)
{
    //check delay
    gpio[GPCLR0] |= (1 << E);
    gpio[GPSET0] |= (1 << RS);
    usleep(1);
    gpio[GPSET0] |= (data << D0);
    usleep(50);
    gpio[GPSET0] |= (data << E);
    usleep(20);
    gpio[GPCLR0] |= (data << E);
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

