#include "stdafx.h"
#include "crc_test.h"

#include "boost\crc.hpp"

void test_crc()
{
	boost::crc_32_type c3t;

	cout << hex;
	cout << c3t.checksum() << endl; //0

	c3t.process_byte(5);
	cout << c3t.checksum() << endl; //	a2681b02
	
	c3t.reset();
	c3t.process_byte(5);
	cout << c3t.checksum() << endl; //	a2681b02

	c3t.reset();
	c3t.process_bytes("1234567890", 10);
	cout << c3t.checksum() << endl; //	261daee5

	char szCh[] = "1234567890";
	c3t.reset();
	c3t.process_block(szCh, szCh+10);
	cout << c3t.checksum() << endl; //	261daee5	
}
