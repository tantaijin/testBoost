#include "stdafx.h"
#include <numeric>
#include "signal_example.h"
#include "boost/signals2.hpp"
#include "boost\typeof\typeof.hpp"

void slot1(){
	cout << "slot1" << endl;
}

void slot2(){
	cout << "slot2" << endl;
}

void slot3(){
	cout << "slot3" << endl;
}

template <int N>
class slots{
public:
	int operator()(){
		cout << "slot " << N << endl;
		return N;
	}
};

template <typename T>
class combiner{
	T v;
public:
	typedef std::pair<T, T> result_type;
	combiner(T t = T()) :v(t){}
	template <typename InputIterator>
	result_type operator()(InputIterator begin, InputIterator end) {
		if (begin == end) {
			return result_type();
		}
		std::vector<T> vec(begin, end);
		T sum = std::accumulate(vec.begin(), vec.end(), v);
		T max = *std::max_element(vec.begin(), vec.end());

		return result_type(sum, max);
	}
};

void test_signal()
{
	boost::signals2::signal<void()> sig;
	sig.connect(&slot1);
	sig.connect(&slot2);
	sig.connect(&slot3, boost::signals2::at_front);
	sig();
	/*
	slot3
	slot1
	slot2
	*/

	boost::signals2::signal<int()> sig2;
	sig2.connect(slots<1>(), boost::signals2::at_back);
	sig2.connect(5, slots<51>(), boost::signals2::at_front);
	sig2.connect(5, slots<52>(), boost::signals2::at_front);
	sig2.connect(3, slots<31>(), boost::signals2::at_front);
	sig2.connect(3, slots<32>(), boost::signals2::at_back);
	sig2();
	/*
	slot 31
	slot 32
	slot 52
	slot 51
	slot 1
	*/

	boost::signals2::signal<int()> sig3;
	sig3.connect(slots<1>());
	sig3.connect(slots<2>());
	sig3.connect(slots<3>());
	sig3.connect(slots<4>());
	cout << "result is :" << *sig3() << endl;
	/*
	slot 1
	slot 2
	slot 3
	slot 4
	result is :4
	*/

	boost::signals2::signal<int(), combiner<int>> sig4;
	sig4.connect(slots<5>());
	sig4.connect(slots<6>());
	sig4.connect(slots<7>());

	BOOST_AUTO(x, sig4());
	cout << x.first << " - " << x.second << endl;
	/*
	slot 5
	slot 6
	slot 7
	18 - 7
	*/

	boost::signals2::signal<int()> sig5;
	assert(sig5.empty());
	sig5.connect(0, slots<11>());
	sig5.connect(0, slots<12>());
	sig5.connect(1, slots<13>());
	assert(sig5.num_slots() == 3);
	sig5.disconnect(0);
	assert(sig5.num_slots() == 1);
	//sig5.disconnect(slots<13>()); // can't build
	//assert(sig5.num_slots() == 0);
}
