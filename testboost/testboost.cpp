// testboost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "boost\timer.hpp"
#include "boost\progress.hpp"

//using namespace boost;
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

#include "boost/static_assert.hpp"

//#define BOOST_DATE_TIME_SOURCE
//#define BOOST_DATE_TIME_NOL_LIB
//#include "boost\date_time\gregorian\greg_date.hpp"
#include "boost\date_time.hpp"

//using namespace boost::gregorian;

int _tmain(int argc, _TCHAR* argv[])
{
	/*  timer */
	boost::timer t;
	std::cout << "max timespan:" << t.elapsed_max() / 3600 << "h" << std::endl;
	std::cout << "min timespan:" << t.elapsed_min() << "s" << std::endl;
	std::cout << "now time elapsed:" << t.elapsed() << "s" << std::endl;

	/*  progress */
	std::vector<std::string> v(100);
	std::ofstream f("d:\\1.txt");
	boost::progress_display pd(v.size());
	std::vector<std::string>::iterator iter;
	for (iter = v.begin(); iter != v.end(); ++iter)
	{
		f << *iter << std::endl;
		++pd;
	}

	/*  date */
	boost::gregorian::date d1(2005,9,1);
	boost::gregorian::date d2(2017,11,5);
	boost::gregorian::date d3(boost::gregorian::neg_infin);
	std::cout << d1 << std::endl;
	std::cout << d2 << std::endl;
	std::cout << to_simple_string(d2) << std::endl;
	std::cout << d3 << std::endl;
	tm t2 = to_tm(d2);
	boost::gregorian::date d4 = boost::gregorian::date_from_tm(t2);
	std::cout << d4 << std::endl;
	/* years months days*/
	d2 += boost::gregorian::years(1);
	std::cout << d2 << std::endl;
	d2 += boost::gregorian::months(1);
	std::cout << d2 << std::endl;
	d2 += boost::gregorian::days(1);
	std::cout << d2 << std::endl;
	/*date_period*/
	boost::gregorian::date_period dp(d1, boost::gregorian::days(20));
	std::cout << dp << " " << dp.begin() << std::endl;
	assert(dp.is_after(boost::gregorian::date(2004, 9, 1)));
	assert(dp.is_before(boost::gregorian::date(2006, 9, 1)));
	assert(dp.contains(boost::gregorian::date(2005, 9, 2)));
	boost::gregorian::date_period dp2(boost::gregorian::date(2007,9,1), boost::gregorian::days(20));
	assert(dp.merge(dp2).is_null());
	assert(dp.span(dp2).end() == dp2.end());
	/* iterator*/
	boost::gregorian::day_iterator di(boost::gregorian::date(2017, 1, 1), 2); // month_iterator year_iterator
	++di;
	std::cout << *di << std::endl;
	boost::gregorian::gregorian_calendar gd;
	std::cout << gd.is_leap_year(2012) << std::endl;

	return 0;
}

