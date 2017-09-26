/*
 * UmbThread.cpp
 *
 *  Created on: 24.09.2017
 *      Author: mateusz
 */

#include "UmbThread.h"
#include "../config/ProgramConfig.h"
#include "../umb/UmbHandling.h"
#include "../aprs/Mappings.h"

#include <vector>

UmbThread::UmbThread(serial* p, uint8_t master_id, vector<UmbDevice>* devices)
																	: port(p),
																	  masterId(master_id),
																	  devs(devices)

{

}

void UmbThread::serviceThread(void)
{
	unsigned char devicesNum = ProgramConfig::getDevicesNumber();
	vector<UmbDevice>::iterator itdevs = devs->begin();

	for (int id = 0; id < devicesNum; id++)
	{
		vector<DeviceChannel> *vc = itdevs[id].getChannels();
		vector<DeviceChannel>::iterator itchannels = vc->begin();

		for (int ic = 0; ic < (int)vc->size(); ic++)
		{
			DeviceChannel* channel = &itchannels[ic];
			unsigned int chnum = channel->getChannelNumber();
			ChannelUsage use = channel->getChannelUsage();

			ChannelValueFoundation *val = UmbHandling::channelQuery(itdevs[id].getDeviceId(),
																	itdevs[id].getDeviceClass(),
																	chnum,
																	*port);

			if (use != NONE) {
				Mappings::usageUnitMapping[use] = channel->getMeasurementUnit();
				Mappings::usageValuesMapping[use] = val;
			}

			printf("kanal: %d, wartosc: %s\r\n", chnum, val->toString().c_str());
		}
	}

}

UmbThread::~UmbThread() {
	// TODO Auto-generated destructor stub
}

