/*symtable.h*/

// 
// Nathanael Bhooshi
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #03: symtable
//
// Symbol Table: a symbol table is a stack of scopes, typically used by a
// compiler to keep track of symbols in a program (functions, variables,
// types, etc.).  In most programming languages, you "enter scope" when you 
// see {, and "exit scope" when you see the corresponding }.  Example:
//
// int main()
// {              <-- enterScope()
//    int i;      <-- enter "i" into symbol table as type "int"
//    .
//    .
//    while (true)
//    {              <-- enterScope()
//       char i;     <-- enter "i" into symbol table as type "char"
//
// Notice there are two variables named "i", which is legal because
// they are in different scopes.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>

using namespace std;

template<typename KeyT, typename SymbolT>
class symtable
{
public:
  //
  // A symbol table is a stack of scopes.  Every scope has a name, and 
  // we use a map to hold the symbols in that scope.  You can *add* to
  // this class, but you must use the Name and Symbols as given to store
  // the scope name, and scope symbols, respectively.
  //
  class Scope
  {
  public:
    string              Name;
    map<KeyT, SymbolT>  Symbols;

    // constructors:
    Scope()
    {
      // default empty string and an empty map:
    }

    Scope(string name)
    {
      this->Name = name;
      // empty map created by map's constructor:
    }
  };

private:
  //
  // TODO: implementation details
  //
	//int Size = 0;
	deque<Scope>myscopes; // creates the deque
	int counter;
	int sycounter; // counter for size
public:
  enum class ScopeOption
  {
    ALL, 
    CURRENT,
    GLOBAL
  };

  //
  // default constructor:
  //
  // Creates a new, empty symbol table.  No scope is open.
  //
  symtable()
  {
	counter = 0;
	sycounter = 0; // initalizes to 0

  }

  //
  // size
  //
  // Returns total # of symbols in the symbol table.
  //
  // Complexity: O(1)
  //
  int size() const // 1111111111111111111111111111111111111111111
  {
    
    return sycounter; // returns the size of table
  }

  //
  // numscopes
  //
  // Returns the # of open scopes.
  //
  // Complexity: O(1)
  //
  int numscopes() const // 2222222222222222222222222222222222222222222
  {

    return myscopes.size(); // number of scopes
  }

  //
  // enterScope
  //
  // Enters a new, open scope in the symbol table, effectively "pushing" on
  // a new scope.  You must provide a name for the new scope, although
  // the name is currently used only for debugging purposes.
  //
  // NOTE: the first scope you enter is known as the GLOBAL scope, since this
  // is typically where GLOBAL symbols are stored.  
  //
  // Complexity: O(1)
  //
  void enterScope(string name) //333333333333333333333333333333333333333333
  {
	  counter++; // increments counter for scopes
	  myscopes.push_back (Scope(name)); // pushes a new scope to que

  }

  //
  // exitScope
  //
  // Exits the current open scope, discarding all symbols in this scope.
  // This effectively "pops" the symbol table so that it returns to the 
  // previously open scope.  A runtime_error is thrown if no scope is 
  // currently open.  
  //
  // Complexity: O(1)
  //
  void exitScope() //44444444444444444444444444444444444444444444444444444
  {
   
    if(myscopes.empty()){ // checks to see if there are any 
		throw runtime_error("no scope is currently open");
	}
    sycounter = sycounter - myscopes.back().Symbols.size(); // decrements the number of symbols
    myscopes.pop_back(); // pop the most recent
	
  }

  //
  // curScope
  //
  // Returns a copy of the current scope.  A runtime_error is thrown if
  // no scope is currently open.
  //
  // Complexity: O(N) where N is the # of symbols in the current scope
  //
  Scope curScope() const //55555555555555555555555555555555555555555555555555
  {
	  if(myscopes.empty()){ // checks if there are any scopes open
		throw runtime_error("no scope is currently open");
	}
	  //Scope scopecur = myscopes.at(myscopes.size() - 1);
	  //Scope tempscope = Scope(tempscope.Name)
	  return myscopes.back(); // creates a copy
  }

  //
  // insert
  //
  // Inserts the (key, symbol) pair in the *current* scope.  If the key
  // already exists in the current scope, the associated symbol is replaced
  // by this new symbol.
  //
  // Complexity: O(lgN) where N is the # of symbols in current scope
  //
  void insert(KeyT key, SymbolT symbol) //666666666666666666666666666666666666666666666666666
  {
// 	  if(myscopes.empty()){
// 		throw runtime_error("no scope is currently open");
// 	}
	  //Scope temp = curScope();
	  
	  auto findkey = myscopes.back().Symbols.find(key); // stores temp key
	  if (findkey == myscopes.back().Symbols.end()){
		  sycounter++; //if not found insert and increment values
		  myscopes.at(myscopes.size() - 1).Symbols[key] = symbol;
	  }
	  else {//if found change to new values
		  myscopes.at(myscopes.size() - 1).Symbols[key] = symbol;
	  }
	  
    //
    // TODO:
    //
  }

