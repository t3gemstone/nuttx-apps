#include <nuttx/config.h>
#include <unistd.h>
#include "blink.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * blink_main
 ****************************************************************************/

int main(int argc, FAR char *argv[])
{
  led_blink();
  return 0;
}

void led_blink(void)
{
    GPIO_setDirMode(MAIN_GPIO1_BASE, 52, GPIO_DIRECTION_OUTPUT); // Green LED
    GPIO_setDirMode(MAIN_GPIO1_BASE, 53, GPIO_DIRECTION_OUTPUT); // Red LED, active low

    while(1) {
        GPIO_pinWriteHigh(MAIN_GPIO1_BASE, 52);
        GPIO_pinWriteHigh(MAIN_GPIO1_BASE, 53);
        usleep(3);
        GPIO_pinWriteLow(MAIN_GPIO1_BASE, 52);
        GPIO_pinWriteLow(MAIN_GPIO1_BASE, 53);
        sleep(3);
    }
}

void GPIO_setDirMode(uint32_t baseAddr, uint32_t pinNum, uint32_t pinDir)
{
    uint32_t                regIndex, bitPos;
    volatile CSL_GpioRegs*  hGpio = (volatile CSL_GpioRegs*)((uintptr_t) baseAddr);

    regIndex = GPIO_GET_REG_INDEX(pinNum);
    bitPos = GPIO_GET_BIT_POS(pinNum);
    CSL_FINSR(hGpio->BANK_REGISTERS[regIndex].DIR, bitPos, bitPos, (((uint32_t) pinDir) & 0x01U));

    return;
}
