/**
  ******************************************************************************
  * @file    modules/io/c_io_novatel.c
  * @author  Patrick Jose Pereira
  * @version V1.0.0
  * @date    22-julho-2015
  * @brief   Implementação da leitura do GPS EOMSTAR.
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "c_io_novatel.h"

/** @addtogroup Module_IO
  * @{
  */

/** @addtogroup Module_IO_Component_NOVATEL
  * \brief Componente para a leitura do GPS OEMSTAR da novatel.
  *
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#define GPS_BAUDRATE  9600
#define GPS_USART     USART3

float lattitude=0.0f;
float longitude=0.0f;
float last_lattitude=0.0f;
float last_longitude=0.0f;
float heigh=0.0f;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions definitions --------------------------------------------*/

/**
  * @brief  Initializes the novatel module according to the specified
  *         parameters in the define area .
  * @retval None
  */
void c_io_gps_init()
{
  if(GPS_USART==USART3)
    c_common_usart3_init(GPS_BAUDRATE); //change this command if GPS_USART change
  c_common_usart_flush(GPS_USART);
  while(!c_common_usart_available(GPS_USART))
  {
    //c_common_utils_delayms(15000);
    c_common_utils_delayms(2000);
    c_common_usart_puts(GPS_USART,"log com1 bestposa");
  };
}

/**
  * @brief  return the distance between the sonar and floor
  * @retval the distance in centimeters
  */

void  c_io_gps_read(float* xyz)
{
  char dist[15]={};
  //c_common_usart_flush(GPS_USART);
  //c_common_usart_puts(GPS_USART,"log com1 bestposa\n\r");

  long timeout_init = c_common_utils_millis();
  long timeout_now  = c_common_utils_millis();

  while(c_common_usart_read(GPS_USART)!='R' && timeout_now - timeout_init < 40)
  {
    timeout_now  = c_common_utils_millis();
    c_common_utils_delayms(1);
  }

  int size1 = c_common_usart_read(GPS_USART);
  int size2 = c_common_usart_read(GPS_USART);

  if(size1<16 && size2<16 && size1>2 && size2>2)
  {
    for (int i = 0; i < size1; ++i)
    {
      dist[i]=c_common_usart_read(GPS_USART);
      lattitude=atof(dist);for (int i = 0; i < size1; ++i)
    {
      dist[i]=c_common_usart_read(GPS_USART);
      lattitude=atof(dist);
    }

    dist[0]=c_common_usart_read(GPS_USART);
    //memset(&dist[0],0,sizeof(dist));
    for (int i = 0; i < 15; ++i)
      dist[i]=0;

    for (int i = 0; i < size2; ++i)
    {
      dist[i]=c_common_usart_read(GPS_USART);
      lattitude=atof(dist);
    }

    if(c_common_usart_read(GPS_USART)=='\n')
    {
      xyz[0] = last_lattitude = lattitude;
      xyz[1] = last_longitude = longitude;
    }
    }

    c_common_usart_read(GPS_USART);
    //memset(&dist[0],0,sizeof(dist));
    for (int i = 0; i < 15; ++i)
      dist[i]=0;

    for (int i = 0; i < size2; ++i)
    {
      dist[i]=c_common_usart_read(GPS_USART);
      lattitude=atof(dist);
    }

    if(c_common_usart_read(GPS_USART)=='\n')
    {
      xyz[0] = last_lattitude = lattitude;
      xyz[1] = last_longitude = longitude;
    }
  }

  /*
  if(timeout_now - timeout_init < 40)
  {
    for (int i = 0; i < 15; ++i)
      dist[i]=c_common_usart_read(GPS_USART);
    lattitude=atof(dist)*100;

    c_common_usart_read(GPS_USART);   // ,

    for (int i = 0; i < 15; ++i)
      dist[i]=c_common_usart_read(GPS_USART);
    longitude=atof(dist)*100;

    if(c_common_usart_read(GPS_USART)=='\n')
    {
      xyz[0] = last_lattitude = lattitude;
      xyz[1] = last_longitude = longitude;
    }
  }
  */
  
  xyz[0] = last_lattitude;
  xyz[1] = last_longitude;
}
