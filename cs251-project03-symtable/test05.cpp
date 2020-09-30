
#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(7) basic symtable test") 
{
    symtable<string, string>  table;
    string symbol;
	
	REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);

	table.enterScope("global");
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 1);
	
	table.insert("i", "int");
	table.insert("j", "double");
	table.insert("k", "char");
	table.insert("o", "int");
	table.insert("y", "int");
	table.insert("ew", "int");
	
	REQUIRE(table.size() == 6);

	
	table.enterScope("middle");
	REQUIRE(table.numscopes() == 2);
	table.insert("sfs", "int");
	table.insert("werwe", "double");
	table.insert("cvb", "char");
	table.insert("ioo", "int");
	table.insert("qwtdd", "int");
	table.insert("eddw", "int");
	
    REQUIRE(table.size() == 12);
	table.insert("eddw", "double");
	REQUIRE(table.size() == 12);
	
}