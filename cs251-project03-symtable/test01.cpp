//
// A symtable unit test based on Catch framework
//
// << YOUR NAME >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>
#include <string>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) basic symtable test") 
{
	symtable<string, string>  table;
	string symbol;
	symtable<string, string>::Scope  scope;
	symtable<string, string>::Scope  scopeee;
	
	REQUIRE(table.size() == 0);
     REQUIRE(table.numscopes() == 0);
	
     table.enterScope("global");
	 REQUIRE(table.size() == 0);
	 REQUIRE(table.numscopes() == 1);

   table.insert("i", "int");
   table.insert("j", "double");
  
   REQUIRE(table.size() == 2);
   REQUIRE(table.numscopes() == 1);
  
   table.enterScope("x");
   table.insert("k", "char");
   table.insert("k", "double");
  
   REQUIRE(table.size() == 3);
   REQUIRE(table.numscopes() == 2); 
   table.exitScope();
	REQUIRE(!table.lookup("k", symbol));
   table.insert("y", "char");
	REQUIRE(table.size() == 3);
   table.insert("y", "double");
	REQUIRE(table.size() == 3);
	REQUIRE(table.lookup("y", symbol));
	REQUIRE(symbol == "double");
   REQUIRE(table.size() == 3);
   REQUIRE(table.numscopes() == 1);
   table.exitScope();
   REQUIRE(table.size() == 0);
   REQUIRE(table.numscopes() == 0);
	
// 	try {
// 		table.exitScope();
// 		REQUIRE(false);
// 	}catch(...) {
// 		REQUIRE(true);
// 	}
// 	try {
// 		table.curScope();
// 		REQUIRE(false);
// 	}catch(...) {
// 		REQUIRE(true);
// 	}

// 	REQUIRE(table.size() == 0);
//      REQUIRE(table.numscopes() == 0);
	
	table.enterScope("global");
	 REQUIRE(table.size() == 0);
	 REQUIRE(table.numscopes() == 1);
	
	table.insert("k", "char");
    table.insert("x", "double");
	
	REQUIRE(table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
     REQUIRE(symbol == "char");
	

	REQUIRE(table.size() == 2);
	
	table.enterScope("global2222");
	
	table.insert("ff", "char");
    table.insert("ee", "double");
	
	scopeee = table.curScope();
	auto findkeylookupcc = scopeee.Symbols.find("ee");
		if(findkeylookupcc != scopeee.Symbols.end()){
			symbol = findkeylookupcc->second;	
		}
	REQUIRE(symbol == "double");

	
	REQUIRE(table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
    REQUIRE(symbol == "char");
	
	

	
}