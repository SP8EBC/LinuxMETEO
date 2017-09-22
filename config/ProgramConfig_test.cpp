/*
 * ProgramConfig_test.cpp
 *
 *  Created on: 12.09.2017
 *      Author: mateusz
 */

#include "ProgramConfig.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PROGRAMCONFIG
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(basic)
{
	ProgramConfig::readConfigFromFile();
	BOOST_CHECK( ProgramConfig::getOutputAprxFile() == "output.txt" );
	BOOST_CHECK( ProgramConfig::getDevicesNumber() == 1);
}
