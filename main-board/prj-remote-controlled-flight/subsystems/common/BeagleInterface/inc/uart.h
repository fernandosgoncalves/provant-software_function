/*
 * communication.h
 *
 *  Created on: 14/05/2014
 *      Author: fernando
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdint.h>   /* Standard types */

class uart {
	int baudRate;
	int fd; //= 0;
	char port[256];
//	char buf[20], dat[20], use[1];
//	int rc,n;
//	bool debugmode =true;

public:
	uart();
	virtual ~uart();
	void setPort(char serialport[256]);
	void setBaudRate(int baudRate);
	char * getPort();
	int getBaudRate();
	int init();
	int writeByte(uint8_t b);
	int writeMsg(const char* str);
	int readUntil(char buffer[256], char until);
	int readByte(unsigned char *buffer);
	int bytesAvailable();
};

#endif /* COMMUNICATION_H_ */
