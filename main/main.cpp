/*
 * main.cpp
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */


#include <iostream>
#include "../serial/serial.h"
#include "../config/ProgramConfig.h"
#include "../umb/UmbThread.h"

using namespace std;

int main() {
#ifndef _ONLY_MANUAL_CFG
	ProgramConfig::readConfigFromFile();
#endif

#ifdef _ONLY_MANUAL_CFG
	ProgramConfig::manualConfig();
#endif

	serial s;

	unsigned char globalChNumber = 0;
	unsigned char devicesNum = ProgramConfig::getDevicesNumber();

	s.init("/dev/ttyUSBWX");

	UmbThread *t;
	t = new UmbThread(&s, ProgramConfig::getMasterId(), ProgramConfig::getDevices());
	t->serviceThread();

	delete t;

	return 0;

}


