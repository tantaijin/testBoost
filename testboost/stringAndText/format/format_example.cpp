#include "stdafx.h"
#include "format_example.h"
#include "boost/format.hpp"

void testFormat()
{
	cout << boost::format("%s %d %d")%"hello" % 1 % 2 << endl;

	boost::format fmt("%1%+%2%=%3%");
	fmt % 2 % 3 % (2 + 3);
	cout << fmt.str() << endl;
}
