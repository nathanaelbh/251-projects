//
// A symtable unit test based on Catch framework
//
// << YOUR NAME >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) basic symtable test") 
{
	symtable<string, string>  table;
	string symbol;
	//symtable<string, string>::Scope  scope;
	//symtable<string, string>::Scope  scopeee;
	
	REQUIRE(table.size() == 0);
     REQUIRE(table.numscopes() == 0);
	
     table.enterScope("global");
	 REQUIRE(table.size() == 0);
	 REQUIRE(table.numscopes() == 1);
	 //table.curScope();
//      table.exitScope();
  
//      REQUIRE(table.size() == 0);
//      REQUIRE(table.numscopes() == 0);
	
//      table.enterScope("firstone");
// 	 table.enterScope("seirstone");
// 	 cout << table.numscopes() << endl;
// 	 table.exitScope();
//      cout << table.numscopes() << endl;
//      table.exitScope();
//      cout << table.numscopes() << endl;
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
	REQUIRE_THROWS(table.exitScope());
	REQUIRE_THROWS(table.curScope());

	REQUIRE(table.size() == 0);
     REQUIRE(table.numscopes() == 0);
	
	table.enterScope("global");
	 REQUIRE(table.size() == 0);
	 REQUIRE(table.numscopes() == 1);
	
	table.insert("k", "char");
    table.insert("x", "double");
	
	REQUIRE(table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
     REQUIRE(symbol == "char");
	
	//cout << table.size();
	REQUIRE(table.size() == 2);
	
	table.enterScope("global2222");
	
	table.insert("ff", "char");
    table.insert("ee", "double");
	
// 	scopeee = table.curScope();
// 	auto findkeylookupcc = scopeee.Symbols.find("ee");
// 		if(findkeylookupcc != scopeee.Symbols.end()){
// 			symbol = findkeylookupcc->second;	
// 		}
	REQUIRE(symbol == "double");
	//cout << scope.size();
	
	REQUIRE(table.lookup("k", symbol, symtable<string, string>::ScopeOption::GLOBAL));
    REQUIRE(symbol == "char");
	
	
	
 	//REQUIRE(scope.Symbol.find("k", symbol));
//      REQUIRE(symbol == "double");
	
	//table.dump(std::cout, symtable<string, string>::ScopeOption::GLOBAL);
	//table.dump(std::cout, symtable<string, string>::ScopeOption::CURRENT);

	
}