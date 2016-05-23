/**
  * @file    modules/io/c_io_servos.h
  * @author  Richard ANdrade
  * @version V1.0.0
  * @date    3-Setembro-2015
  * @brief   Definição do módulo de administraçao de servos.
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PV_IO_SERVOS_H
#define PV_IO_SERVOS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

 /* FreeRTOS kernel includes */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

 /* kernel includes */
#include "c_common_gpio.h"
#include "c_common_i2c.h"
#include "c_common_uart.h"
#include "c_common_utils.h"

/*Servos includes*/
#include "c_io_rx24f.h"
#include "c_io_herkulex.h"

#include "pv_typedefs.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define SERVO_HERKULEX
//#define SERVO_RX24F
/* Exported functions ------------------------------------------------------- */
void c_io_servos_init();
pv_type_datapr_servos c_io_servos_read();
void c_io_servos_writePosition(float positionRight, float positionLeft);
void c_io_servos_writeTorque(float torqueRight, float torqueLeft);
pv_type_servoOutput c_io_servos_getInformation();
#ifdef __cplusplus
}
#endif

#endif //PV_IO_SERVOS_H
