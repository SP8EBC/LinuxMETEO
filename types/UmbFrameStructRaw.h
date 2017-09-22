/*
 * UmbFrameStruct.h
 *
 *  Created on: 19.09.2017
 *      Author: mateusz
 */

#ifndef TYPES_UMBFRAMESTRUCTRAW_H_
#define TYPES_UMBFRAMESTRUCTRAW_H_


struct UmbFrameRaw {
	unsigned char protVersion;

	unsigned char slaveId;
	unsigned char slaveClass;

	unsigned char ln;

	unsigned char cmdId;

	unsigned char *content;

	unsigned short checksum;

	unsigned char status;
};



#endif /* TYPES_UMBFRAMESTRUCTRAW_H_ */
