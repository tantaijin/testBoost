#include "stdafx.h"
#include <vector>
#include "boost/utility.hpp"
#include "boost/smart_ptr.hpp"
#include "boost/utility/in_place_factory.hpp"

class MyClass:public boost::noncopyable
{
public:
	void test(){}
};

std::vector<int> func(){
	std::vector<int> v(10);
	return v;
}

/*
** how to register BOOST_TYPEOF BOOST_AUTO
*/
#include "boost/typeof/typeof.hpp"
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

namespace ex{
	struct demo_cl
	{
		int a;
		int b;
	};
}
BOOST_TYPEOF_REGISTER_TYPE(ex::demo_cl);

#define auto_t BOOST_AUTO

#include "boost/optional.hpp"
boost::optional<double> calc(double x){
	return boost::optional<double>(x != 0, x / 10);
}

boost::optional<double> sqrt_op(double x){
	return boost::optional<double>(x > 0, sqrt(x));
}

void testCommonTool()
{
	/*
	** boost::noncopyable
	*/
	MyClass mc;
	mc.test();
	//MyClass mc2 = mc; // error

	/*
	** BOOST_TYPEOF BOOST_AUTO
	*/
	BOOST_TYPEOF(2 * 3) nTest = 2 * 3; // nTest is int
	BOOST_AUTO(nType, 2 * 3); // nType is int
	BOOST_AUTO(v, func()); // v is std::vector<int>
	BOOST_AUTO(p, std::make_pair(1, L"str")); // p is pair<int, string>
	cout << nType << endl;

	BOOST_AUTO(x, make_pair("test", ex::demo_cl()));
	cout << typeid(x).name() << endl;
	x.second.a = 20;
	cout << x.second.a << endl;
	auto_t(y, boost::make_shared<int>(10));
	cout << "*y = " << *y << endl;

	/*
	** optional
	*/
	boost::optional<int> op0;
	boost::optional<int> op1(boost::none);
	assert(op0 == op1 && !op0 && !op1);
	assert(op0.get_value_or(253) == 253);

	boost::optional<std::string> ops("string");
	cout << *ops << endl;

	std::vector<int> v2(10);
	boost::optional<std::vector<int>> optv(v2);
	optv->push_back(1);
	cout << optv->size() << endl;

	optv = boost::none;
	assert(!optv);

	boost::optional<double> ret = calc(1.0);
	if (ret){
		cout << "calc: " << *ret << endl;
	}
	ret = sqrt_op(-1);
	if (ret){
		cout << *ret << endl;
	}
	else{
		cout << "no result" << endl;
	}
	// make_optional
	boost::optional<int> opm = boost::make_optional(5);
	cout << "make_optional :" << *opm << endl;

	auto_t(opmd, boost::make_optional(1.2)); // make_optional buneng yong zai yingyong(&)
	auto_t(opmd2, boost::make_optional<double>(1.2));
	cout << "make_optional :" << *opmd2 << endl;
	auto_t(opmd3, boost::make_optional<double>(*opm > 5, 1.2));
	assert(!opmd3);

	boost::optional<string> opstr(boost::in_place("hello")); // no temp value
	cout << *opstr << endl;
}