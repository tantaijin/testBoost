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

typedef struct{
	int operator()(int x){
		return x*x;
	}
}demo_class3;

class demo_class_cb{
public:
	typedef boost::function<void(int)> func_type;

	func_type m_func;
	int n;
	demo_class_cb(int i) : n(i){}

	template <typename CallBack>
	void accept(CallBack b){
		m_func = b;
	}
	void run(){
		m_func(n);
	}
};

class callback_factory{
public:
	void callback_func1(int i){
		cout << "void callback_func1(int i) : " << i << endl;
	}
	void callback_func2(int i, int j){
		cout << "void callback_func1(int i, int j) : " << i << ","<< j << endl;
	}
};

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

	demo_class3 dc;
	boost::function<int(int)> func2;
	func2 = boost::ref(dc);
	cout << func2(2) << endl; // 4

	demo_class_cb dcc(10);
	callback_factory cbf;
	dcc.accept(boost::bind(&callback_factory::callback_func1, cbf, _1));
	dcc.run(); // void callback_func1(int i) : 10
	dcc.accept(boost::bind(&callback_factory::callback_func2, cbf, _1, 5));
	dcc.run(); // void callback_func1(int i, int j) : 10,5

}
