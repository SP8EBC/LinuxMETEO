/*
 * Routine23AnswerCbk.cpp
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#include "Routine23AnswerCbk.h"
#include "../types/ChannelType.h"
#include "../types/Integer.h"
#include "../types/Float.h"

#include <cstring>
#include <stdint.h>

#include <cstdio>

Routine23AnswerCbk::Routine23AnswerCbk() {
	// TODO Auto-generated constructor stub

}

Routine23AnswerCbk::~Routine23AnswerCbk() {
	// TODO Auto-generated destructor stub
}


void* Routine23AnswerCbk::parseAnswer(UmbFrameRaw* in)
{
	void* return_value = 0;

	unsigned temp = 0;
	signed stemp = 0;
	float ftemp = 0.0f;

	unsigned char ff[] = {0x40, 0x16, 0x14, 0x7b};
	uint8_t ffa[] = {0x7b, 0x14, 0x16, 0x40};
	void *f = &ff;



	if (in == 0)
	{

	}
	else
	{
		uint8_t* content = in->content;
//		in->status = *content;

		unsigned short channelNumber = ( *(in->content + 1) | *(in->content + 2) << 8);
		unsigned char channelType = *(in->content + 3);

		switch(channelType)
		{
		case UNSIGNED_CHAR:
			return_value = new Integer();
			temp = (unsigned)((unsigned char)*(in->content + 4));
			((Integer*)return_value)->setValue((int) temp);

			break;
		case SIGNED_CHAR:
			return_value = new Integer();
			stemp = (signed)((signed char)*(in->content + 4));
			((Integer*)return_value)->setValue(stemp);

			break;
		case UNSIGNED_SHORT:
			return_value = new Integer();
			temp = (unsigned)((unsigned short)(*(in->content + 4) | *(in->content + 5) << 8));
			((Integer*)return_value)->setValue(temp);

			break;
		case SIGNED_SHORT:
			return_value = new Integer();
			stemp = (signed)((signed short)(*(in->content + 4) | *(in->content + 5) << 8));
			((Integer*)return_value)->setValue(stemp);

			break;
		case UNSIGNED_INT:
			return_value = new Integer();
			temp = (unsigned)((*(in->content + 4) | (*(in->content + 5) << 8) | (*(in->content + 6) << 16) | (*(in->content + 7) << 24)));
			((Integer*)return_value)->setValue(temp);

			break;
		case SIGNED_INT:
			return_value = new Integer();
			stemp = (signed)((*(in->content + 4) | (*(in->content + 5) << 8) | (*(in->content + 6) << 16) | (*(in->content + 7) << 24)));
			((Integer*)return_value)->setValue(temp);


			break;
		case FLOAT:
			return_value = new Float();
//			f = (float*)((*(in->content + 4) | (*(in->content + 5) << 8) | (*(in->content + 6) << 16) | (*(in->content + 7) << 24)));
//			ftemp = *(float*)((void*)ff);
			memcpy(&ftemp, in->content + 4, 4);
			((Float*)return_value)->setValue(ftemp);


			break;
		case DOUBLE:
			return_value = new Float();
			//*f = ((*(in->content + 4) | (*(in->content + 5) << 8) | (*(in->content + 6) << 16) | (*(in->content + 7) << 24)));
			memcpy(&ftemp, in->content + 4, 4);
			((Float*)return_value)->setValue(ftemp);

			break;
		default:
			return_value = new Float();
			((Float*)return_value)->setValue(0.0f);
			break;
		}
	}

	printf("parseAnswer - kanal: %d - status: %d - ln: %d - chtype: %d - temp: %d - stemp: %d - ftem: %f\r\n", ( *(in->content + 1) | *(in->content + 2) << 8),  (int)*(in->content), (int)(in->ln), *(in->content + 3), temp, stemp, ftemp);
	return return_value;
}

