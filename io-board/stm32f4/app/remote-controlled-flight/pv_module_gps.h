/**
  ******************************************************************************
  * @file    app/remote-controlled-flight/pv_module_gps.h
  * @author  Patrick Jose Pereira
  * @version V1.0.0
  * @date    27-August-2014
  * @brief   Implementação do módulo de leitura de dados do GPS.
  ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PV_MODULE_GPS_H
#define PV_MODULE_GPS_H

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
 	
/* proVANT includes */
#include "c_io_novatel.h"

#include "pv_typedefs.h"

struct pv_interface_gps
{
  xQueueHandle oGpsData;  
} pv_interface_gps;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void module_gps_init();
void module_gps_run();

#ifdef __cplusplus
}
#endif

#endif