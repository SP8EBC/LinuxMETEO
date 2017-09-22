/*
 * UmbHandling.h
 *
 *  Created on: 19.09.2017
 *      Author: mateusz
 */

#ifndef UMB_UMBHANDLING_H_
#define UMB_UMBHANDLING_H_

enum CommState {
	IDLE = 0,
	RXING = 1,
	TXING = 2,
	WAITING = 3
};

class UmbHandling {
private:

public:
	UmbHandling();
	virtual ~UmbHandling();
};

#endif /* UMB_UMBHANDLING_H_ */
