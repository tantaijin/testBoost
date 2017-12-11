#include "stdafx.h"
#include "tuple_example.h"
#include "boost/typeof/typeof.hpp"
#include "boost/assign.hpp"
#include "boost/tuple/tuple.hpp"

void test_tuple_example()
{
	boost::tuple<int, double> tp;
	tp = boost::make_tuple(1, 100.00);
	assert(tp.get<0>() == 1);
	cout << tp.get<0>() << endl; // 1
	cout << tp.get<1>() << endl; // 100
	cout << boost::get<0>(tp) << endl; // 1
}
