#include "stdafx.h"
#include "variant_example.h"
#include "boost/variant.hpp"

struct var_print :public boost::static_visitor < > {
	template <typename T>
	void operator()(T &i) const{
		i *= 2;
		cout << i << endl;
	}
};

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

	typedef boost::variant<int, double> var_t2;
	var_t2 v3;
	v3 = 1;
	var_print vp;
	boost::apply_visitor(vp, v3); // 2
	v3 = 2.3;
	boost::apply_visitor(vp, v3); // 4.6
}
