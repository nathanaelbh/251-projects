/*test01.cpp*/

//
// Unit tests for threaded AVL tree
//

#include <iostream>
#include <vector>

#include "avlt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) empty tree") 
{
  avlt<int, int>  tree;
// 	int w;
// 	int q;
// 	int e;
	//int u;
	//int r;
	//int o;
	//int d;
  REQUIRE(tree.size() == 0);
  REQUIRE(tree.height() == -1);
	tree.insert(4,1);
	tree.insert(10,1);
	tree.insert(5,1);
// 	tree.insert(5,1);
// 	tree.insert(30,1);
	//tree.insert(60,1);
	//tree.insert(1,1);
	//cout << tree.height();
	
	//w = tree % 15;
	//q = tree % 20;
	//e = tree % 100;
// 	u = tree % 5;
// 	r = tree % 30;
	//o = tree % 60; 
	//d = tree % 1;
	
	//cout << " " << w << " " << q << " " << e << ""  << " tree height:" << tree.height();
	
	//tree.dump(cout);
	
	
	tree.range_search(3,9);

}
