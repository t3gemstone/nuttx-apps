

if(CONFIG_BLINK)
  nuttx_add_application(
    NAME
    ${CONFIG_BLINK_PROGNAME}
    SRCS
    blink_main.c
    STACKSIZE
    ${CONFIG_BLINK_STACKSIZE}
    PRIORITY
    ${CONFIG_BLINK_PRIORITY})
endif()
