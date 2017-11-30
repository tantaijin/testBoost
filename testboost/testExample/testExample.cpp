#include "stdafx.h"
#include "testExample.h"
#define BOOST_ENABLE_ASSERT_HANDLER
#include "boost/assert.hpp"
#include "boost/format.hpp"

namespace boost{
	// can be effective in release
	void assertion_failed(char const * expr, char const * function, char const * file, long line){
		boost::format fmt("user defined failed info:\n %s\n%s\n%s\n%d\n");
		fmt %expr%function%file%line;
		cout << fmt;
	}
};

void fun(int x)
{
	BOOST_ASSERT(x != 0 && "error drive by 0"); // only effective in debug

	//BOOST_STATIC_ASSERT(sizeof(int) == 1); // error C2338: sizeof(int) == 1
}

void testTest()
{
	fun(0);
	// test lib, need to learn
}
