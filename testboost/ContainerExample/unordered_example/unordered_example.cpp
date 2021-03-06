#include "stdafx.h"
#include "unordered_example.h"
#include "boost/assign/list_of.hpp"
#include "boost/unordered_set.hpp"
#include "boost/unordered_map.hpp"
#include "boost/typeof/typeof.hpp"

template <typename T>
void HashFunc(){
	T s = (boost::assign::list_of(1), 3, 2, 4, 5, 1);
	for (T::iterator iter = s.begin(); iter != s.end(); ++iter)
	{
		cout << *iter << " ";
	} // 1 3 2 4 5
	cout << endl;
	cout << s.size() << " " << s.empty() << endl; // 5 0
}

// unordered support c++ self type and most stl type, not support userdefined type
// if want to support , can do this
struct demo_class_unor{
	bool operator == (const demo_class_unor& th){
		return a == th.a;
	}
	int a;
};
size_t hash_vale(const demo_class_unor& dcu)
{
	return boost::hash<int>()(dcu.a);
}

void test_unordered()
{
	HashFunc<boost::unordered_set<int>>();

	boost::unordered_map<int, std::string> um(boost::assign::map_list_of(1, "one")(2, "two")(3, "three"));
	um.insert(std::make_pair(10, "ten"));
	um[4] = "for";

	for (BOOST_AUTO(pos, um.begin()); pos != um.end(); ++pos)
	{
		cout << "[" << pos->first << ", " << pos->second << "] ";
	}
	cout << endl; //[4, for] [10, ten] [1, one] [2, two] [3, three]
	um.erase(10);
	for (BOOST_AUTO(pos, um.begin()); pos != um.end(); ++pos)
	{
		cout << "[" << pos->first << ", " << pos->second << "] ";
	}
	cout << endl; //[4, for] [1, one] [2, two] [3, three]

	boost::unordered_set<demo_class_unor> us;
}
