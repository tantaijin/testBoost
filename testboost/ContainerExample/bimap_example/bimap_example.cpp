#include "stdafx.h"
#include "bimap_example.h"
#include "boost/bimap.hpp"
#include "boost/typeof/typeof.hpp"

void test_bimap()
{
	boost::bimap<int, std::string> bm;
	bm.left.insert(std::make_pair(1, "one"));
	bm.left.insert(std::make_pair(2, "two"));

	bm.right.insert(std::make_pair("three", 3));
	bm.right.insert(std::make_pair("four", 4));
	bm.right.insert(std::make_pair("teststring", 2)); // disable

	for (BOOST_AUTO(pos, bm.left.begin()); pos != bm.left.end(); ++pos)
	{
		cout << "[" << pos->first << ", " << pos->second << "] ";
	}
	cout << endl; // [1, one] [2, two] [3, three] [4, four]

	bm.insert(boost::bimap<int, std::string>::value_type(5, "five"));
	for (BOOST_AUTO(pos, bm.left.begin()); pos != bm.left.end(); ++pos)
	{
		cout << "[" << pos->first << ", " << pos->second << "] ";
	}
	cout << endl; // [1, one] [2, two] [3, three] [4, four] [5, five]
}
