/*
 * Routine23AnswerCbk.h
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#ifndef UMB_ROUTINE23ANSWERCBK_H_
#define UMB_ROUTINE23ANSWERCBK_H_

#include "../types/ChannelValueFoundation.h"
#include "../types/UmbFrameStructRaw.h"

class Routine23AnswerCbk {
public:
	static void* parseAnswer(UmbFrameRaw* in);

	Routine23AnswerCbk();
	virtual ~Routine23AnswerCbk();
};

#endif /* UMB_ROUTINE23ANSWERCBK_H_ */
