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
	cout << boost::to_upper_copy(strTest) << endl;
	cout << strTest << endl;
	boost::to_lower(strTest);
	cout << strTest << endl;
}
