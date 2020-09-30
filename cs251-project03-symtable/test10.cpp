#include <iostream>

#include "symtable.h"
#include <string>

#include "catch.hpp"

using namespace std;

TEST_CASE("(434) basic symtable test")
{
	symtable<string, string> table;
		string symbol;

    REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);
	
	table.enterScope("global");
	REQUIRE(table.curScope().Name == "global");
	
	table.insert("i", "int");
    table.insert("j", "double");
	REQUIRE(table.size() == 2);
    REQUIRE(table.numscopes() == 1);
	REQUIRE(table.lookup("i", symbol));
	REQUIRE(symbol == "int");
	table.enterScope("global1");
	REQUIRE(table.curScope().Name == "global1");
	

}