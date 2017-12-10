#include "stdafx.h"
#include "circular_buffer_example.h"
#include "boost/circular_buffer.hpp"
#include "boost/typeof/typeof.hpp"

template<typename T>
void print_stl(T &x)
{
	for (BOOST_AUTO(pos, x.begin()); pos != x.end(); ++pos)
	{
		cout << *pos << " ";
	}
	cout << endl;
}

void test_circular_buffer_example()
{
	boost::circular_buffer<int> cb(5);
	assert(cb.empty());

	cb.push_back(1);
	cb.push_front(2);
	cb.insert(cb.begin(), 3);
	print_stl(cb); // 3 2 1

	cb.pop_back();
	print_stl(cb); // 3 2
	cb.push_back(4);
	cb.push_back(5);
	cb.push_back(6);
	print_stl(cb); // 3 2 4 5 6
	cb.push_back(7);
	print_stl(cb); // 2 4 5 6 7
	cb.push_front(8);
	print_stl(cb); // 8 2 4 5 6
}
