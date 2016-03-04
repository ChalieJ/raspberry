#ifndef __RASPBERRY_H__
#define __RASPBERRY_H__

#define PERI_BASE       0x3F000000
#define CLK_BASE        (PERI_BASE + 0x101000)
#define GPIO_BASE       (PERI_BASE + 0x200000)
#define GPIO_PWM        (PERI_BASE + 0x20C000)

////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// GPIO REGISTER DEFINE ///////
////////////////////////////////////////////////////////////////////////////////////

typedef struct {
    unsigned int RESERVED   :2;
    unsigned int FSEL10     :3;
    unsigned int FSEL9      :3;
    unsigned int FSEL8      :3;
    unsigned int FSEL7      :3;
    unsigned int FSEL6      :3;
    unsigned int FSEL5      :3;
    unsigned int FSEL4      :3;
    unsigned int FSEL3      :3;
    unsigned int FSEL2      :3;
    unsigned int FSEL1      :3;
} GPIO_FSEL0_IDX_TYPE;
    
typedef union {
    unsigned int            nREG;
    GPIO_FSEL0_IDX_TYPE     bREG;
} GPIO_FSEL0_TYPE;

typedef struct {
    unsigned int RESERVED   :2;
    unsigned int FSEL20     :3;
    unsigned int FSEL19     :3;
    unsigned int FSEL18     :3;
    unsigned int FSEL17     :3;
    unsigned int FSEL16     :3;
    unsigned int FSEL15     :3;
    unsigned int FSEL14     :3;
    unsigned int FSEL13     :3;
    unsigned int FSEL12     :3;
    unsigned int FSEL11     :3;
} GPIO_FSEL1_IDX_TYPE;
    
typedef union {
    unsigned int            nREG;
    GPIO_FSEL1_IDX_TYPE     bREG;
} GPIO_FSEL1_TYPE;

typedef struct {
    unsigned int RESERVED   :2;
    unsigned int FSEL30     :3;
    unsigned int FSEL29     :3;
    unsigned int FSEL28     :3;
    unsigned int FSEL27     :3;
    unsigned int FSEL26     :3;
    unsigned int FSEL25     :3;
    unsigned int FSEL24     :3;
    unsigned int FSEL23     :3;
    unsigned int FSEL22     :3;
    unsigned int FSEL21     :3;
} GPIO_FSEL2_IDX_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_FSEL2_IDX_TYPE     bREG;
} GPIO_FSEL2_TYPE;

typedef struct {
    unsigned int RESERVED   :2;
    unsigned int FSEL40     :3;
    unsigned int FSEL39     :3;
    unsigned int FSEL38     :3;
    unsigned int FSEL37     :3;
    unsigned int FSEL36     :3;
    unsigned int FSEL35     :3;
    unsigned int FSEL34     :3;
    unsigned int FSEL33     :3;
    unsigned int FSEL32     :3;
    unsigned int FSEL31     :3;
} GPIO_FSEL3_IDX_TYPE;
   
typedef union {
    unsigned int            nREG;
    GPIO_FSEL3_IDX_TYPE     bREG;
} GPIO_FSEL3_TYPE;

typedef struct {
    unsigned int RESERVED   :2;
    unsigned int FSEL50     :3;
    unsigned int FSEL49     :3;
    unsigned int FSEL48     :3;
    unsigned int FSEL47     :3;
    unsigned int FSEL46     :3;
    unsigned int FSEL45     :3;
    unsigned int FSEL44     :3;
    unsigned int FSEL43     :3;
    unsigned int FSEL42     :3;
    unsigned int FSEL41     :3;
} GPIO_FSEL4_IDX_TYPE;
   
typedef union {
    unsigned int            nREG;
    GPIO_FSEL4_IDX_TYPE     bREG;
} GPIO_FSEL4_TYPE;

typedef struct {
    unsigned int RESERVED   :20;
    unsigned int FSEL54     :3;
    unsigned int FSEL53     :3;
    unsigned int FSEL52     :3;
    unsigned int FSEL51     :3;
} GPIO_FSEL5_IDX_TYPE;
   
typedef union {
    unsigned int            nREG;
    GPIO_FSEL5_IDX_TYPE     bREG;
} GPIO_FSEL5_TYPE;

/* PIN0 range : 1 ~ 32 */
typedef struct {
    unsigned int PIN1       :1;
    unsigned int PIN2       :1;
    unsigned int PIN3       :1;
    unsigned int PIN4       :1;
    unsigned int PIN5       :1;
    unsigned int PIN6       :1;
    unsigned int PIN7       :1;
    unsigned int PIN8       :1;
    unsigned int PIN9       :1;
    unsigned int PIN10      :1;
    unsigned int PIN11      :1;
    unsigned int PIN12      :1;
    unsigned int PIN13      :1;
    unsigned int PIN14      :1;
    unsigned int PIN15      :1;
    unsigned int PIN16      :1;
    unsigned int PIN17      :1;
    unsigned int PIN18      :1;
    unsigned int PIN19      :1;
    unsigned int PIN20      :1;
    unsigned int PIN21      :1;
    unsigned int PIN22      :1;
    unsigned int PIN23      :1;
    unsigned int PIN24      :1;
    unsigned int PIN25      :1;
    unsigned int PIN26      :1;
    unsigned int PIN27      :1;
    unsigned int PIN28      :1;
    unsigned int PIN29      :1;
    unsigned int PIN30      :1;
    unsigned int PIN31      :1;
    unsigned int PIN32      :1;
} GPIO_PIN0_IDX_TYPE;

