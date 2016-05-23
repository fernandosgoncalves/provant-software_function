/*
 *-----------------------------------------------------------------------------
 *  Filename:    vant.cpp
 *  Implementation of Vant class
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

#include "vant.h"

vant::vant() {
	int i;
	//Vant Dynamics
	dotPitch = 0;
	dotRoll = 0;
	dotYaw = 0;
	pitch = 0;
	roll = 0;
	dotX = 0;
	dotY = 0;
	dotZ = 0;
	yaw = 0;
	x = 0;
	y = 0;
	z = 0;
	alphar=0;
	alphal=0;
	dotAlphar=0;
	dotAlphal=0;

	//Control output:
	escRightNewtons = 0;
	escLeftNewtons = 0; 
	escRightSpeed = 0;
	escLeftSpeed = 0;
	servoRight = 0;
	servoLeft = 0;
	
	//Esc data:
	current[0] = 0;
	voltage[0] = 0;
	current[1] = 0;
	voltage[1] = 0;
	rpm[0] = 0;
	rpm[1] = 0;


	//GPS Raw Data
	gpsFix = 0;
	gpsNumSat = 0;
	gpsCoordLat = 0;
	gpsCoordLong = 0; 
	gpsAltitude = 0;
	gpsSpeed = 0;
	gpsGroundCourse = 0;
	
	//GPS Comp Data
	gpsDistanceToHome = 0;
	gpsDirectionToHome = 0;
	gpsUpdate = 0;

	//Analog
	vbat = 0;
	intPowerMeterSum = 0;
	rssi = 0;
	amperage = 0;

	//Altitude
	estAlt = 0;
	vario = 0;

	//Status
	cycleTime = 0;
	i2cErrorsCount = 0;
	sensor = 0;
	flag = 0;
	
	//RC
	for(i = 0; i < 7; i++){
		channels[i] = 0;
		normChannels[i] = 0;
	}

	//IDENT
	version = 0; 
	multitype = 0;
	mspVersion = 0;
	capability = 0;
	stop=1;

	//Motor Pins
	for(i = 0; i < 8; i++){
		pwmPin[i] = 0;
	}

	//Speed Motors
	for(i=0; i < 6; i++){
		motorSpeed[i] = 0;
		//servos
		servos[i] = 0;
	}

	//Debug
	for(i=0; i < 4; i++){
		debug[i] = 0;
	}
	
	//RAW IMU
	for(i=0; i<3; i++){
		gyro[i] = 0;
		mag[i] = 0;
		acc[i] = 0;
	}
}

vant::~vant() {
}

void vant::setRoll(float roll) {
	this->roll = roll;
}

float vant::getRoll(){
	return this->roll;
}

void vant::setPitch(float pitch){
	this->pitch = pitch;
}

float vant::getPitch(){
	return this->pitch;
}

void vant::setYaw(float yaw){
	this->yaw = yaw;
}

float vant::getYaw(){
	return this->yaw;
}

void vant::setDotRoll(float dotRoll){
	this->dotRoll = dotRoll;
}

float vant::getDotRoll(){
	return this->dotRoll;
}

void vant::setDotPitch(float dotPitch){
	this->dotPitch = dotPitch;
}

float vant::getDotPitch(){
	return this->dotPitch;
}

void vant::setDotYaw(float dotYaw){
	this->dotYaw = dotYaw;
}

float vant::getDotYaw(){
	return this->dotYaw;
}

void vant::setX(float x){
	this->x = x;
}

float vant::getX(){
	return this->x;
}

void vant::setY(float y){
	this->y = y;
}

float vant::getY(){
	return this->y;
}

void vant::setZ(float z){
	this->z = z;
}

float vant::getZ(){
	return this->z;
}

void vant::setDotX(float dotX){
	this->dotX = dotX;
}

float vant::getDotX(){
	return this->dotX;
}

void vant::setDotY(float dotY){
	this->dotY = dotY;
}

float vant::getDotY(){
	return this->dotY;
}

void vant::setDotZ(float dotZ){
	this->dotZ = dotZ;
}

float vant::getDotZ(){
	return this->dotZ;
}

void vant::setServoLeft(float servoLeft){
	this->servoLeft = servoLeft;
}

float vant::getServoLeft(){
	return this->servoLeft;
}

void vant::setEscLeftNewtons(float escLeftNewtons){
	this->escLeftNewtons = escLeftNewtons;
}

float vant::getEscLeftNewtons(){
	return this->escLeftNewtons;
}

void vant::setEscLeftSpeed(float escLeftSpeed){
	this->escLeftSpeed = escLeftSpeed;
}

float vant::getEscLeftSpeed(){
	return this->escLeftSpeed;
}

void vant::setServoRight(float servoRight){
	this->servoRight = servoRight;
}

float vant::getServoRight(){
	return this->servoRight;
}

void vant::setEscRightNewtons(float escRightNewtons){
	this->escRightNewtons = escRightNewtons;
}

float vant::getEscRightNewtons(){
	return this->escRightNewtons;
}

void vant::setEscRightSpeed(float escRightSpeed){
	this->escRightSpeed = escRightSpeed;
}

float vant::getEscRightSpeed(){
	return this->escRightSpeed;
}

void vant::setRpm(int pos, int rpm){
	this->rpm[pos] = rpm;
}

float vant::getRpm(int pos){
	return this->rpm[pos];
}

void vant::setCurrent(int pos, float current){
	this->current[pos] = current;
}

float vant::getCurrent(int pos){
	return this->current[pos];
}

void vant::setVoltage(int pos, float voltage){
	this->voltage[pos] = voltage;
}

float vant::getVoltage(int pos){
	return this->voltage[pos];
}

void vant::setGpsFix(uint8_t gpsFix){
	this->gpsFix = gpsFix;
}

uint8_t vant::getGpsFix(){
	return gpsFix;
}

void vant::setGpsNumSat(uint8_t gpsNumSat){
	this->gpsNumSat = gpsNumSat;
}

uint8_t vant::getGpsNumSat(){
	return gpsNumSat;
}

void vant::setGpsCoordLat(uint32_t gpsCoordLat){
	this->gpsCoordLat = gpsCoordLat;
}

uint32_t vant::getGpsCoordLat(){
	return gpsCoordLat;
}

void vant::setGpsCoordLong(uint32_t gpsCoordLong){
	this->gpsCoordLong = gpsCoordLong;
}

uint32_t vant::getGpsCoordLong(){
	return gpsCoordLong;
}

void vant::setGpsAltitude(uint16_t gpsAltitude){
	this->gpsAltitude = gpsAltitude;
}

uint16_t vant::getGpsAltitude(){
	return gpsAltitude;
}

void vant::setGpsSpeed(uint16_t gpsSpeed){
	this->gpsSpeed = gpsSpeed;
}

uint16_t vant::getGpsSpeed(){
	return gpsSpeed;
}

void vant::setGpsGroundCourse(uint16_t gpsGroundCourse){
	this->gpsGroundCourse = gpsGroundCourse;
}

uint16_t vant::getGpsGroundCourse(){
	return gpsGroundCourse;
}

uint16_t vant::setGpsDistanceToHome(uint16_t gpsDistanceToHome){
	this->gpsDistanceToHome = gpsDistanceToHome;
}

uint16_t vant::getGpsDistanceToHome(){
	return gpsDistanceToHome;
}

uint16_t vant::setGpsDirectionToHome(uint16_t gpsDirectionToHome){
	this->gpsDirectionToHome = gpsDirectionToHome;
}

uint16_t vant::getGpsDirectionToHome(){
	return gpsDirectionToHome;
}

uint8_t vant::setGpsUpdate(uint8_t gpsUpdate){
	this->gpsUpdate = gpsUpdate;
}

uint8_t vant::getGpsUpdate(){
	return gpsUpdate;
}

void vant::setVbat(uint8_t vbat){
	this->vbat = vbat;
}

uint8_t vant::getVbat(){
	return vbat;
}

void vant::setIntPowerMeterSum(uint16_t intPowerMeterSum){
	this->intPowerMeterSum = intPowerMeterSum;
}

uint16_t vant::getIntPowerMeterSum(){
	return intPowerMeterSum;
}

void vant::setRssi(uint16_t rssi){
	this->rssi = rssi;
}

uint16_t vant::getRssi(){
	return rssi;
}

void vant::setAmperage(uint16_t amperage){
	this->amperage = amperage;
}

uint16_t vant::getAmperage(){
	return amperage;
}

void vant::setEstAlt(int32_t estAlt){
	this->estAlt = estAlt;
}

int32_t vant::getEstAlt(){
	return estAlt;
}

void vant::setVario(int16_t vario){
	this->vario = vario;
}

int16_t vant::getVario(){
	return vario;
}

void vant::setCycleTime(uint16_t cycleTime){
	this->cycleTime = cycleTime;
}

uint16_t vant::getCycleTime(){
	return cycleTime;
}

void vant::setI2cErrorsCount(uint16_t i2cErrorsCount){
	this->i2cErrorsCount = i2cErrorsCount;
}

uint16_t vant::getI2cErrorsCount(){
	return i2cErrorsCount;
}

void vant::setSensor(uint16_t sensor){
	this->sensor = sensor;
}

uint16_t vant::getSensor(){
	return sensor;
}

void vant::setFlag(uint32_t flag){
	this->flag = flag;
}

uint32_t vant::getFlag(){
	return flag;
}

void vant::setChannel(int channel, uint16_t value){
	this->channels[channel-1] = value;

}

uint16_t vant::getChannel(int channel){
	return channels[channel-1];
}

void vant::setNormChannel(int channel, int16_t value){
	this->normChannels[channel-1] = value;

}

int16_t vant::getNormChannel(int channel){
	return normChannels[channel-1];
}

void vant::setVersion(uint8_t version){
	this->version = version;
}

uint8_t vant::getVersion(){
	return version;
}

void vant::setMultitype(uint8_t multitype){
	this->multitype = multitype;
}

uint8_t vant::getMultitype(){
	return multitype;
}

void vant::setMspVersion(uint8_t mspVersion){
	this->mspVersion = mspVersion;
}

uint8_t vant::getMspVersion(){
	return mspVersion;
}

void vant::setCapability(uint32_t capability){
	this->capability = capability;
}

uint32_t vant::getCapability(){
	return capability;
}

void vant::setPwmPin(int pin, uint8_t value){
	this->pwmPin[pin-1] = value;

}

uint8_t vant::getPwmPin(int pin){
	return pwmPin[pin-1];
}

void vant::setMotorSpeed(int motor, uint16_t value){
	this->motorSpeed[motor-1] = value;

}

uint16_t vant::getMotorSpeed(int motor){
	return motorSpeed[motor-1];
}

void vant::setServo(int servo, int16_t angle){
	this->servos[servo-1] = angle;
}

int16_t vant::getServo(int servo){
	return servos[servo-1];
}

void vant::setDebug(int pos, int16_t value){
	this->debug[pos-1] = value;
}

int16_t vant::getDebug(int pos){
	return this->debug[pos-1];
}

void vant::setDebug2(int pos, float value){
	this->debug2[pos-1] = value;
}

float vant::getDebug2(int pos){
	return this->debug2[pos-1];
}

void vant::setGyro(int pos, int16_t value){
	this->gyro[pos-1] = value;
}

int16_t vant::getGyro(int pos){
	return this->gyro[pos-1];
}

void vant::setMag(int pos, int16_t value){
	this->mag[pos-1] = value;
}

int16_t vant::getMag(int pos){
	return this->mag[pos-1];
}

void vant::setAcc(int pos, int16_t value){
	this->acc[pos-1] = value;
}

int16_t vant::getAcc(int pos){
	return this->acc[pos-1];
}

void vant::setAlphal(float alphal){
	this->alphal=alphal;
}
float vant::getAlphal(){
	return this->alphal;
}
void vant::setAlphar(float alphar){
	this->alphar=alphar;
}
float vant::getAlphar(){
	return this->alphar;
}
void vant::setDotAlphal(float dotAlphal){
	this->dotAlphal=dotAlphal;
}
float vant::getDotAlphal(){
	return this->dotAlphal;
}
void vant::setDotAlphar(float dotAlphar){
	this->dotAlphar=dotAlphar;
}
float vant::getDotAlphar(){
	return this->dotAlphar;
}

proVant::atitude vant::getAtitude(){
	proVant::atitude atd;

	atd.roll = this->getRoll();
	atd.pitch = this->getPitch();
	atd.yaw = this->getYaw();
	atd.dotRoll = this->getDotRoll();
	atd.dotPitch = this->getDotPitch();
	atd.dotYaw = this->getDotYaw();

	return atd;
}
proVant::status vant::getStatus(){
	proVant::status aux;
	aux.cycleTime=0;
	aux.flag=0;
	aux.i2cErrorsCount=0;
	aux.sensor=0;
	aux.stop=this->rpm[0];
	return aux;
}
proVant::position vant::getPosition(){
	proVant::position position;
	position.x=this->getX();
	position.y=this->getY();
	position.z=this->getZ();

	position.dotX=this->getDotX();
	position.dotY=this->getDotY();
	position.dotZ=this->getDotZ();

	return position;
}

proVant::servos_state vant::getServoState(){
	proVant::servos_state servos;
	servos.alphal=this->current[0];
	servos.alphar=this->current[1];
	servos.dotAlphal=this->voltage[0];
	servos.dotAlphar=this->voltage[1];
	return servos;
}

proVant::controlOutput vant::getActuation(){
	proVant::controlOutput actuation;
	actuation.servoLeft=this->servoLeft;
	actuation.servoRight=this->servoRight;
	actuation.escRightNewtons=this->escRightNewtons;
	actuation.escLeftNewtons=this->escLeftNewtons;
	actuation.escRightSpeed=this->escRightSpeed;
	actuation.escLeftSpeed=this->escLeftSpeed;
	return actuation;
}
proVant::debug vant::getDebug(){
	proVant::debug debug2;
	debug2.debug[0]=this->debug[0];
	debug2.debug[1]=this->debug[1];
	debug2.debug[2]=this->debug[2];
	debug2.debug[3]=this->debug[3];
	return debug2;
}
proVant::debug2 vant::getDebug2(){
	proVant::debug2 debug2;
	debug2.debug[0]=this->debug2[0];
	debug2.debug[1]=this->debug2[1];
	debug2.debug[2]=this->debug2[2];
	debug2.debug[3]=this->debug2[3];
	return debug2;
}
proVant::rcNormalize vant::getNormChannels(){
	proVant::rcNormalize channel;
	channel.normChannels[0]=this->normChannels[0];
	channel.normChannels[1]=this->normChannels[1];
	channel.normChannels[2]=this->normChannels[2];
	channel.normChannels[3]=this->normChannels[3];
	channel.normChannels[4]=this->normChannels[4];
	channel.normChannels[5]=this->normChannels[5];
	channel.normChannels[6]=this->normChannels[6];
	return channel;
}
