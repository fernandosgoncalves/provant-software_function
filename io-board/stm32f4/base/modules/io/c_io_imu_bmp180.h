 /*
  * @file    modules/io/c_io_imu.h
  * @author  Martin Vincent Bloedorn
  * @version V1.0.0
  * @date    11-February-2014
  * @brief   Funções para IMUs (incialmente baseadas no CIs ITG3205 e ADXL345).
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef C_IO_IMU_BMP180_H
#define C_IO_IMU_BMP180_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

#include "c_common_i2c.h"
#include "c_common_utils.h"
#include "c_common_gpio.h"

#define ARM_MATH_CM4
#include "arm_math.h"
#include <math.h>

/* FreeRTOS kernel includes */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
//BMP180 register map. For details see BMP180 datasheet
#define BMP180_ADDR       0x77
#define BMP180_OUT_XLSB   0xF8
#define BMP180_OUT_LSB    0xF7
#define BMP180_OUT_MSB    0xF6
#define BMP180_CTRL_MEAS  0xF4
#define BMP180_SOFT_RESET 0xE0
#define BMP180_ID         0xD0
/*Oversampling Setting*/
#define BMP180_TEMPERATURE  0x2E
#define BMP180_PRESS_OSS_0  0x34
#define BMP180_PRESS_OSS_1  0x74
#define BMP180_PRESS_OSS_2  0xB4
#define BMP180_PRESS_OSS_3  0xF4
/*Time convertion*/
#define BMP180_TIME_TEMP    5
#define BMP180_TIME_OSS_0   5
#define BMP180_TIME_OSS_1   8
#define BMP180_TIME_OSS_2   14
#define BMP180_TIME_OSS_3   26
/*over*/
#define BMP180_OSS_0   0 //<- Less time
#define BMP180_OSS_1   1
#define BMP180_OSS_2   2
#define BMP180_OSS_3   3
//Define of Oversampling used in the configuration
#define OSS	      BMP180_OSS_0  					// Oversampling Setting
#define OSS_TIME  BMP180_TIME_OSS_0                 // Time delay
/* Exported functions ------------------------------------------------------- */
void  c_io_imu_bmp180_int(I2C_TypeDef* I2Cx);
void  c_io_imu_bmp180_Calibration();
float c_io_imu_bmp180_getTemperature();
float  c_io_imu_bmp180_getPressure();
float c_io_imu_bmp180_Altitude(float pressure);

#ifdef __cplusplus
}
#endif

#endif //C_IO_IMU_H
