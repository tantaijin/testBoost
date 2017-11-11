// testboost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dateExample\dateExample.h"
#include "timeExample\timeExample.h"
#include "smartptrExample\smartptrExample.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//testDate();
	//testTime();
	testscoped_Ptr();
	testscoped_array();
	testshared_ptr();
	return 0;
}

