/*
 * serial.cpp
 *
 *  Created on: 22.09.2017
 *      Author: mateusz
 */

#include "serial.h"
#include <iostream>
#include <stdint.h>
#include <cstring>
#include <vector>
#include <string>
#include <sys/time.h>

#include "../exceptions/NullPointerE.h"
#include "../exceptions/TimeoutE.h"

#include "../config/ProgramConfig.h"

#define SOH 0x01
#define STX 0x02
#define ETX 0x03
#define EOT 0x04

#define V10 0x10

#define MASTER_ID 0x01

serial::serial() {
	// TODO Auto-generated constructor stubes
}

void serial::transmitUmb(UmbFrameRaw* in) {
	int i = 0;
	unsigned short crc = 0xFFFF;

	if (in == 0)
		throw NullPointerE();

	char *txbuffer = new char[in->ln + 15];
	memset(txbuffer, 0x00, in->ln + 15);

	txbuffer[i++] = SOH;
	txbuffer[i++] = V10;
	txbuffer[i++] = in->slaveId;
	txbuffer[i++] = in->slaveClass << 4;
	txbuffer[i++] = ProgramConfig::getMasterId();
	txbuffer[i++] =  0xF0;
	txbuffer[i++] = in->ln;
	txbuffer[i++] = STX;
	//
	txbuffer[i++] = in->cmdId;
	txbuffer[i++] = V10;
	for (int j; j < in->ln - 2; j++ )
		txbuffer[i++] = *(in->content+j);
	//
	txbuffer[i++] = ETX;
	for (int j = 0; j < i; j++)
		crc = calc_crc(crc, txbuffer[j]);
	txbuffer[i++] = crc & 0xFF;
	txbuffer[i++] = (crc & 0xFF00) >> 8;
	txbuffer[i++] = EOT;

	write(handle, txbuffer, i);
}

UmbFrameRaw* serial::receiveUmb(unsigned short max_timeout) {
	uint8_t ln_rcv = 0;
	uint8_t rx_buf = 0;
	uint8_t n = 0;
	uint8_t pos = 0;
	struct timeval timeout, timeout_start;

	vector<uint8_t> *rx = new vector<uint8_t>();

	gettimeofday(&timeout_start, NULL);
	do {
		gettimeofday(&timeout, NULL);
		if (timeout.tv_sec - timeout_start.tv_sec > 2)
			break;		//TODO: zrobić rzucanie wyjątku

		n = read(handle, &rx_buf, 1);
	}while(rx_buf != SOH);

	rx->push_back(rx_buf);
	pos = 2;

	for (pos; pos <= 7; pos++)
	{
		gettimeofday(&timeout, NULL);
		if (timeout.tv_sec - timeout_start.tv_sec > 2)
			throw TimeoutE();		//TODO: zrobić rzucanie wyjątku

		n = read(handle, &rx_buf, 1);
		if (n != 0)
			rx->push_back(rx_buf);
		else
			throw TimeoutE();
	}

	ln_rcv = rx_buf;
	ln_rcv += 4;

	for (pos; pos <= ln_rcv; pos++) {
		gettimeofday(&timeout, NULL);
		if (timeout.tv_sec - timeout_start.tv_sec > 2)
			throw TimeoutE();		//TODO: zrobić rzucanie wyjątku

		n = read(handle, &rx_buf, 1);
		if (n != 0)
			rx->push_back(rx_buf);
		else
			throw TimeoutE();
	}

}

serial::~serial() {
	// TODO Auto-generated destructor stub
}

void serial::init(string port)
{
	struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof tty);

	handle = open( port.c_str(), O_RDWR| O_NOCTTY );


	/* Error Handling */
	if ( tcgetattr ( handle, &tty ) != 0 ) {
	   std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */
	cfsetospeed (&tty, (speed_t)B19200);
	cfsetispeed (&tty, (speed_t)B19200);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag		&=  ~ICANON;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  0;                  // read doesn't block
	tty.c_cc[VTIME]  =  9;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	tty.c_iflag = 0;
	tty.c_oflag = 0;

	tty.c_cc[VINTR]    = 0;     /* Ctrl-c */
	tty.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
	tty.c_cc[VERASE]   = 0;     /* del */
	tty.c_cc[VKILL]    = 0;     /* @ */
	tty.c_cc[VEOF]     = 4;     /* Ctrl-d */
	tty.c_cc[VTIME]    = 0;     /* inter-character timer unused */
	tty.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
	tty.c_cc[VSWTC]    = 0;     /* '\0' */
	tty.c_cc[VSTART]   = 0;     /* Ctrl-q */
	tty.c_cc[VSTOP]    = 0;     /* Ctrl-s */
	tty.c_cc[VSUSP]    = 0;     /* Ctrl-z */
	tty.c_cc[VEOL]     = 0;     /* '\0' */
	tty.c_cc[VREPRINT] = 0;     /* Ctrl-r */
	tty.c_cc[VDISCARD] = 0;     /* Ctrl-u */
	tty.c_cc[VWERASE]  = 0;     /* Ctrl-w */
	tty.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
	tty.c_cc[VEOL2]    = 0;     /* '\0' */

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( handle, TCIFLUSH );
	if ( tcsetattr ( handle, TCSANOW, &tty ) != 0) {
	   std::cout << "Error " << errno << " from tcsetattr" << std::endl;
	}
}

void serial::test_transmit()
{
	for (uint8_t i = 0; i < 255; i++)
		write( handle, &i, 1 );
}

short serial::checkCRC(char* pInputData) {
	char ii,i = 0;
	unsigned short crc = 0xFFFF;
	ii = pInputData[6] + 12;
	for (i = 0; i < ii - 3; i++)
		crc = calc_crc(crc, pInputData[i]);
	if ( (pInputData[ii - 2] == ( (crc & 0xFF00) >> 8) ) && ( pInputData[ii - 3] == (crc & 0xFF) ) )
		return 0;
	else
		return -1;
}

unsigned short serial::calc_crc(unsigned short crc_buff, unsigned char input) {
	unsigned char i;
	unsigned short x16;
	for	(i=0; i<8; i++)
	{
		// XOR current D0 and next input bit to determine x16 value
		if		( (crc_buff & 0x0001) ^ (input & 0x01) )
			x16 = 0x8408;
		else
			x16 = 0x0000;
		// shift crc buffer
		crc_buff = crc_buff >> 1;
		// XOR in the x16 value
		crc_buff ^= x16;
		// shift input for next iteration
		input = input >> 1;
	}
	return (crc_buff);
}

