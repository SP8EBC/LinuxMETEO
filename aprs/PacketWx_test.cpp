/*
 * PacketWx_test.cpp
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */

#include "PacketWx.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PACKETWX
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(basic)
{
	AprsPacketWx* p;
	AprsCall s("nocall", 1), d("nocall", 10);

	p = new AprsPacketWx(&s, &d, 120, 2.0f, 5.0f, 15.0f, 50, 1013, 1000);

	string o = p->toString();

	BOOST_CHECK( o == "" );
}
