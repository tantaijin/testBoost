#include "stdafx.h"
#include "variant_example.h"
#include "boost/variant.hpp"

void test_variant_example()
{
	boost::variant<int, float, std::string> v;
	v = "123";
	cout << boost::get<std::string>(v) << endl;
}
