/**
  ******************************************************************************
  * @file    modules/io/c_io_imu.c
  * @author  Richard Andrade
  * @version V1.0.0
  * @date    4-Setembro-2015
  * @brief   Sensor para IMUs (baseado BMP180).
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "c_io_imu_bmp180.h"

/** @addtogroup Module_IO
  * @{
  */

/** @addtogroup Module_IO_Component_IMU
  * \brief Componente para IMU.
  *
  * Este componente é projetado para implementar funções do barometro BMP180 da aeronave - leitura
  * e pré-processamento.
  *
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
	// Calibration values
	int ac1;
	int ac2;
	int ac3;
	unsigned int ac4;
	unsigned int ac5;
	unsigned int ac6;
	int b1;
	int b2;
	int mb;
	int mc;
	int md;
}Cal_values;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2C_TypeDef* I2Cx_bmp180;
long b5;
Cal_values c_val;
/* Private function prototypes -----------------------------------------------*/
int c_io_imu_bmp180_ReadInt(uint8_t  address);
long c_io_imu_bmp180_ReadUT();
long c_io_imu_bmp180_ReadUP();
char c_io_imu_bmp180_Read(uint8_t address);
/* Private functions ---------------------------------------------------------*/
int c_io_imu_bmp180_ReadInt(uint8_t address)
{
	uint8_t  buffer[2];
	// Read two bytes from registers adress
	c_common_i2c_readBytes(I2Cx_bmp180, BMP180_ADDR, address, 2, buffer);
	return (int) (buffer[0]<<8 | buffer[1]);
}
char c_io_imu_bmp180_Read(uint8_t address)
{
	uint8_t  buffer[2];
	// Read two bytes from registers adress
	c_common_i2c_readBytes(I2Cx_bmp180, BMP180_ADDR, address, 1, buffer);
	return (char) buffer[0];
}

// Read the uncompensated temperature value
long c_io_imu_bmp180_ReadUT()
{
	long ut;
	// Write 0x2E into Register 0xF4
	// This requests a temperature reading
	c_common_i2c_writeByte(I2Cx_bmp180, BMP180_ADDR, BMP180_CTRL_MEAS, BMP180_TEMPERATURE);
	// Wait at least 4.5ms
	c_common_utils_delayms(BMP180_TIME_TEMP);
	// Read two bytes from registers 0xF6 and 0xF7
	ut = c_io_imu_bmp180_ReadInt(BMP180_OUT_MSB);

	return ut;
}

// Read the uncompensated pressure value
long c_io_imu_bmp180_ReadUP()
{
	uint8_t buffer[3]={};
	long up = 0;

	// Write 0x34+(OSS<<6) into register 0xF4
	// Request a pressure reading w/ oversampling setting
	c_common_i2c_writeByte(I2Cx_bmp180, BMP180_ADDR, BMP180_CTRL_MEAS, (0x34 + (OSS<<6))); //<- Ja é colocado no init
	// Wait for conversion, delay time dependent on OSS
	c_common_utils_delayms(OSS_TIME);//<- a Thread roda mais tempo nao precisa
	// Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
	c_common_i2c_readBytes(I2Cx_bmp180, BMP180_ADDR, BMP180_OUT_MSB, 3, buffer);

	up = (((long) buffer[0] << 16) | ((long) buffer[1] << 8) | (long) buffer[2]) >> (8-OSS);

	return up;
}

/* Exported functions definitions --------------------------------------------*/
void  c_io_imu_bmp180_int(I2C_TypeDef* I2Cx){
	I2Cx_bmp180=I2Cx;
	c_common_i2c_writeByte(I2Cx_bmp180, BMP180_ADDR, BMP180_CTRL_MEAS, (0x34 + (OSS<<6)));
	c_common_utils_delayms(OSS_TIME); //Waiting for ready the first sample
	c_io_imu_bmp180_Calibration();
}

// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void c_io_imu_bmp180_Calibration()
{
	char aux, aux2;
	c_val.ac1 = (short) c_io_imu_bmp180_ReadInt(0xAA);
	c_val.ac2 = (short) c_io_imu_bmp180_ReadInt(0xAC);
	c_val.ac3 = (short) c_io_imu_bmp180_ReadInt(0xAE);
	c_val.ac4 = (unsigned short) c_io_imu_bmp180_ReadInt(0xB0);
	c_val.ac5 = (unsigned short) c_io_imu_bmp180_ReadInt(0xB2);
	c_val.ac6 = (unsigned short) c_io_imu_bmp180_ReadInt(0xB4);
	c_val.b1 =  (short) c_io_imu_bmp180_ReadInt(0xB6);
	c_val.b2 =  (short) c_io_imu_bmp180_ReadInt(0xB8);
	c_val.mb =  (short) c_io_imu_bmp180_ReadInt(0xBA);
	c_val.mc =  (short) c_io_imu_bmp180_ReadInt(0xBC);
	c_val.md =  (short) c_io_imu_bmp180_ReadInt(0xBE);
}

// Calculate temperature in deg C
float c_io_imu_bmp180_getTemperature()
{
	long x1, x2;
	long ut = c_io_imu_bmp180_ReadUT();

	x1 = (((long)ut - (long)c_val.ac6)*(long)c_val.ac5) >> 15;
	x2 = ((long)c_val.mc << 11)/(x1 + c_val.md);
	b5 = x1 + x2;

	float temp = ((b5 + 8)>>4);
	temp = temp /10;

	return temp;
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
float c_io_imu_bmp180_getPressure()
{
	float pressure;
	long x1, x2, x3, b3, b6, p;
	unsigned long b4, b7;
	long up = c_io_imu_bmp180_ReadUP();
	b6 = b5 - 4000;
	// Calculate B3
	x1 = (c_val.b2 * (b6 * b6)>>12)>>11;
	x2 = (c_val.ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((long)c_val.ac1)*4 + x3)<<OSS) + 2)>>2;

	// Calculate B4
	x1 = (c_val.ac3 * b6)>>13;
	x2 = (c_val.b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (c_val.ac4 * (unsigned long)(x3 + 32768))>>15;

	b7 = ((unsigned long)(up - b3) * (50000>>OSS));
	if (b7 < 0x80000000)
		p = (b7<<1)/b4;
	else
		p = (b7/b4)<<1;

	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	p += (x1 + x2 + 3791)>>4;

	pressure=p*0.01;
	return pressure;
}

//Uncompensated caculation - in Meters
float c_io_imu_bmp180_Altitude(float pressure)
{
  float A = pressure/1013.25;
  float B = 1/5.25588;
  float C = pow(A,B);
  C = 1 - C;
  C = C /0.0000225577;  // ==> C = C / (1/44330)
                        // ==> C = C * 44330
  return C;
}
/* IRQ handlers ------------------------------------------------------------- */

/**
  * @}
  */

/**
  * @}
  */

