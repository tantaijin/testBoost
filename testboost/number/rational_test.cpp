#include "stdafx.h"
#include "rational_test.h"
#include "boost\rational.hpp"

void test_rational()
{
	boost::rational<int> pi(22, 7);
	cout << pi << endl;// 22/7
}
