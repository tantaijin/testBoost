#include "stdafx.h"
#include "property_tree_example.h"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\xml_parser.hpp"
#include "boost\typeof\typeof.hpp"

/*
<conf>
<gui>1</gui>
<theme>matrix</theme>
<urls>
<url>url1</url>
<url>url2</url>
<url>url3</url>
</urls>
<clock_style>24</clock_style>
</conf>
*/
void test_property_tree()
{
	boost::property_tree::ptree pt;
	boost::property_tree::xml_parser::read_xml("..\\xml\\config.xml", pt);

	cout << pt.get<std::string>("conf.theme") << endl; // matrix 
	cout << pt.get<int>("conf.gui") << endl; //	1
	cout << pt.get("conf.proprety_not_exist", 100) << endl; //	100

	BOOST_AUTO(child, pt.get_child("conf.urls"));
	for (BOOST_AUTO(pos, child.begin()); pos != child.end(); ++pos)
	{
		cout << pos->second.data() << " ";
	}
	cout << endl; // url1 url2 url3
}
