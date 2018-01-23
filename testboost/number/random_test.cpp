#include "stdafx.h"
#include "random_test.h"

#include <ctime>
#include "boost/random.hpp"

void test_random()
{
	boost::mt19937 mrand(time(0));
	for (int i = 0; i < 100; ++i)
	{
		cout << mrand() << endl;
	}
}
