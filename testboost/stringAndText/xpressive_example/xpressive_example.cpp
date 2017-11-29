#include "stdafx.h"
#include "xpressive_example.h"
#include "boost/typeof/typeof.hpp"
#include "boost/xpressive/xpressive.hpp"

void test_xpressive_example()
{
	boost::xpressive::cregex regx = boost::xpressive::cregex::compile("a.c");

	assert(boost::xpressive::regex_match("abc", regx));
	assert(boost::xpressive::regex_match("axc", regx));
	assert(!boost::xpressive::regex_match("ac", regx));
	assert(!boost::xpressive::regex_match("abbc", regx));

	//\\d <= >[0-9] \w<=>[a-z] \s<=> (space)
	boost::xpressive::cregex regxsfz = boost::xpressive::cregex::compile("\\d{6}((1|2)\\d{3})((0|1)\\d)([0-3]\\d)(\\d{3}(x|\\d))", 
		boost::xpressive::icase); // icase  ingore case sentive
	assert(boost::xpressive::regex_match("36048119880228552x", regxsfz));

	boost::xpressive::cmatch xmt;
	boost::xpressive::regex_match("36048119880228552x", xmt, regxsfz);
	for (BOOST_AUTO(pos, xmt.begin()); pos != xmt.end(); ++pos)
	{
		cout << "[" << *pos << "]";
	}
	cout << endl;
	cout << "date: " << xmt[1] << xmt[3] << xmt[5] << endl;

	std::string strregcheck("readme.txt");
	boost::xpressive::cregex regstart = boost::xpressive::cregex::compile("^re.*");
	boost::xpressive::cregex regend = boost::xpressive::cregex::compile(".*txt$");
	assert(boost::xpressive::regex_match(strregcheck.c_str(), regstart));
	assert(boost::xpressive::regex_match(strregcheck.c_str(), regend));

	std::string strregsearch("this is a POWER-suit test");
	boost::xpressive::cregex regserch = boost::xpressive::cregex::compile("power-.{4}", boost::xpressive::icase);
	assert(boost::xpressive::regex_search(strregsearch.c_str(), regserch));
	boost::xpressive::cmatch cmt;
	boost::xpressive::regex_search(strregsearch.c_str(), cmt, regserch);
	cout << cmt[0] << endl;

	boost::xpressive::sregex sreg = boost::xpressive::sregex::compile("(.*)(me)");
	cout << boost::xpressive::regex_replace(strregcheck, sreg, "hello") << endl; // hello.txt
	cout << boost::xpressive::regex_replace(strregcheck, sreg, "$1you") << endl; // readyou.txt
	cout << boost::xpressive::regex_replace(strregcheck, sreg, "$&$&") << endl; // readmereadme.txt

	std::string strreplace("1234 hello world !!!");
	boost::xpressive::sregex sreg1 = boost::xpressive::sregex::compile("^(\\d| )*");
	boost::xpressive::sregex sreg2 = boost::xpressive::sregex::compile("!*$");
	cout << boost::xpressive::regex_replace(strreplace, sreg1, "") << endl; // trim_left hello world !!!
	cout << boost::xpressive::regex_replace(strreplace, sreg2, "") << endl; // trim_right 1234 hello world
	cout << boost::xpressive::regex_replace(strreplace, sreg1, "Y2000 ") << endl; // replace_all Y2000 hello world !!!

	/*
	** boost::xpressive::sregex_iterator
	*/
	std::string striter("power-suit, power-hell, power-world");
	boost::xpressive::sregex reg = boost::xpressive::sregex::compile("power-.{4}", boost::xpressive::icase);
	boost::xpressive::sregex_iterator regiter(striter.begin(), striter.end(), reg);
	boost::xpressive::sregex_iterator enditer;
	for (; regiter != enditer; ++regiter)
	{
		cout << "[" << (*regiter)[0] << "]";
	}
	cout << endl; // [power-suit][power-hell][power-worl]

	/*
	** boost::xpressive::sregex_token_iterator
	*/
	//boost::xpressive::sregex_token_iterator
	char* strtoken = "link*||hello||world||jk";
	boost::xpressive::cregex regtoken = boost::xpressive::cregex::compile("\\w+", boost::xpressive::icase);
	boost::xpressive::cregex_token_iterator pos(strtoken, strtoken + strlen(strtoken), regtoken);
	while (pos != boost::xpressive::cregex_token_iterator())
	{
		cout << "[" << (*pos) << "]";
		++pos;
	}
	cout << endl; // [link][hello][world][jk]

	boost::xpressive::cregex reg_split = boost::xpressive::cregex::compile("\\|\\|", boost::xpressive::icase);
	boost::xpressive::cregex_token_iterator pos_split(strtoken, strtoken + strlen(strtoken), reg_split, -1);
	while (pos_split != boost::xpressive::cregex_token_iterator())
	{
		cout << "[" << (*pos_split) << "]";
		++pos_split;
	}
	cout << endl; // [link*][hello][world][jk]
}
