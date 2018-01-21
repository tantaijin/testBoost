#include "stdafx.h"
#include "number_test.h"
#include "boost\integer_traits.hpp"

#include "boost\cstdint.hpp"

void test_integer()
{
	cout << boost::integer_traits<int>::const_min << endl; // -2147483648
	cout << boost::integer_traits<int>::const_max << endl; // 2147483647
	cout << boost::integer_traits<int>::is_signed << endl; // 1

	boost::int8_t a = 1;
	boost::int16_t b = 2;
	boost::int32_t c = 3;
	boost::int64_t d = 4;
	cout << (int)a << " " << b << " " << c << " " << d << " " << endl; // 1 2 3 4

	boost::int_fast16_t aa = 1;
	boost::int_fast32_t bb = 2;
	boost::int_fast64_t cc = 3;

	boost::int_least16_t aaa = 1;
	boost::int_least32_t bbb = 2;
	boost::int_least64_t ccc =3;
}
