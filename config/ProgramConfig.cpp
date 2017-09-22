/*
 * ProgramConfig.cpp
 *
 *  Created on: 12.09.2017
 *      Author: mateusz
 */

#include "ProgramConfig.h"

#include <sstream>
#include <iostream>
#include <string>
#include <libconfig.h++>

float ProgramConfig::lat = 0.0f;
float ProgramConfig::lon = 0.0f;
bool ProgramConfig::latns;
bool ProgramConfig::lonwe;

string ProgramConfig::comport;
string ProgramConfig::outputAprxFile;
unsigned char ProgramConfig::devicesNumber;
vector<UmbDevice> ProgramConfig::devices;

using namespace libconfig;

ProgramConfig::ProgramConfig() {
	// TODO Auto-generated constructor stub

}

ProgramConfig::~ProgramConfig() {
	// TODO Auto-generated destructor stub
}

string ProgramConfig::getLat() {
	ostringstream out;
	out << ProgramConfig::lat;

	return out.str();
}

string ProgramConfig::getLon() {
	ostringstream out;
	out << ProgramConfig::lon;

	return out.str();
}

string ProgramConfig::getLatns() {
	ostringstream out;

	if (ProgramConfig::latns)
		out << "S";
	else
		out << "N";

	return out.str();
}

const string& ProgramConfig::getOutputAprxFile() {
	return outputAprxFile;
}

unsigned char ProgramConfig::getDevicesNumber() {
	return devicesNumber;
}

void ProgramConfig::setDevicesNumber(unsigned char devicesNumber) {
	ProgramConfig::devicesNumber = devicesNumber;
}

void ProgramConfig::setOutputAprxFile(const string& outputAprxFile) {
	this->outputAprxFile = outputAprxFile;
}

string ProgramConfig::getLonwe() {
	ostringstream out;

	if (ProgramConfig::lonwe)
		out << "E";
	else
		out << "W";

	return out.str();
}

int ProgramConfig::readConfigFromFile() {
	Config cLibConfig;

	try {
		cLibConfig.readFile("/etc/linuxmeteo.conf");
		cout << "--- libconfig++: Otwieram plik konfiguracyjny..." << endl;
	}

	catch(const FileIOException &ex)
	{
		printf("--- libconfig++: Nie mozna otworzyc pliku!!!\r\n");
		return -1;
	}
	catch(const ParseException &ex) {
		printf("--- libconfig++: Blad parsowania pliku wejsciowego!!!");
		return -2;
	}

	Setting &rRoot = cLibConfig.getRoot();

	cLibConfig.lookupValue("ComPort", comport);
	cLibConfig.lookupValue("OutputAprxFile", outputAprxFile);

	Setting &Devs = rRoot["Devices"];
	devicesNumber = Devs.getLength();

	cout << "devicesNumber: " << devicesNumber << endl;

	for (int ii = 0; ii < devicesNumber; ii++)
	{
			UmbDevice* d = new UmbDevice();
			int temp;

			Devs[ii].lookupValue("deviceId", temp);
			d->setDeviceId((unsigned short)temp);

			Devs[ii].lookupValue("deviceClass", temp);
			d->setDeviceClass((unsigned short)temp);

			Setting &Channels = Devs[ii].lookup("Channels");

			for (int iii = 0; iii < Channels.getLength(); iii++)
			{
				DeviceChannel* dc = new DeviceChannel();
				string s;

				Channels[iii].lookupValue("channelNumber", temp);
				dc->setChannelNumber((unsigned int) temp);

				Channels[iii].lookupValue("channelName", s);
				dc->setChannelName(s);

				Channels[iii].lookupValue("channelType", s);
				dc->setChannelType(DeviceChannel::CastStringToEnum(s));

				d->getChannels()->push_back(*dc);

			}

			devices.push_back(*d);

			delete d;
	}

	return 0;
}
