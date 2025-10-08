#include <nuttx/config.h>
#include <unistd.h>
#include "blink.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * blink_main
 ****************************************************************************/

void led_blink(void)
{
    GPIO_setDirMode(MAIN_GPIO1_BASE, 52, GPIO_DIRECTION_OUTPUT); // Green LED
    GPIO_setDirMode(MAIN_GPIO1_BASE, 53, GPIO_DIRECTION_OUTPUT); // Red LED, active low

    while(1) {
        GPIO_pinWriteHigh(MAIN_GPIO1_BASE, 52);
        GPIO_pinWriteHigh(MAIN_GPIO1_BASE, 53);
        sleep(3);
        GPIO_pinWriteLow(MAIN_GPIO1_BASE, 52);
        GPIO_pinWriteLow(MAIN_GPIO1_BASE, 53);
        sleep(3);
    }
}

int main(int argc, FAR char *argv[])
{
  led_blink();
  return 0;
}
