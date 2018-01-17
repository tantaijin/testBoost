#include "stdafx.h"
#include "boost\foreach.hpp"
#include "boost\assign.hpp"

#include "boost\algorithm\minmax.hpp"
#include "boost\algorithm\minmax_element.hpp"

#include "boost/typeof/typeof.hpp"

void test_suanfa()
{
	std::vector<int> v = (boost::assign::list_of(1), 2, 3, 4);
	BOOST_FOREACH(int x, v)
	{
		cout << ++x << " ";
	}
	cout << endl; // 2 3 4 5

	boost::tuple<int, int> t = boost::minmax(2, 3);
	cout << t.get<1>() << " " << t.get<0>() << endl; // 3 2

	BOOST_AUTO(x2, boost::minmax_element(v.begin(), v.end()));
	cout << "min: " << *x2.first << endl; // min: 1
	cout << "max: " << *x2.second << endl; // max: 4
}
