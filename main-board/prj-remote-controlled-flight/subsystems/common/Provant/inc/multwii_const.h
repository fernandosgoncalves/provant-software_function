// Author = Fernando

#ifndef MULTIWII_CONST_H_
#define MULTIWII_CONST_H_

#define MSP_HEAD		36,77,62
#define MSP_LIST		100-1,120+1,200-1,254+1
#define MSP_IDENT    		100   //out message multitype + multiwii version + protocol version + capabilityvariable
#define MSP_STATUS    		101   //out message cycletime & errors_count & sensor present & box activation & current number
#define MSP_RAW_IMU   		102   //out message 9 DOF
#define MSP_SERVO      		103   //out message 8 servos
#define MSP_MOTOR     		104   //out message 8 motors
#define MSP_RC         		105   //out message 8 rc chan and more
#define MSP_RAW_GPS  		106   //out message fix, numsat, lat, lon, alt, speed, ground course
#define MSP_ATTITUDE 		108   //out message 2 angles 1 heading
#define MSP_COMP_GPS		107   //out message distance home, direction homeMSP_ATTITUDE
#define MSP_ALTITUDE  		109   //out message altitude, variometer
#define MSP_ANALOG     		110   //out message vbat, powermetersum, rssi if available on RX
#define MSP_RC_TUNING  		111   //out message rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_PID        		112   //out message P I D coeff (9 are used currently)
#define MSP_BOX       		113   //out message BOX setup (number is t of your setup)
#define MSP_MISC       		114   //out message powermeter trig
#define MSP_MOTOR_PINS 		115   //out message which pins are in use for motors & servos, for GUI 
#define MSP_BOXNAMES   		116   //out message the aux switch names
#define MSP_PIDNAMES   		117   //out message the PID names
#define MSP_WP         		118   //out message get a WP, WP# is in the payload, returns (WP#, lat, lon, alt, flags) WP#0-home, WP#16-poshold
#define MSP_BOXIDS           	119   //out message get the permanent IDs associated to BOXes
#define MSP_SERVO_CONF         	120   //out message Servo settings
#define MSP_SET_RAW_RC         	200   //in message 8 rc chan
#define MSP_SET_RAW_GPS        	201   //in message fix, numsat, lat, lon, alt, speed
#define MSP_SET_PID            	202   //in message P I D coeff (9 are used currently)
#define MSP_SET_BOX            	203   //in message BOX setup (number is dependant of your setup)
#define MSP_SET_RC_TUNING      	204   //in message rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_ACC_CALIBRATION    	205   //in message no param
#define MSP_MAG_CALIBRATION    	206   //in message no param
#define MSP_SET_MISC           	207   //in message powermeter trig + 8 free for future use
#define MSP_RESET_CONF         	208   //in message no param
#define MSP_SET_WP             	209   //in message sets a given WP (WP#,lat, lon, alt, flags)
#define MSP_SELECT_SETTING     	210   //in message Select Setting Number (0-2)
#define MSP_SET_HEAD           	211   //in message define a new heading hold direction
#define MSP_SET_SERVO_CONF     	212   //in message Servo settings
#define MSP_SET_MOTOR          	214   //in message PropBalance function
#define MSP_BIND               	240   //in message no param
#define MSP_EEPROM_WRITE       	250   //in message no param
#define MSP_DEBUGMSG           	253   //out message debug string buffer
#define MSP_DEBUG              	254   //out message debug1,debug2,debug3,debug4

#define MSP_RAW_GPS_SIZE	16
#define MSP_COMP_GPS_SIZE	5
#define MSP_ATTITUDE_SIZE	6
#define MSP_ANALOG_SIZE		7
#define MSP_ALTITUDE_SIZE	6
#define MSP_STATUS_SIZE		10
#define MSP_DEBUG_SIZE		8
#define MSP_RC_SIZE		24
#define MSP_PID_SIZE		30
#define MSP_IDENT_SIZE		7
#define MSP_SERVO_SIZE		16
#define MSP_MOTOR_PINS_SIZE	8
#define MSP_MOTOR_SIZE          16

/*class Attitude:
	roll		=0
	pitch		=0
	yaw			=0

class Raw_gps:
	fix     	=0
	numsats 	=0
	lat			=0
	lon			=0
	alt			=0
	speed		=0
	ggc			=0

class Comp_gps:
	distance	=0
	direction	=0
	update		=0

class Analog:
	vbat		=0
	power		=0
	rssi		=0
	current		=0

class Altitude:
	alt 		=0
	vario		=0

class Status:
	cycleTime	=0
	i2cec		=0
	sensor		=0
	flag		=0
	gccs		=0

class Debug:
	debug		=[0]*4

class Rc:
	channel		=[0]*12

class Pid:
	pid			=[0]*30

class Ident:
	version		=0
	multtype	=0
	mspversion	=0
	capability	=0

class RawIMU:
    gyr = [0,0,0]
    acc = [0,0,0]
    mag = [0,0,0]

class Servo:
	servo		=[0]*8

class Motor_pins:
	pin         =[0]*8

class Motor:
	motor 		=[0]*8*/

#endif /* MULTIWII_CONST_H_ */
