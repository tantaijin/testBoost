#include "stdafx.h"
#include "bind_and_function_example.h"
#include "boost\bind.hpp"
#include "boost\function.hpp"

int sum_func(int a, int b){
	return a + b;
}

typedef struct {
	int sum(int x, int y){ return x + y; }
}test_demo_struct;

void test_bind()
{
	cout << boost::bind(sum_func, 1, 2)() << endl; // 3
	cout << boost::bind(sum_func, _1, _2)(3, 4) << endl; // 7

	test_demo_struct d;
	test_demo_struct *p = &d;
	cout << boost::bind(&test_demo_struct::sum, d, 1, 2)() << endl; // 3
	cout << boost::bind(&test_demo_struct::sum, p, _1, 4)(3) << endl; // 7

	boost::function<int(int, int)> func;
	assert(!func);
	func = sum_func;
	if (func)
	{
		cout << func(1, 2) << endl; // 3
	}
	func = 0;
	assert(func.empty());

	boost::function<int(test_demo_struct&, int, int)> funcmem;
	//funcmem = &test_demo_struct::sum;
	funcmem = boost::bind(&test_demo_struct::sum, _1, _2, _3);
	cout << funcmem(d, 1, 2) << endl; // 3

	boost::function<int(int, int)> funcmem2;
	funcmem2 = boost::bind(&test_demo_struct::sum, &d, _1, _2);
	cout << funcmem2(1, 2) << endl; // 3
}
