#include "stdafx.h"
#include "variant_example.h"
#include "boost/variant.hpp"

void test_variant_example()
{
	boost::variant<int, float, std::string> v;
	v = "123";
	cout << boost::get<std::string>(v) << endl;

	typedef boost::variant<int, double, std::string> var_t;
	var_t v2;
	assert(v2.type() == typeid(int));
	assert(v2.which() == 0);

	v2 = "variant string";
	cout << boost::get<std::string>(v2) << endl; // variant string
	cout << *boost::get<std::string>(&v2) << endl; // variant string
}
