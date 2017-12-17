#include "stdafx.h"
#include "anyExample.h"
#include "boost/any.hpp"
#include "boost/assign/list_of.hpp"
#include "boost/exception/diagnostic_information.hpp"

template <typename T>
bool can_cast(boost::any& a){
	return typeid(T) == a.type();
}

template <typename T>
T &get(boost::any &a)
{
	BOOST_ASSERT(can_cast<T>(a));
	return *boost::any_cast<T>(&a);
}

template <typename T>
T *get_pointer(boost::any& a)
{
	BOOST_ASSERT(can_cast<T>(a));
	return boost::any_cast<T>(&a);
}

template <typename T>
boost::any make_ptr_any(T* p = 0)
{
	return boost::any(boost::shared_ptr<T>(p));
}

template <typename T> struct any_print;
template <typename T> struct any_print < boost::shared_ptr<T> >
{
	void operator()(boost::any &a){
		cout << **boost::any_cast<boost::shared_ptr<T>>(&a) << endl;
	}
};

void test_any_example()
{
	boost::any a(10);
	int n = boost::any_cast<int>(a);
	cout << n << endl; // 10

	boost::any_cast<int&>(a) = 20;
	cout << boost::any_cast<int>(a) << endl; // 20

	try
	{
		boost::any a;
		boost::any_cast<int>(a);
	}
	catch (boost::exception&)
	{
		cout << boost::current_exception_diagnostic_information() << endl;
	}

	boost::any a1, a2(2);
	assert(boost::any_cast<int*>(&a1) == 0);
	assert(boost::any_cast<std::string *>(&a2) == 0);
	assert(boost::any_cast<int*>(&a2)==0);

	boost::any a3(100);
	a3 = std::string("hello world");

	boost::any an;
	int x = 1;
	an = x;
	get<int>(an) = 10;
	assert( boost::any_cast<int>(an) == 10);
	*get_pointer<int>(an) = 20;
	assert(boost::any_cast<int>(an) == 20);

	boost::any a5 = make_ptr_any<int>(new int(5));
	assert(*boost::any_cast<boost::shared_ptr<int>>(a5) == 5);

	std::vector<boost::any> v;
	v.push_back(1);
	v.push_back(std::string("123"));
	v.push_back(boost::shared_ptr<int>(new int(5)));
	assert(v.size() == 3);

	std::vector<boost::any> v2;
	v2 = boost::assign::list_of<boost::any>(1)(2)(std::string("3"));
	assert(v.size() == 3);

	boost::any a6(123);
	//any_print<int>(a6);
}
