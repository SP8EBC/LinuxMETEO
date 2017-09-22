/*
 * Integer.cpp
 *
 *  Created on: 16.09.2017
 *      Author: mateusz
 */

#include "Integer.h"
#include "../aux/UnitsConversionMatrix.h"

#include <sstream>
#include <cstdio>

using namespace std;

const string Integer::type = "int";

Integer::Integer(){
	// TODO Auto-generated constructor stub
	value = &this->store;
}

Integer::~Integer() {
	// TODO Auto-generated destructor stub
}

string Integer::getType() {
	return Integer::type;
}

string Integer::toAprsConvertedString(MeasurementUnit &from, MeasurementUnit &to) {
	float output = (float)this->store * UnitsConversionMatrix::conversionMatrix[to][from];
	char s[4] = {0, 0, 0, 0};

	sprintf(s, "%03d", (int)output);

	string o(s);

	return o;
}

int Integer::getValue() const {
	return store;
}

void Integer::setValue(int store) {
	this->store = store;
}

string Integer::toString() {
	stringstream out;
	out << this->store;

	return out.str();

}

