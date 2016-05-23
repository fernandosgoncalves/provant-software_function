/**
  ******************************************************************************
  * @file    app/remote-controlled-flight/pv_module_gps.c
  * @author  Patrick Jose Pereira
  * @version V1.0.0
  * @date    27-August-2014
  * @brief   Implementação do módulo de leitura de dados do GPS.
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "pv_module_gps.h"

/** @addtogroup ProVANT_app
  * @{
  */

/** @addtogroup app_gps
  * \brief Módulo responsavel por tratar os dados do GPS.
  *
  * Definição do módulo de tratamento dos dados de GPS.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MODULE_PERIOD	   100//ms

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
portTickType lastWakeTime;
pv_msg_gps oGpsData;
pv_msg_controlOutput oControlOutputData; 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions definitions --------------------------------------------*/

/** \brief Inicializacao do módulo de GPS.
  *
  * Instancia as Queues de comunicação inter-thread.
  * @param  None
  * @retval None
  */
void module_gps_init() 
{
  c_io_gps_init();

  pv_interface_gps.oGpsData          = xQueueCreate(1, sizeof(pv_msg_gps));
}

/** \brief Função principal do módulo de GPS.
  * @param  None
  * @retval None
  *
  */
void module_gps_run()
{
  float xyz[3];
  oGpsData.heartBeat=0;
  while(1)
  {
    lastWakeTime = xTaskGetTickCount();
    c_io_gps_read(xyz);
    oGpsData.heartBeat++;
    oGpsData.gpsOutput.lat=xyz[0]+1;
    oGpsData.gpsOutput.lon=xyz[1]+1;

    if(pv_interface_gps.oGpsData != 0)
      xQueueOverwrite(pv_interface_gps.oGpsData, &oGpsData);

    vTaskDelayUntil( &lastWakeTime, (MODULE_PERIOD / portTICK_RATE_MS));
  }
}
/* IRQ handlers ------------------------------------------------------------- */

/**
  * @}
  */

/**
  * @}
  */