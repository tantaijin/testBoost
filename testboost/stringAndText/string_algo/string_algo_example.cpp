#include "stdafx.h"
#include "string_algo_example.h"
#include "boost/algorithm/string.hpp"

void test_string_algo()
{
	string str("readme.txt");
	if (boost::ends_with(str, "txt"))
	{
		cout << boost::to_upper_copy(str) << endl;
		assert(boost::ends_with(str, "txt"));
	}

	boost::replace_first(str, "readme", "followme");
	cout << str << endl;

	std::vector<char> v(str.begin(), str.end());
	std::vector<char> v2(boost::to_upper_copy(boost::erase_first_copy(v, "txt")));
	for (size_t i = 0; i < v2.size(); ++i)
	{
		cout << v2[i];
	}
	cout << endl;


	// begin with i , not check case sentive
	// copy end, return copy
	// boost::to_upper  boost::to_upper_copy
	std::string strTest("I Known");
	cout << boost::to_upper_copy(strTest) << endl; // I KNOWN
	cout << strTest << endl; // I Known
	boost::to_lower(strTest);
	cout << strTest << endl; // i known
	cout << boost::istarts_with(strTest, "I") << endl; // 1
	cout << boost::starts_with(strTest, "I") << endl; // 0
	// starts_with ends_with contains equals lexicographical_compare(check if str1 < str2 by sequence of zidian)
	// all 
	cout << boost::all(strTest.substr(2,5), boost::is_lower()) << endl; // 1

	std::string str1("Hello");
	std::string	str2("hello");
	assert(!boost::is_equal()(str1, str2));

	std::string strFmt(" hello world! ");
	cout << boost::trim_copy(strFmt) << endl;
	cout << boost::trim_left_copy(strFmt) << endl;
	cout << boost::trim_right_copy(strFmt) << endl;
	/*
	hello world!
	hello world!
	hello world!
	*/
	std::string strFmt2("2017  hello world  123!!!");
	cout << boost::trim_copy_if(strFmt2, boost::is_digit()) << endl;
	cout << boost::trim_left_copy_if(strFmt2, boost::is_digit()) << endl;
	cout << boost::trim_right_copy_if(strFmt2, boost::is_punct()) << endl;
	cout << boost::trim_copy_if(strFmt2, boost::is_punct() || boost::is_digit()) << endl;
	/*
	hello world  123!!!
	hello world  123!!!
	2017  hello world  123
	hello world
	*/
}
