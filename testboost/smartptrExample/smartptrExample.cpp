#include "stdafx.h"
#include <vector>
#include "smartptrExample.h"
#include "boost\smart_ptr.hpp"

using namespace boost;

struct posix_file{
	posix_file(const char* pszfilename){
		cout << "open file " << pszfilename << endl;
	}
	~posix_file(){
		cout << "close file" << endl;
	}
};

void testscoped_Ptr()
{
	scoped_ptr<int> p(new int);
	if (p)
	{
		*p = 100;
		cout << *p << endl;
	}
	p.reset();
	assert(p == 0);
	if (!p)
	{
		scoped_ptr<posix_file> fp(new posix_file("1.txt"));
	}
	cout << "function end" << endl;
}

void testscoped_array()
{
	int *arr = new int[100];
	scoped_array<int> sa(arr); // not using anymore
	_Fill_n(&sa[0], 100, 5);
	sa[10] = sa[20] + sa[30];
	cout << sa[10] << endl;
}

/*
** 应用于桥接模式
*/
class Sample{
private:
	class Impl;
	boost::shared_ptr<Impl> m_p;

public:
	Sample();
	void print();
};

class Sample::Impl{
public:
	void print(){
		cout << "print of Impl" << endl;
	}
};

Sample::Sample(){
	m_p = boost::make_shared<Impl>();
}

void Sample::print(){
	m_p->print();
}

/*
** 应用于工厂模式
*/
class abstract
{
public:
	virtual void f() = 0;
	virtual void g() = 0;

protected:
	virtual ~abstract(){}
};

class Impl2 :public abstract{
public:
	void f(){ cout << "f()" << endl; }
	void g(){ cout << "g()" << endl; }
};

boost::shared_ptr<abstract> create(){
	return boost::shared_ptr<abstract>(boost::make_shared<Impl2>());
}

/*
** 高级用法
*/
void any_func(void *p){
	cout << "any func()" << endl;
}

void testshared_ptr()
{
	boost::shared_ptr<std::exception> sp1(new std::bad_exception("error"));
	boost::shared_ptr<std::bad_exception> sp2 = dynamic_pointer_cast<std::bad_exception>(sp1);
	boost::shared_ptr<std::exception> sp3 = static_pointer_cast<std::exception>(sp2);
	assert(sp3 == sp1);

	boost::shared_ptr<string> ssp(boost::make_shared<string>("make_shared test"));
	boost::shared_ptr<vector<int>> vsp(boost::make_shared<vector<int>>(10, 5));
	cout << "begin: " << *vsp->begin() << " size: " << vsp->size() << endl;

	{
		typedef vector<boost::shared_ptr<int>> vtype;
		vtype v(10);

		for (vtype::iterator iter = v.begin(); iter != v.end(); iter++)
		{
			*iter = boost::make_shared<int>(1);
			cout << *(*iter) << " ";
		}
		cout << endl;

		boost::shared_ptr<int> p = v[9];
		*p = 100;
		cout << *v[9] << endl;
	}

	/*
	** 桥接模式
	*/
	{
		Sample s;
		s.print();
	}
	/*
	** 工厂模式
	*/
	boost::shared_ptr<abstract> p = create();
	p->f();
	/*
	**删除器的用法
	*/
	FILE *hfile = nullptr;
	fopen_s(&hfile, "d:\\1.txt", "ab");
	boost::shared_ptr<FILE> spf(hfile, fclose);
	/*
	** 高级用法
	*/
	boost::shared_ptr<void> pf((void*)0, any_func);
}

void testshared_array()
{
	int *p = new int[10];
	boost::shared_array<int> sa(p);
	boost::shared_array<int> sa2 = sa;
	sa2[0] = 10;
	cout << "test shared_array: " << sa[0] << endl;
}

void testweak_ptr()
{
	boost::shared_ptr<int> sp(boost::make_shared<int>(10));
	boost::weak_ptr<int> wp(sp);
	assert(wp.use_count() == 1);

	if (!wp.expired()) // expired() <=> use_count()==0
	{
		boost::shared_ptr<int> sp2 = wp.lock(); //返回shared_ptr，不会影响计数
		*sp2 = 100;
		assert(wp.use_count() == 2);
	}
	assert(wp.use_count() == 1);
	cout << "test weak_ptr: " << *sp << endl;
	sp.reset();
	assert(wp.expired()); // expired()==true的时候lock返回存储空指针的shared_ptr对象
	assert(!wp.lock());
}