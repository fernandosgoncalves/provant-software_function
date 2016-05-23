/*
 * communication.cpp
 *
 *  Created on: 14/05/2014
 *      Author: fernando
 */

#include "uart.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */

uart::uart() {
}
//
uart::~uart() {
//	// TODO Auto-generated destructor stub
	close(this->fd);
}

void uart::setPort(char serialport[256]) {
	strcpy(this->port, serialport);
}

void uart::setBaudRate(int baudRate) {
	this->baudRate = baudRate;
}

char * uart::getPort() {
	return this->port;
}

int uart::getBaudRate() {
	return this->baudRate;
}

int uart::init() {
	struct termios toptions;
	int fd;
	fd = open(this->port, O_RDWR | O_NOCTTY);
	if (fd == -1) {
		perror("init_serialport: Unable to open port ");
		return -1;
	}

	if (tcgetattr(fd, &toptions) < 0) {
		perror("init_serialport: Couldn't get term attributes");
		return -1;
	}

	speed_t brate = this->baudRate; // let you override switch below if needed
	switch (this->baudRate) {
	case 4800:
		brate = B4800;
		break;
	case 9600:
		brate = B9600;
		break;
	case 19200:
		brate = B19200;
		break;
	case 38400:
		brate = B38400;
		break;
	case 57600:
		brate = B57600;
		break;
	case 115200:
		brate = B115200;
		break;
	case 460800:
		brate = B460800;
		break;
	case 921600:
		brate = B921600;
		break;
	}

	cfsetispeed(&toptions, brate);
	cfsetospeed(&toptions, brate);

	toptions.c_cflag &= ~PARENB;
	toptions.c_cflag &= ~CSTOPB;
	toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8;

	// no flow control
	toptions.c_cflag &= ~CRTSCTS;
	toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
	toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
	toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
	toptions.c_oflag &= ~OPOST; // make raw

	// see: http://unixwiz.net/techtips/termios-vmin-vtime.html
	toptions.c_cc[VMIN] = 0;
	toptions.c_cc[VTIME] = 20;
	if (tcsetattr(fd, TCSANOW, &toptions) < 0) {
		perror("init_serialport: Couldn't set term attributes");
		return -1;
	}

	this->fd = fd;
	return 1;
}

int uart::writeByte(uint8_t b) {
//	bool debugmode = true;
//    if(debugmode == true) printf("%d\n", b);
	int n = write(this->fd, &b, 1);
	if (n != 1)
		return -1;
	return 0;
}

int uart::writeMsg(const char* str) {
	int len = strlen(str);
	int n = write(this->fd, str, len);
	if (n != len)
		return -1;
	return n;
}

int uart::readUntil(char buffer[255], char until) {
	unsigned char *b;
	int i = 0, n;
	do {
		n = readByte(b);
		if (n == -1)
			return -1;    // couldn't read
		if (n == 0) {
			usleep(500); // wait 0.5 msec try again
			continue;
		}
		buffer[i] = b[0];
		i++; 
		buffer[i] = 0;  // null terminate the string
	} while (b[0] != until);
	return i;
}

int uart::readByte(unsigned char *buffer) {
	//char b[1];
	int n = 0;
        n = read(this->fd, buffer, 1);  // read a char at a time
	if (n == -1) {
		printf("erro ao ler serial\n");
		return -1;    // couldn't read
	}
	//printf("%c\n", buffer[0]);
	return n;
}

int uart::bytesAvailable(){
	int bytes;
	ioctl(this->fd, FIONREAD, &bytes);
	return bytes;
}
