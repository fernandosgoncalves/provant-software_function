/**
  ******************************************************************************
  * @file    modules/io/c_io_novatel.h
  * @author  Patrick Jose Pereira
  * @version V1.0.0
  * @date    22-julho-2015
  * @brief   Implementação da leitura do GPS EOMSTAR.
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef C_IO_NOVATEL_H
#define C_IO_NOVATEL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

 /* kernel includes */
#include "c_common_gpio.h"
#include "c_common_i2c.h"
#include "c_common_uart.h"
#include "c_common_utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Definitions----------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define OEMSTAR/* FreeRTOS kernel includes */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported variables---------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void c_io_gps_init();
void c_io_gps_read(float* xyz);

#ifdef __cplusplus
}
#endif

#endif //C_IO_NOVATEL_H

