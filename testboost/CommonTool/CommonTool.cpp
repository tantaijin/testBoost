#include "stdafx.h"
#include <vector>
#include "boost/utility.hpp"
#include "boost/smart_ptr.hpp"
#include "boost/utility/in_place_factory.hpp"
#include "boost/assign.hpp"

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

#include "boost/serialization/singleton.hpp"
using boost::serialization::singleton;

class MySingleClass :public singleton < MySingleClass > {
public:
	void print(){ cout << "MySingleClass" << endl; }
	void print() const { cout << "MySingleClass const" << endl; }
};

#include "boost/logic/tribool.hpp"
BOOST_TRIBOOL_THIRD_STATE(unknown);
#include "boost/logic/tribool_io.hpp"

#include "boost/operators.hpp"

class MyPoint:public boost::less_than_comparable<MyPoint, boost::equality_comparable<MyPoint>>
{
public:
	MyPoint(int a = 0, int b = 0):x(a),y(b){}
	friend bool operator<(const MyPoint& p1, const MyPoint& p2)
	{
		return (p1.x < p2.x) && (p1.y < p2.y);
	}
	friend bool operator==(const MyPoint& p1, const MyPoint& p2)
	{
		return (p1.x == p2.x) && (p1.y == p2.y);
	}
private:
	int x;
	int y;
};

#include "boost/exception/all.hpp"
class MyException : virtual public std::exception, virtual public boost::exception
{
};

struct my_err{};

void thread_work(){
	boost::throw_exception(std::exception("thread test"));
}

#include "boost/config/suffix.hpp"

typedef struct Const_Test_{
	static const int v1 = 10;
	enum{
		v2 = 20,
	};
}CONTEST_TEST;
typedef struct Const_Test2_{
	BOOST_STATIC_CONSTANT(int, v1 = 10);
	BOOST_STATIC_CONSTANT(int, v2 = 20);
}CONTEST_TEST2;

//#include "boost/config/warning_disable.hpp" //disable warning 4996

#include "boost/utility/binary.hpp"

#include "boost/current_function.hpp"
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

	/*
	** boost::assign
	*/
	using namespace boost::assign; // only can effective on stl
	std::vector<int> vtest;
	vtest += 1, 2, 3, 5 * 6;
	push_back(v)(7)(9);

	std::list<std::string> ltest;
	push_front(ltest)("hello")("world");

	std::map<int, std::string> mapTest;
	mapTest += std::make_pair(1, "123"), std::make_pair(2, "456");

	std::vector <int> vT = list_of(1)(2)(3);
	std::set<std::string> ss = (list_of("123"), "456");
	std::map<int, std::string> mm = map_list_of(1, "1")(2, "2");

	// assign (repeat repeat_fun range)
	std::vector<int> vl = list_of(1).repeat(3, 2)(3); // 1 2 2 2 3
	std::multiset<int> ms;
	insert(ms).repeat_fun(5, &rand).repeat(2, 1)(3); // x x x x x 1 1 3
	std::deque<int> d;
	push_front(d).range(vl.begin(), vl.begin() + 5);
	// list_of
	std::vector<std::vector<int>> vlist = list_of(list_of(1)(2))( list_of(3)( 4));
	// ref_list_of  like list_of

	/*
	** boost::swap
	*/
	int a[10] = { 0 };
	int b[10] = { 5 };
	boost::swap(a, b);

	/*
	** boost::singleton
	*/
	MySingleClass::get_const_instance().print();
	MySingleClass::get_mutable_instance().print();

	/*
	** boost::tribool true,false, indeterminate(||true==true  &&false==false  else==indeterminate)
	*/
	boost::tribool tb;
	tb = boost::indeterminate;
	if (tb) {
		cout << "true" << endl;
	}
	if (!tb) {
		cout << "false" << endl;
	}
	if (boost::indeterminate(tb)) { // or unknown(tb)
		cout << "boost::indeterminate" << endl;
	}
	/*
	false 0
	true 1
	inderterminate 2
	*/
	cout << tb << endl; // need include  boost/logic/tribool_io.hpp


	/*
	** operator
	*/
	/*
	boost::equality_comparable //== => !=
	boost::less_than_comparable // < => > <= >=
	boost::addable				// += => +
	boost::subtractable			// -= => -
	boost::incrementable		// ++(pre) => (after)++
	boost::decrementable		// --pre) => (after)--
	boost::equivalent			// < => ==
	*/
	MyPoint p1(1, 1), p2(2, 2);
	assert(p1 < p2 && p1 <= p2 && p2 > p1 && p2 >= p1);
	assert(p1 != p2);

	//boost::totally_ordered = boost::equality_comparable + less_than_comparable;
	//boost::additive = boost::addable + boost::subtractable;
	//boost::arithmetic = boost::additive + boost::multiplicative;
	//boost::unit_steppable = boost::incrementable + boost::decrementable;

	typedef boost::error_info<struct tag_err_no, int> err_no;
	typedef boost::error_info<struct tag_err_str, std::string> err_str;

#define DEFINE_ERROR_INFO(name, type) boost::error_info<struct tag_##name type> name
	try
	{
		throw MyException() << err_no(10);
	}
	catch (MyException& e)
	{
		cout << *boost::get_error_info<err_no>(e) << endl;
		cout << e.what() << endl;
	}

	try
	{
		// enable_error_info throw the exception class (child of my_err and boost::exception)
		throw boost::enable_error_info(my_err()) << err_str("enable_error_info string error info");
		//boost::throw_exception() <==> throw boost::enable_error_info
	}
	catch (boost::exception& e) // must using boost::exception
	{
		cout << *boost::get_error_info<err_str>(e) << endl;
	}

	try
	{
		BOOST_THROW_EXCEPTION(std::logic_error("logic error"));
	}
	catch (boost::exception& e)
	{
		cout << boost::diagnostic_information(e) << endl;
	}

	// thread exception info
	try
	{
		thread_work();
	}
	catch (...)
	{
		boost::exception_ptr p = boost::current_exception();
		cout << boost::current_exception_diagnostic_information() << endl;
	}

	/*
	** 
	*/
	cout << BOOST_STRINGIZE(__LINE__) << endl; // line NO.
	int x2 = 255;
	cout << BOOST_STRINGIZE(x2) << endl; // x not 255
	/*
	typedef struct Const_Test_{
	static const int v1 = 10;
	enum{
	v2 = 20,
	};
	}CONTEST_TEST;

	typedef struct Const_Test2_{
	BOOST_STATIC_CONSTANT(int, v1 = 10);
	BOOST_STATIC_CONSTANT(int, v2 = 20);
	}CONTEST_TEST2;
	*/

	/*
	**
	*/
	cout << hex << showbase;
	cout << BOOST_BINARY(0110) << endl; // 0x6
	cout << BOOST_BINARY(01 0001 0001) << endl; //0x111
	cout << BOOST_BINARY_UL(0110) << endl; // 0x6
	cout << BOOST_BINARY_LL(0110) << endl; // 0x6

	cout << BOOST_CURRENT_FUNCTION << endl; // void __cdecl testCommonTool(void)
}