/*
 * UmbHandling.h
 *
 *  Created on: 19.09.2017
 *      Author: mateusz
 */

#ifndef UMB_UMBHANDLING_H_
#define UMB_UMBHANDLING_H_

#include "../serial/serial.h"

enum CommState {
	IDLE = 0,
	RXING = 1,
	TXING = 2,
	WAITING = 3
};

class UmbHandling {
private:

public:
	static int checkStatus(unsigned short deviceId, unsigned short deviceClass, serial& serialPort);
	static int testChannelQuery(serial& serialPort);

	UmbHandling();
	virtual ~UmbHandling();
};

#endif /* UMB_UMBHANDLING_H_ */
