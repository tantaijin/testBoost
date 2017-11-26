#include "stdafx.h"
#include "xpressive_example.h"
#include "boost/xpressive/xpressive.hpp"

void test_xpressive_example()
{
	boost::xpressive::cregex regx = boost::xpressive::cregex::compile("a.c");

	assert(boost::xpressive::regex_match("abc", regx));
	assert(boost::xpressive::regex_match("axc", regx));
	assert(!boost::xpressive::regex_match("ac", regx));
	assert(!boost::xpressive::regex_match("abbc", regx));

	//\\d <= >[0-9] \w<=>[a-z] \s<=> (space)
	boost::xpressive::cregex regxsfz = boost::xpressive::cregex::compile("\\d{6}(1|2)\\d{3}(0|1)\\d[0-3]\\d\\d{3}(x|\\d)", 
		boost::xpressive::icase); // icase  ingore case sentive
	assert(boost::xpressive::regex_match("36048119880228552x", regxsfz));
}
