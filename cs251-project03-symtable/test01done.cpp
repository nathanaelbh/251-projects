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
	
//   //
//   // these lookups should both succeed:
//   //
//   string symbol;
  
//   REQUIRE(table.lookup("k", symbol));
//   REQUIRE(symbol == "char");
  
//   REQUIRE(table.lookup("i", symbol));
//   REQUIRE(symbol == "int");
  
//   REQUIRE(table.lookup("j", symbol));
//   REQUIRE(symbol == "double");
  
//   //
//   // this lookup should return false:
//   //
//   REQUIRE((!table.lookup("x", symbol)));
	
// 	cout << "HEEEEEEEEEEEEEEEEYYYYY" << endl;
}
