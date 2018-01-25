#include "stdafx.h"
#include "result_of_example.h"
#include "boost\utility\result_of.hpp"
#include "boost\typeof\typeof.hpp"

template <typename T, typename T1>
typename boost::result_of<T(T1)>::type call_func(T t, T1 t1) {
	return t(t1);
}

void test_result_of()
{
	typedef double (*FuncType)(double d);
	boost::result_of<FuncType(double)>::type x;
	cout << typeid(x).name() << endl; // double

	FuncType func = sqrt;
	BOOST_AUTO(x2, call_func(func, 5.0));
	cout << typeid(x2).name() << endl; // double
}
