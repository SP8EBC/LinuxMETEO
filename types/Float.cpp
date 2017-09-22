/*
 * Float.cpp
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#include "Float.h"
#include "../aux/UnitsConversionMatrix.h"

#include <sstream>
#include <cstdio>

const string Float::type = "float";

Float::Float() {
	// TODO Auto-generated constructor stub
	value = &this->store;

}

Float::~Float() {
	// TODO Auto-generated destructor stub
}

string Float::getType() {
	return Float::type;
}

string Float::toAprsConvertedString(MeasurementUnit &from, MeasurementUnit &to) {
	float output = this->store * UnitsConversionMatrix::conversionMatrix[to][from];
	char s[4] = {0, 0, 0, 0};

	sprintf(s, "%03d", (int)output);

	string o(s);

	return o;
}

float Float::getValue() const {
	return store;
}

void Float::setValue(float store) {
	this->store = store;
}

string Float::toString() {
	stringstream out;
	out << this->store;

	return out.str();

}
