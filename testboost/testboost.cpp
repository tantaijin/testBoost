// testboost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dateExample\dateExample.h"
#include "timeExample\timeExample.h"
#include "smartptrExample\smartptrExample.h"
#include "poolExample\poolExample.h"
#include "CommonTool\CommonTool.h"
#include "stringAndText\lexical_cast_example\lexical_cast_example.h"
#include "stringAndText\format\format_example.h"
#include "stringAndText\string_algo\string_algo_example.h"
#include "stringAndText\xpressive_example\xpressive_example.h"
#include "testExample\testExample.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//testDate();
	//testTime();
	testscoped_Ptr();
	testscoped_array();
	testshared_ptr();
	testshared_array();
	testweak_ptr();
	testpool();
	testCommonTool();
	test_lexical_cast();
	testFormat();
	test_string_algo();
	test_xpressive_example();
	testTest();
	return 0;
}

