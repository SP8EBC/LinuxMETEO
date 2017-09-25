/*
 * main.cpp
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */


#include <iostream>
#include "../serial/serial.h"
#include "../config/ProgramConfig.h"

using namespace std;

int main() {
	ProgramConfig::readConfigFromFile();
	serial s;

	unsigned char globalChNumber = 0;
	unsigned char devicesNum = ProgramConfig::getDevicesNumber();

//	vector<UmbDevice> devices = ProgramConfig::getDevices();

	s.init("/dev/ttyUSB0");

	for (int i = 0; i < devicesNum; i++ ) {
//		globalChNumber += devices[i].getChannels()->size();
	}



	return 0;

}


