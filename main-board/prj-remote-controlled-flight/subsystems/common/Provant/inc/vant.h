/*
 *-----------------------------------------------------------------------------
 *  Filename:    vant.h
 *  Header of Vant class that storage the UAV dynamics
 *  Created on: 24/09/2014
 *  Author: Fernando S. Gonçalves
 *-----------------------------------------------------------------------------
 *     ___                           _
 *    / _ \_ __ ___/\   /\__ _ _ __ | |_
 *   / /_)/ '__/ _ \ \ / / _` | '_ \| __|
 *  / ___/| | | (_) \ V / (_| | | | | |_
 *  \/    |_|  \___/ \_/ \__,_|_| |_|\__|
 *
 *-----------------------------------------------------------------------------
 *
 */

#ifndef VANT_H_
#define VANT_H_

#include <stdint.h>   /* Standard types */
#include "proVantTypes.h"

class vant {
	//Vant Dynamics
	float roll;
	float pitch;
	float yaw;
	float dotRoll;
	float dotPitch;
	float dotYaw;
	float x;
	float y;
	float z;
	float dotX;
	float dotY;
	float dotZ;
	float alphar;
	float alphal;
	float dotAlphar;
	float dotAlphal;

	//Control output:
	float servoLeft;
	float escLeftNewtons;
	float escLeftSpeed;

	float servoRight;
	float escRightNewtons;
	float escRightSpeed;
	
	//Esc data:
	int rpm[2];
	float current[2];
	float voltage[2];

	//GPS Raw Data
	uint8_t gpsFix;
	uint8_t gpsNumSat;
	uint32_t gpsCoordLat;
	uint32_t gpsCoordLong; 
	uint16_t gpsAltitude;
	uint16_t gpsSpeed;
	uint16_t gpsGroundCourse;
	
	//GPS Comp Data
	uint16_t gpsDistanceToHome;
	uint16_t gpsDirectionToHome;
	uint8_t gpsUpdate;

	//Analog
	uint8_t  vbat;
	uint16_t intPowerMeterSum;
	uint16_t rssi;
	uint16_t amperage;

	//Altitude
	int32_t estAlt;
	int16_t vario;

	//Status
	uint16_t cycleTime;
	uint16_t i2cErrorsCount;
	uint16_t sensor;
	uint32_t flag;
	
	//RC
	int16_t channels[7];

	//RC Normalize
	int16_t normChannels[7];

	//IDENT
	uint8_t version; 
	uint8_t multitype;
	uint8_t mspVersion;
	uint32_t capability;
	bool stop;
	
	//Motor Pins
	uint8_t pwmPin[8];

	//Motor Speed
	uint16_t motorSpeed[6];

	//Servos
	int16_t servos[6];
	
	//Debug
	int16_t debug[4];

	//Debug
	float debug2[4];

