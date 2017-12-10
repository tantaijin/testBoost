#include "stdafx.h"
#include "bimap_example.h"
#include "boost/bimap.hpp"
#include "boost/assign.hpp"
#include "boost/assign/list_of.hpp"
#include "boost/typeof/typeof.hpp"
#include "boost/bimap/unordered_set_of.hpp"
#include "boost/bimap/multiset_of.hpp"
#include "boost/bimap/list_of.hpp"
#include "boost/bimap/unconstrained_set_of.hpp"
#include "boost/bimap/vector_of.hpp"
#include "boost/bimap/support/lambda.hpp"

template<typename T>
void print_map(T &m){
	for (BOOST_AUTO(pos, m.begin()); pos != m.end(); ++pos) // not pos = m.begin()
	{
		cout << pos->first << "<-->" << pos->second << endl;
	}
}

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

	//boost::bimap<int, boost::bimaps::unordered_set_of<std::string>> bm2;
	//boost::bimap<boost::bimaps::multiset_of<std::string>, boost::bimaps::multiset_of<std::string>> bm2;
	//boost::bimap<boost::bimaps::unordered_set_of<std::string>, boost::bimaps::list_of<std::string>> bm2;
	//boost::bimap<boost::bimaps::vector_of<int>, boost::bimaps::unconstrained_set_of<std::string>> bm2;
	boost::bimap<boost::bimaps::multiset_of<int>, boost::bimaps::multiset_of<std::string>> bm2;

	bm2.left.insert(std::make_pair(1, "111"));
	bm2.left.insert(std::make_pair(2, "222"));
	bm2.left.insert(std::make_pair(2, "555"));

	bm2.right.insert(std::make_pair("hello", 4));
	bm2.right.insert(std::make_pair("world", 3));
	bm2.right.insert(std::make_pair("!", 2));

	print_map(bm2.left);
	/*
	1<-->111
	2<-->222
	2<-->555
	2<-->!
	3<-->world
	4<-->hello
	*/
	boost::bimap<boost::bimaps::set_of<int>, boost::bimaps::vector_of<std::string>> bm3;
	bm3.left[2] = "ttt";
	print_map(bm3.left);
	//2<-->ttt
	//bm3.right.insert(std::make_pair("error", 2)); //error

	boost::bimap<boost::bimaps::tagged<int, struct id>, boost::bimaps::tagged<std::string, struct name>> bm4;
	bm4.by<name>().insert(std::make_pair("bynametest", 2017));
	bm4.right.insert(std::make_pair("righttest", 20172));
	print_map(bm4.by<name>());
	/*
	bynametest<-->2017
	righttest<-->20172
	*/

	typedef boost::bimap<boost::bimaps::multiset_of<int>, boost::bimaps::multiset_of<std::string>> bmType;
	bmType bm5 = boost::assign::list_of<bmType::relation>(1, "one")(2, "two");
	print_map(bm5.left);
	/*
	1<-->one
	2<-->two
	*/

	boost::assign::insert(bm5.right)("three", 3)("four", 4);
	print_map(bm5.right);
	/*
	four<-->4
	one<-->1
	three<-->3
	two<-->2
	*/
	print_map(bm5.left);
	/*
	1<-->one
	2<-->two
	3<-->three
	4<-->four
	*/

	typedef boost::bimap<boost::bimaps::multiset_of<int>, boost::bimaps::vector_of<std::string>> bmivType;
	bmivType bm6;
	boost::assign::push_back(bm6.right)("bmivType", 1);
	print_map(bm6.right); // bmivType<-->1

	typedef boost::bimap<int, std::string> bmisType;
	bmisType bm7 = boost::assign::list_of<bmisType::relation>(111, "111")(2, "monkey");
	BOOST_AUTO(pos7, bm7.left.find(111));
	print_map(bm7.left); // 111<-->111
	bm7.left.replace_key(pos7, 123);
	bm7.left.replace_data(pos7, "123");
	print_map(bm7.left); // 123<-->123

	//bm7.left.modify_key(pos7, boost::bimaps::_key = 2);
	bm7.left.modify_data(pos7, boost::bimaps::_data = "monkey"); // can not using modify_key together
	//assert(bm7.left.size() == 1);

	bmisType bm8;
	bm8 = boost::assign::list_of<bmisType::relation>(3, "33");
	BOOST_AUTO(pos8, bm8.left.find(3));

	BOOST_AUTO(posRight, bm8.project_right(pos8));
	cout << posRight->first << ", " << posRight->second << endl; // 33, 3

	typedef	boost::bimap<boost::bimaps::set_of<boost::bimaps::tagged<int, struct id>>, 
		boost::bimaps::multiset_of <boost::bimaps::tagged< std::string, struct name >> > bmssType;
	bmssType bm9 = boost::assign::list_of<bmssType::relation>(4, "44");
	boost::assign::insert(bm9.by<id>())(5, "55");
	boost::assign::insert(bm9.by<name>())("66", 6);
	print_map(bm9.left);
	BOOST_AUTO(pos9Right, bm9.by<name>().find("66")); BOOST_AUTO(pos9Left, bm9.project<id>(pos9Right));
	--pos9Left;
	cout << pos9Left->first << "==" << pos9Left->second << endl; // 5==55
}
