#include "stdafx.h"
#include "signal_example.h"
#include "boost/signals2.hpp"

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
	void operator()(){
		cout << "slot " << N << endl;
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

	boost::signals2::signal<void()> sig2;
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
}
