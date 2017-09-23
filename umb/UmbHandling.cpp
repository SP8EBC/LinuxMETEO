/*
 * UmbHandling.cpp
 *
 *  Created on: 19.09.2017
 *      Author: mateusz
 */

#include "UmbHandling.h"
#include "Routine26Query.h"
#include "Routine23Query.h"
#include "../types/UmbFrameStructRaw.h"

#include <string>

UmbHandling::UmbHandling() {
	// TODO Auto-generated constructor stub

}

int UmbHandling::checkStatus(unsigned short deviceId, unsigned short deviceClass, serial& serialPort) {

	UmbFrameRaw f;
	memset (&f, 0x00, sizeof(f));

	Routine26Query::prepareQuery(deviceId, deviceClass, &f);
	serialPort.transmitUmb(&f);
	serialPort.receiveUmb(2);


	return 0;
}

int UmbHandling::testChannelQuery(serial& serialPort) {
	UmbFrameRaw f;
	memset (&f, 0x00, sizeof(f));

	Routine23Query::prepareQuery(0x64, 1, 8, &f);
	serialPort.transmitUmb(&f);
	serialPort.receiveUmb(2);

	return 0;
}

UmbHandling::~UmbHandling() {
	// TODO Auto-generated destructor stub
}

