#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(2) basic symtable test") 
{
	symtable<string, string>  table;
	string symbol;
	
	REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);

	table.enterScope("global");
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 1);
	
	table.insert("i", "int");
	table.insert("j", "int");
	table.insert("opppp", "int");
	
	REQUIRE(table.curScope().Name == "global");
	REQUIRE(table.lookup("j", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::CURRENT));
	
	table.enterScope("middle");
	REQUIRE(table.curScope().Name == "middle");
	REQUIRE(table.size() == 3);
	REQUIRE(table.numscopes() == 2);
	
	table.insert("i", "int");
	table.insert("j", "double");
	table.insert("gh", "double");

	
	REQUIRE(table.size() == 6);
	REQUIRE(table.numscopes() == 2);
	
	REQUIRE(!table.lookup("gh", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(table.lookup("j", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(symbol == "int");
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(table.lookup("j", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(!table.lookup("opppp", symbol, symtable<string, string>::ScopeOption::CURRENT));

	
	table.enterScope("current");
	REQUIRE(table.curScope().Name == "current");
	REQUIRE(table.size() == 6);
	REQUIRE(table.numscopes() == 3);
	
	table.insert("p", "int");
	table.insert("o", "double");
	
	REQUIRE(table.lookup("j", symbol, symtable<string, string>::ScopeOption::GLOBAL));
    REQUIRE(symbol == "int");
	
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
	
	REQUIRE(table.lookup("j", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("p", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(symbol == "int");
	REQUIRE(!table.lookup("w", symbol, symtable<string, string>::ScopeOption::CURRENT));
	
	table.exitScope();
	
	table.insert("p", "int");
	REQUIRE(table.lookup("p", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(symbol == "int");
	REQUIRE(table.lookup("j", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(!table.lookup("k", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::CURRENT));
	
}