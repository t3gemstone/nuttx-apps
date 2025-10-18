/****************************************************************************
 * apps/blink/blink_main.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <unistd.h>
#include "blink.h"

/****************************************************************************
 * Public Functions
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
    sleep(1);
    GPIO_pinWriteLow(MAIN_GPIO1_BASE, 52);
    GPIO_pinWriteLow(MAIN_GPIO1_BASE, 53);
    sleep(1);
  }
}
