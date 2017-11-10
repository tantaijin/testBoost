#include "stdafx.h"
#include "timeExample.h"
#include "boost\date_time.hpp"

using namespace boost::posix_time;
using namespace boost::gregorian;

void testTime()
{
	time_duration td(1, 2, 3, 1000); // hour, minute, second, microsecond (¦Ìs)  1 millisec second = 1000us
	cout << td << endl; // 01:02:03.001000
	cout << to_simple_string(td) << endl;
	cout << to_iso_string(td) << endl;

	hours h1(1);
	minutes m2(2);
	seconds s3(3);
	millisec m4(1);
	time_duration td2 = h1 + m2 + s3 + m4;
	cout << td2 << endl; // 01:02:03.001000

	time_duration td3(not_a_date_time);
	assert(td3.is_special() && td3.is_not_a_date_time());

	time_duration td4(neg_infin);
	assert(td4.is_negative()); // is small than 0

	cout << "unit: " << time_duration::unit() << endl;

	time_duration::tick_type my_millisec = time_duration::ticks_per_second() / 1000; // 1ms
	time_duration td5(1, 2, 3, 10 * my_millisec); // 10ms
	cout << "tick: " << td5 << endl;

	ptime pt(date(2017, 11, 10), hours(1));
	cout << pt << endl;
	ptime p1 = second_clock::local_time(); // local time
	ptime p2 = microsec_clock::universal_time(); // utc time
	cout << p1 << endl << p2 << endl;

	ptime p3(not_a_date_time);
	assert(p3.is_not_a_date_time());
	ptime p4(pos_infin); // or neg_infin
	assert(p4.is_special() && p4.is_infinity());
}