	//Raw Imu Data
	int16_t gyro[3];
	int16_t mag[3];
	int16_t acc[3];
public:
	vant();
	virtual ~vant();
	void setRoll(float roll);
	float getRoll();
	void setPitch(float pitch);
	float getPitch();
	void setYaw(float yaw);
	float getYaw();
	void setDotRoll(float dotRoll);
	float getDotRoll();
	void setDotPitch(float dotPitch);
	float getDotPitch();
	void setDotYaw(float dotYaw);
	float getDotYaw();
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	void setZ(float z);
	float getZ();
	void setDotX(float dotX);
	float getDotX();
	void setDotY(float dotY);
	float getDotY();
	void setDotZ(float dotZ);
	float getDotZ();
	void setAlphal(float alphal);
	float getAlphal();
	void setAlphar(float alphar);
	float getAlphar();
	void setDotAlphal(float dotAlphal);
	float getDotAlphal();
	void setDotAlphar(float dotAlphar);
	float getDotAlphar();
	void setServoLeft(float servoLeft);
	float getServoLeft();
	void setEscLeftNewtons(float escLeftNewtons);
	float getEscLeftNewtons();
	void setEscLeftSpeed(float escLeftSpeed);
	float getEscLeftSpeed();
	void setServoRight(float servoRight);
	float getServoRight();
	void setEscRightNewtons(float escRightNewtons);
	float getEscRightNewtons();
	void setEscRightSpeed(float escRightSpeed);
	float getEscRightSpeed();
	void setRpm(int pos, int rpm);
	float getRpm(int pos);
	void setCurrent(int pos,float current);
	float getCurrent(int pos);
	void setVoltage(int pos,float voltage);
	float getVoltage(int pos);
	void setGpsFix(uint8_t gpsFix);
	uint8_t getGpsFix();
	void setGpsNumSat(uint8_t gpsNumSat);
	uint8_t getGpsNumSat();
	void setGpsCoordLat(uint32_t gpsCoordLat);
	uint32_t getGpsCoordLat();
	void setGpsCoordLong(uint32_t gpsCoordLong);
	uint32_t getGpsCoordLong();
 	void setGpsAltitude(uint16_t gpsAltitude);
	uint16_t getGpsAltitude();
	void setGpsSpeed(uint16_t gpsSpeed);
	uint16_t getGpsSpeed();
	void setGpsGroundCourse(uint16_t gpsGroundCourse);
	uint16_t getGpsGroundCourse();
	uint16_t setGpsDistanceToHome(uint16_t gpsDistanceToHome);
	uint16_t getGpsDistanceToHome();
	uint16_t setGpsDirectionToHome(uint16_t gpsDirectionToHome);
	uint16_t getGpsDirectionToHome();
	uint8_t setGpsUpdate(uint8_t gpsUpdate);
	uint8_t getGpsUpdate();
	void setVbat(uint8_t vbat);
	uint8_t getVbat();
	void setIntPowerMeterSum(uint16_t intPowerMeterSum);
	uint16_t getIntPowerMeterSum();
	void setRssi(uint16_t rssi);
	uint16_t getRssi();
	void setAmperage(uint16_t amperage);
	uint16_t getAmperage();
	void setEstAlt(int32_t estAlt);
	int32_t getEstAlt();
	void setVario(int16_t vario);
	int16_t getVario();
	void setCycleTime(uint16_t cycleTime);
	uint16_t getCycleTime();
	void setI2cErrorsCount(uint16_t i2cErrorsCount);
	uint16_t getI2cErrorsCount();
	void setSensor(uint16_t sensor);
	uint16_t getSensor();
	void setFlag(uint32_t flag);
	uint32_t getFlag();
	void setChannel(int channel, uint16_t value);
	uint16_t getChannel(int channel);
	void setNormChannel(int channel, int16_t value);
	int16_t getNormChannel(int channel);
	void setVersion(uint8_t version);
	uint8_t getVersion();
	void setMultitype(uint8_t multitype);
	uint8_t getMultitype();
	void setMspVersion(uint8_t mspVersion);
	uint8_t getMspVersion();
	void setCapability(uint32_t capability);
	uint32_t getCapability();
	void setPwmPin(int pin, uint8_t value);
	uint8_t getPwmPin(int pin);
	void setMotorSpeed(int motor, uint16_t value);
	uint16_t getMotorSpeed(int motor);
	void setServo(int servo, int16_t angle);
	int16_t getServo(int servo);
	void setDebug(int pos, int16_t value);
	int16_t getDebug(int pos);
	void setDebug2(int pos, float value);
	float getDebug2(int pos);
	void setGyro(int pos, int16_t value);
	int16_t getGyro(int pos);
	void setMag(int pos, int16_t value);
	int16_t getMag(int pos);
	void setAcc(int pos, int16_t value);
	int16_t getAcc(int pos);
	proVant::atitude getAtitude();
	proVant::position getPosition();
	proVant::servos_state getServoState();
	proVant::controlOutput getActuation();
	proVant::debug getDebug();
	proVant::debug2 getDebug2();
	proVant::rcNormalize getNormChannels();
	proVant::status getStatus();
};

#endif /* VANT_H_ */
