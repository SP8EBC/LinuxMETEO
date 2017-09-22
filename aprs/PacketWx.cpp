/*
 * PacketWx.cpp
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */

#include <cstdio>

#include "PacketWx.h"
#include "PacketFoundation.h"
#include "Call.h"
#include "../config/ProgramConfig.h"

AprsPacketWx::AprsPacketWx(AprsCall* s, AprsCall* d, unsigned short _direction,
												   float _windspeed,
												   float _gusts,
												   float _temperature,
												   unsigned char _humidity,
												   unsigned short _qnh,
												   unsigned short _qfe)
												   :
												   AprsPacketFoundation(s, d),
												   direction(_direction),
												   windspeed(_windspeed),
												   gusts(_gusts),
												   temperature(_temperature),
												   humidity(_humidity),
												   qnh(_qnh),
												   qfe(_qfe){
	// TODO Auto-generated constructor stub
}

AprsPacketWx::~AprsPacketWx() {
	// TODO Auto-generated destructor stub
}

string AprsPacketWx::toString() {
	string* out;
	char cout[190];

	float max_wind_speed = 0.0, temp;
	unsigned char wind_speed_mph, wind_gusts_mph;
	max_wind_speed = this->gusts * 0.1f;		// Wyszukiwane najwiekszej wartosci
	temp = this->windspeed;
	temp /= 0.45;																						// Konwersja na mile na godzine
	max_wind_speed /= 0.45;
	if ((temp - (short)temp) >= 0.5)												// Zaokraglanie wartosci
		/* Odejmuje od wartosci zmiennoprzecinkowej w milach nad godzine wartosc
			 po zrzutowaniu na typ short czyli z odcienta czescia po przecinku.
			 Jezeli wynik jest wiekszy albo rowny 0.5 to trzeba zaokraglic w gore */
		wind_speed_mph = (short)temp + 1;
	else
		/* A jezeli jest mniejsza niz 0.5 to zaokraglamy w dol */
		wind_speed_mph = (short)temp;
	if ((max_wind_speed - (short)max_wind_speed) >= 0.5)
		/* Analogiczna procedura ma miejsce dla porywow wiatru*/
		wind_gusts_mph = (short)max_wind_speed + 1;
	else
		wind_gusts_mph = (short)max_wind_speed;
	sprintf(cout, "!%s%s%c%s%s%c%03d/%03dg%03dt%03dr...p...P...b%05d",
							ProgramConfig::getLat().c_str(),
							ProgramConfig::getLatns().c_str(),
							'/',
							ProgramConfig::getLon().c_str(),
							ProgramConfig::getLonwe().c_str(),
							'_',
							/* kierunek */(short)(this->direction),
							/* predkosc*/(int)wind_speed_mph,
							/* porywy */(short)(wind_gusts_mph),
							/*temperatura */(short)(this->temperature*1.8+32),
							qnh *10);

	out = new string(cout);

	return *out;
}

