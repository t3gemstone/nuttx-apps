#include <stdint.h>

#define GPIO_MAX_PORT                   (8U)
#define GPIO_MAX_PINS_PER_PORT          (8U)
#define GPIO_PINS_PER_REG_SHIFT         (5U)
#define GPIO_PINS_PER_BANK_SHIFT        (4U)

#define GPIO_GET_PIN_OFFSET(pinNum)     (((uint32_t)pinNum) % (GPIO_MAX_PORT * GPIO_MAX_PINS_PER_PORT))

#define GPIO_GET_PORT_NUM(pinNum)       ((GPIO_GET_PIN_OFFSET(pinNum)) / GPIO_MAX_PINS_PER_PORT)

#define GPIO_GET_PIN_INDEX(pinNum)      ((GPIO_GET_PIN_OFFSET(pinNum)) % GPIO_MAX_PINS_PER_PORT)

#define CSL_GPIO_GIODIR(n)                            (0x34U + ((n) * 0x20U))
#define CSL_GPIO_GIODIN(n)                            (0x38U + ((n) * 0x20U))
#define CSL_GPIO_GIODOUT(n)                           (0x3CU + ((n) * 0x20U))
#define CSL_GPIO_GIOSET(n)                            (0x40U + ((n) * 0x20U))
#define CSL_GPIO_GIOCLR(n)                            (0x44U + ((n) * 0x20U))
#define CSL_GPIO_GIOPDR(n)                            (0x48U + ((n) * 0x20U))
#define CSL_GPIO_GIOPULDIS(n)                         (0x4CU + ((n) * 0x20U))
#define CSL_GPIO_GIOPSL(n)                            (0x50U + ((n) * 0x20U))

#define CSL_REG32_WR(p, v)      (CSL_REG32_WR_RAW((volatile uint32_t *)(p), (uint32_t)(v)))
#define CSL_REG32_RD(p)         (CSL_REG32_RD_RAW((volatile uint32_t *) (p)))

#define MCU_GPIO0_BASE          0x4201000UL
#define MCU_GPIO0_SIZE          0x100UL

#define MAIN_GPIO0_BASE         0x600000UL
#define MAIN_GPIO0_SIZE         0x100UL

#define MAIN_GPIO1_BASE         0x601000UL
#define MAIN_GPIO1_SIZE         0x100UL

#define GPIO_GET_REG_INDEX(pinNum)      (((uint32_t) pinNum) >> GPIO_PINS_PER_REG_SHIFT)
#define GPIO_GET_BIT_POS(pinNum)        (pinNum - ((GPIO_GET_REG_INDEX(pinNum)) << GPIO_PINS_PER_REG_SHIFT))
#define GPIO_GET_BIT_MASK(pinNum)       (((uint32_t) 1U) << GPIO_GET_BIT_POS(pinNum))

#define GPIO_DIRECTION_OUTPUT           (0U)


#define CHIP_MPCORE_VBASE	 (0x0001800000)


#define CSL_FINSR(reg, msb, lsb, val)                                       \
    ((reg) = ((reg) & (~(((((uint32_t)1U) << ((msb) - (lsb) + ((uint32_t)1U))) - ((uint32_t)1U)) << (lsb))))         \
    | CSL_FMKR((msb), (lsb), (val)))
#define CSL_FMKR(msb, lsb, val)                                             \
    (((val) & ((((uint32_t)1U) << ((msb) - (lsb) + ((uint32_t)1U))) - ((uint32_t)1U))) << (lsb))

typedef struct {
    volatile uint32_t DIR;
    volatile uint32_t OUT_DATA;
    volatile uint32_t SET_DATA;
    volatile uint32_t CLR_DATA;
    volatile uint32_t IN_DATA;
    volatile uint32_t SET_RIS_TRIG;
    volatile uint32_t CLR_RIS_TRIG;
    volatile uint32_t SET_FAL_TRIG;
    volatile uint32_t CLR_FAL_TRIG;
    volatile uint32_t INTSTAT;
} CSL_GpioBank_registersRegs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    volatile uint32_t PID;
    volatile uint32_t PCR;
    volatile uint32_t BINTEN;
    volatile uint8_t  RSVD0[4];
    CSL_GpioBank_registersRegs  BANK_REGISTERS[9];
} CSL_GpioRegs;

static inline void CSL_REG32_WR_RAW(volatile uint32_t * const p, uint32_t v);
static inline void CSL_REG32_WR_RAW(volatile uint32_t * const p, uint32_t v)
{
    *p = v;
    return;
}

static inline uint32_t CSL_REG32_RD_RAW(volatile const uint32_t * const p);
static inline uint32_t CSL_REG32_RD_RAW(volatile const uint32_t * const p)
{
    return (*p);
}

static inline void GPIO_pinWriteHigh(uint32_t baseAddr, uint32_t pinNum)
{
    uint32_t                regIndex, regVal;
    volatile CSL_GpioRegs*  hGpio = (volatile CSL_GpioRegs*)((uintptr_t) baseAddr);

    regIndex = GPIO_GET_REG_INDEX(pinNum);
    regVal = GPIO_GET_BIT_MASK(pinNum);
    CSL_REG32_WR(&hGpio->BANK_REGISTERS[regIndex].SET_DATA, regVal);

    return;
}

static inline void GPIO_pinWriteLow(uint32_t baseAddr, uint32_t pinNum)
{
    uint32_t                regIndex, regVal;
    volatile CSL_GpioRegs*  hGpio = (volatile CSL_GpioRegs*)((uintptr_t) baseAddr);

    regIndex = GPIO_GET_REG_INDEX(pinNum);
    regVal = GPIO_GET_BIT_MASK(pinNum);
    CSL_REG32_WR(&hGpio->BANK_REGISTERS[regIndex].CLR_DATA, regVal);

    return;
}

void GPIO_pinWriteHigh(uint32_t baseAddr, uint32_t pinNum);
void GPIO_pinWriteLow(uint32_t baseAddr, uint32_t pinNum);
void GPIO_setDirMode(uint32_t baseAddr, uint32_t pinNum, uint32_t pinDir);

void gpio_config(void);
void led_blink(void);
