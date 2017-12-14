#include "stdafx.h"
#include "anyExample.h"
#include "boost/any.hpp"
#include "boost/exception/diagnostic_information.hpp"

void test_any_example()
{
	boost::any a(10);
	int n = boost::any_cast<int>(a);
	cout << n << endl; // 10

	boost::any_cast<int&>(a) = 20;
	cout << boost::any_cast<int>(a) << endl; // 20

	try
	{
		boost::any a;
		boost::any_cast<int>(a);
	}
	catch (boost::exception&)
	{
		cout << boost::current_exception_diagnostic_information() << endl;
	}

	boost::any a1, a2(2);
	assert(boost::any_cast<int*>(&a1) == 0);
	assert(boost::any_cast<std::string *>(&a2) == 0);
	assert(boost::any_cast<int*>(&a2)==0);
}
