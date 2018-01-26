#include "stdafx.h"
#include "ref_example.h"
#include "boost\ref.hpp"

#include "assert.h"

void test_ref()
{
	int x = 10;
	boost::reference_wrapper<int> rw(x);
	assert(rw == x);
	(int&)rw = 100;
	assert(x == 100);

	boost::reference_wrapper<int> rw2(rw);
	assert(rw2 == 100);

	std::string str;
	boost::reference_wrapper<std::string> rws(str);
	*rws.get_pointer() = "hello world";
	cout << rws.get().c_str() << endl;
}
