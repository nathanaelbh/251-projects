/*test02.cpp*/

//
// Some Catch-based unit tests for binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(2) testing BST clear") 
{
  bstt<int, int>  tree;
	vector<int> values = {150, 50, 400, 55, 45, 500, 350 };
  
  for (int x : values)  // insert each value:
    tree.insert(x, 7);
	
	tree.dump(cout);
  
//   vector<int> values = {30, 15, 8, 25, 20, 28, 50, 70, 60};
  
//   for (int x : values)  // insert each value:
//     bst.insert(x);
    
//   // make sure they were all inserted:
//   //REQUIRE( bst.size() == values.size() );
  
//   for (int x : values)
//     REQUIRE(bst.search(x));
    
//   REQUIRE(!bst.search(-99));
//   REQUIRE(!bst.search(39));
//   REQUIRE(!bst.search(32));
	
	//
	// now we clear
	// 
// 	bst.clear();
	
// 	REQUIRE(bst.size() == 0);
// 	bst.inorder();

  //
  // re-build a simple BST tree with 4 nodes:
  //
//   bst.insert(100);
//   bst.insert(50);
//   bst.insert(150);
//   bst.insert(125);

  // 
  // Tests:
  //
//   REQUIRE(bst.size() == 4);
  
//   REQUIRE(bst.search(100));
//   REQUIRE(bst.search(125));
//   REQUIRE(bst.search(150));
//   REQUIRE(bst.search(50));
  
//   REQUIRE(!bst.search(101));
//   REQUIRE(!bst.search(1));
//   REQUIRE(!bst.search(999));
  
//   // some output even though we can't check it:
//   bst.inorder();
//   bst.addTo(3);
//   bst.inorder();
	
}
