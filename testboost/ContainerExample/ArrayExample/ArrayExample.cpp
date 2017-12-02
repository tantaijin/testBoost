#include "stdafx.h"
#include "ArrayExample.h"
#include "boost/array.hpp"
#include "boost/typeof/typeof.hpp"
#include "boost/dynamic_bitset.hpp"
#include "boost/utility/binary.hpp"

void TestArray()
{
	boost::array<std::string, 5> arrStr;
	arrStr.assign("1");

	for (BOOST_AUTO(pos, arrStr.begin()); pos != arrStr.end(); ++pos)
	{
		cout << pos->c_str() << " ";
	}
	cout << endl;

	boost::dynamic_bitset<> db1;
	boost::dynamic_bitset<> db2(10);
	boost::dynamic_bitset<> db3(8, BOOST_BINARY(01001));
	boost::dynamic_bitset<> db4(std::string("01001"));
	boost::dynamic_bitset<> db5(db4);
	
	cout << "db3: " << db3.to_ulong() << endl; // db3: 0x9
	db3.push_back(true);
	cout << "db3: " << db3.to_ulong() << endl; // db3: 0x10009 if db3==16
	cout << "db3: " << db3.to_ulong() << endl; // db3: 0x109 if db3 == 8

	db3[1] |= 1;
	cout << "db3: " << db3.to_ulong() << endl; // db3: 0x10b if db3 == 8
}