/* PIN1 range : 33 ~ 54 */
typedef struct {
    unsigned int PIN33      :1;
    unsigned int PIN34      :1;
    unsigned int PIN35      :1;
    unsigned int PIN36      :1;
    unsigned int PIN37      :1;
    unsigned int PIN38      :1;
    unsigned int PIN39      :1;
    unsigned int PIN40      :1;
    unsigned int PIN41      :1;
    unsigned int PIN42      :1;
    unsigned int PIN43      :1;
    unsigned int PIN44      :1;
    unsigned int PIN45      :1;
    unsigned int PIN46      :1;
    unsigned int PIN47      :1;
    unsigned int PIN48      :1;
    unsigned int PIN49      :1;
    unsigned int PIN50      :1;
    unsigned int PIN51      :1;
    unsigned int PIN52      :1;
    unsigned int PIN53      :1;
    unsigned int PIN54      :1;
    unsigned int RESERVED   :10;
} GPIO_PIN1_IDX_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN0_IDX_TYPE      bREG;
} GPIO_SET0_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN1_IDX_TYPE      bREG;
} GPIO_SET1_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN0_IDX_TYPE      bREG;
} GPIO_CLR0_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN1_IDX_TYPE      bREG;
} GPIO_CLR1_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN0_IDX_TYPE      bREG;
} GPIO_PIN_LEVEL0_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN1_IDX_TYPE      bREG;
} GPIO_PIN_LEVEL1_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN0_IDX_TYPE      bREG;
} GPIO_EVENT0_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN1_IDX_TYPE      bREG;
} GPIO_EVENT1_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN0_IDX_TYPE      bREG;
} GPIO_RISING_EDGE0_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN1_IDX_TYPE      bREG;
} GPIO_RISING_EDGE1_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN0_IDX_TYPE      bREG;
} GPIO_FALLING_EDGE0_TYPE;

typedef union {
    unsigned int            nREG;
    GPIO_PIN1_IDX_TYPE      bREG;
} GPIO_FALLING_EDGE1_TYPE;

typedef struct {
    volatile GPIO_FSEL0_TYPE            GpioFsel0;          /* 0x0000   GPIO Function Select0   reset : 0x00000000 */
    volatile GPIO_FSEL1_TYPE            GpioFsel1;          /* 0x0004   GPIO Function Select1   reset : 0x00000000 */
    volatile GPIO_FSEL2_TYPE            GpioFsel2;          /* 0x0008   GPIO Function Select2   reset : 0x00000000 */
    volatile GPIO_FSEL3_TYPE            GpioFsel3;          /* 0x000C   GPIO Function Select3   reset : 0x00000000 */
    volatile GPIO_FSEL4_TYPE            GpioFsel4;          /* 0x0010   GPIO Function Select4   reset : 0x00000000 */
    volatile GPIO_FSEL5_TYPE            GpioFsel5;          /* 0x0014   GPIO Function Select5   reset : 0x00000000 */
    unsigned int Reserved0;
    volatile GPIO_SET0_TYPE             GpioSet0;           /* 0x001C   GPIO Pin Output Set0    reset : 0x00000000 */     
    volatile GPIO_SET1_TYPE             GpioSet1;           /* 0x0020   GPIO Pin Output Set1    reset : 0x00000000 */
    unsigned int Reserved1;
    volatile GPIO_CLR0_TYPE             GpioClear0;         /* 0x0028   GPIO Pin Output Clear0  reset : 0x00000000 */
    volatile GPIO_CLR1_TYPE             GpioClear1;         /* 0x002C   GPIO Pin Output Clear1  reset : 0x00000000 */
    unsigned int Reserved2;
    volatile GPIO_PIN_LEVEL0_TYPE       GpioPinLevel0;      /* 0x0034   GPIO Pin Level0         reset : 0x00000000 */
    volatile GPIO_PIN_LEVEL1_TYPE       GpioPinLevel1;      /* 0x0038   GPIO Pin Level1         reset : 0x00000000 */
    unsigned int Reserved3;
    volatile GPIO_EVENT0_TYPE           GpioEvent0;         /* 0x0040 */
    volatile GPIO_EVENT1_TYPE           GpioEvent1;         /* 0x0044 */
    unsigned int Reserved4;
    volatile GPIO_RISING_EDGE0_TYPE     GpioRisingEdge0;    /* 0x004C */
    volatile GPIO_RISING_EDGE1_TYPE     GpioRisingEdge1;    /* 0x0050 */
    unsigned int Reserved5;
    volatile GPIO_FALLING_EDGE0_TYPE    GpioFallingEdge0;   /* 0x0058 */
    volatile GPIO_FALLING_EDGE1_TYPE    GpioFallingEdge1;   /* 0x005C */
    unsigned int Reserved6;
    /* 0x0064 */
    /* 0x0068 */
    unsigned int Reserved7;
    /* 0x0070 */
    /* 0x0074 */
    unsigned int Reserved8;
    /* 0x007C */
    /* 0x0080 */
    unsigned int Reserved9;
    /* 0x0088 GPIO Pin Async Falling Edge Detect 0 */
    /* 0x008C GPIO Pin Async Falling Edge Detect 1 */
    unsigned int Reserved10;
    /* 0x0094 GPIO Pin Pull-up/Pull-down Enable */
    /* 0x0098 GPIO Pin Pull-up/Pull-down Enable Clock 0 */
    /* 0x009C GPIO Pin Pull-up/Pull-down Enable Clock 1 */
} GPIO, *PGPIO;

#endif //__RASBERRY_H__