#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(899) basic symtable test") 
{
    symtable<string, string>  table;
	string symbol;
	
	REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);

	table.enterScope("global");
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 1);
	
	table.insert("i", "char");
	table.insert("j", "double");
	table.insert("k", "char");
	table.insert("o", "int");
	table.insert("y", "int");
	table.insert("ew", "int");
	REQUIRE(table.size() == 6);
	
	table.enterScope("middle");
	table.insert("i", "double");
	table.insert("j", "double");
	table.insert("k", "char");
	table.insert("o", "int");
	table.insert("y", "int");
	table.insert("ew", "int");
	REQUIRE(table.size() == 12);
	
	table.enterScope("current");
	table.insert("i", "int");
	table.insert("j", "double");
	table.insert("k", "char");
	table.insert("o", "int");
	table.insert("y", "int");
	table.insert("ew", "int");
	REQUIRE(table.size() == 18);
	
	REQUIRE(table.lookup("i", symbol));
	REQUIRE(symbol == "int");
	
	
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(symbol == "char");
// 	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
// 	REQUIRE(symbol == "double");
	
}