  //
  // lookup
  //
  // Searches the symbol table for the first (key, symbol) pair that 
  // matches the given key.  The search starts in the current scope, and 
  // proceeds "outward" to the GLOBAL scope.  If a matching (key, symbol)
  // pair is found, true is returned along with a copy of the symbol (via 
  // "symbol" reference parameter).  If not found, false is returned and
  // the "symbol" parameter is left unchanged.
  //
  // NOTE: the search can be controlled by the "option" parameter.  By 
  // default, the entire symbol table is searched as described above.
  // However, the search can also be limited to just the current scope, 
  // or just the GLOBAL scope, via the "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   string                   symbol;
  //   bool                     found;
  //   ...
  //   found = table.lookup("i", 
  //                        symbol, 
  //                        symtable<string,string>::ScopeOption::CURRENT);
  //
  // Complexity: O(SlgN) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  bool lookup(KeyT key,  //77777777777777777777777777777777777777777777777777777
              SymbolT& symbol, 
              ScopeOption option = ScopeOption::ALL) const
  {
//     if(myscopes.empty()){
// 		throw runtime_error("no scope is currently open");
// 	}
// 	

	if(option == ScopeOption::CURRENT){ //current scope
		auto findkeylookupc = myscopes.back().Symbols.find(key); //stores into temp variable
		if(findkeylookupc != myscopes.back().Symbols.end()){// checks to see if the temp is in the scope
			symbol = findkeylookupc->second;
			return true;
		}
		    return false;
	}
	
	else if(option == ScopeOption::GLOBAL){// global scope
	auto findkeylookupf = myscopes.front().Symbols.find(key); // stores into temp
	if(myscopes.front().Symbols.end() != findkeylookupf){// checks to see if the temp is in the global scope
		symbol = findkeylookupf->second;
		return true;
	}
		return false;
    }

	else if(option == ScopeOption::ALL){// all scopes
	for(int i = myscopes.size() - 1 ; i >= 0; i-- ){// goes through all scopes
	    auto findkeylookup = myscopes[i].Symbols.find(key);// makes temp
		if(myscopes[i].Symbols.end() != findkeylookup){// checks that scope if tep is there
			symbol = findkeylookup->second;
			return true;
		}
	}
		    return false;
	}
	return false;
  }

  //
  // dump
  // 
  // Dumps the contents of the symbol table to the output stream, 
  // starting with the current scope and working "outward" to the GLOBAL
  // scope.  You can dump the entire symbol table (the default), or dump
  // just the current scope or global scope; this is controlled by the 
  // "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   ...
  //   table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
  //
  // Complexity: O(S*N) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  void dump(ostream& output, ScopeOption option = ScopeOption::ALL) const
  {
    output << "**************************************************" << endl;

    if (option == ScopeOption::ALL){// dump for all
      output << "*************** SYMBOL TABLE (ALL) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
    output << "** # of symbols: " << this->size() << endl;
	  for(int i = myscopes.size() - 1; i >= 0; i--){ // goes through each scope
	  	  output << "** " << myscopes.at(i).Name << " **" << endl;
		  for(auto &pair : myscopes.at(i).Symbols){// iterates through the scope
		 output << pair.first <<": " << pair.second << endl;
		  }
	  }
	}  
	  
    else if (option == ScopeOption::CURRENT){// current scope
      output << "*************** SYMBOL TABLE (CUR) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
    output << "** # of symbols: " << this->size() << endl;
	  output << "** " << myscopes.back().Name << " **" << endl;
	  for(auto &pair : myscopes.back().Symbols){//for the current prints all elements
		 output << pair.first <<": " << pair.second << endl;	 
	  }
	  }
    else{ // global:
      output << "*************** SYMBOL TABLE (GBL) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
    output << "** # of symbols: " << this->size() << endl;
	  output << "** " << myscopes.front().Name << " **" << endl;
	  for(auto &pair : myscopes.front().Symbols){//for the global prints all elements
		 output << pair.first <<": " << pair.second << endl;
	  }
	}
    

    //
    // output format per scope:
    //
    // ** scopename **
    // key: symbol
    // key: symbol
    // ...
    //
	
    output << "**************************************************" << endl;
   // output << "** # of scopes: " << this->numscopes() << endl;
  }

};
