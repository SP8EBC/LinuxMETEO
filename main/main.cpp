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
	ProgramConfig::readConfigFromFile();
	serial s;

	unsigned char globalChNumber = 0;
	unsigned char devicesNum = ProgramConfig::getDevicesNumber();

	s.init("/dev/ttyUSB0");

	UmbThread *t;
	t = new UmbThread(&s, ProgramConfig::getMasterId(), ProgramConfig::getDevices());
	t->serviceThread();

	delete t;

	return 0;

}


