#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(4) basic symtable test") 
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

	REQUIRE(table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
    REQUIRE(symbol == "char");
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(symbol == "int");
	REQUIRE(table.lookup("y", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(symbol == "int");
	REQUIRE(table.lookup("ew", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(symbol == "int");
	
	
	table.exitScope();
	
	table.enterScope("global");
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(!table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(!table.lookup("y", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(!table.lookup("ew", symbol, symtable<string, string>::ScopeOption::CURRENT));
	
}