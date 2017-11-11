#include "stdafx.h"
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

void testshared_ptr()
{
	boost::shared_ptr<std::exception> sp1(new std::bad_exception("error"));
	boost::shared_ptr<std::bad_exception> sp2 = dynamic_pointer_cast<std::bad_exception>(sp1);
	boost::shared_ptr<std::exception> sp3 = static_pointer_cast<std::exception>(sp2);
	assert(sp3 == sp1);
}