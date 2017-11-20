#include "stdafx.h"
#include "lexical_cast_example.h"
#include "boost/lexical_cast.hpp"

// if cast ok
template <typename T>
bool num_valid(const char* pstr)
try
{
	boost::lexical_cast<T>(pstr);
	return true;
}
catch (boost::bad_lexical_cast e)
{
	return false;
}

template <typename TT>
class outable{
	friend std::ostream & operator<<(std::ostream &os, const TT& x){
		os << typeid(x).name();
		return os;
	}
};
class demo_class2 :public outable < demo_class2 > {};

void test_lexical_cast()
{
	int nTest = boost::lexical_cast<int>("2");
	std::string strTest = boost::lexical_cast<std::string>(nTest);
	float ftest = boost::lexical_cast<float>("2.1");
	std::string strf = boost::lexical_cast<std::string>(ftest);
	cout << nTest << " str " << strTest << endl;
	cout << ftest << " str " << strf << endl;

	try
	{
		cout << boost::lexical_cast<int>("hello world") << endl;
	}
	catch (boost::bad_lexical_cast e)
	{
		cout << e.what() << endl;
	}

	assert(num_valid<int>("123"));
	assert(num_valid<double>("3.14"));
	assert(num_valid<float>("0.15926"));

	cout << boost::lexical_cast<std::string>(demo_class2()) << endl;
}