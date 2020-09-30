
#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(4) basic symtable test") 
{
    symtable<string, string>  table;
    string symbol;
	symtable<string, string>::Scope  scopeee;
	
	REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);

	table.enterScope("global");
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 1);
	
	
	table.exitScope();
	try {
		table.exitScope();
		REQUIRE(false);
	}catch(...) {
		REQUIRE(true);
	}
	try {
		table.curScope();
		REQUIRE(false);
	}catch(...) {
		REQUIRE(true);
	}
	table.enterScope("global");
}