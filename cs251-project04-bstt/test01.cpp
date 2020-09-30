/*test01.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) empty tree") 
{
  bstt<int, int>  tree;
	int x;
	int y;
	int z;
	//int Key;

  REQUIRE(tree.size() == 0);
	
  vector<int> values = {100, 50, 40, 35, 45, 150, 125, 175, 33, 36, 37, 38, 99};
  
  for (int x : values)  // insert each value:
    tree.insert(x, 7);
	
 tree.insert(111, 7);
	tree.insert(1, 6);
	REQUIRE(tree.search(50,x)==true);
//bstt<int, int>  secondtree(tree);
	
	//thirdtree = tree;
	//thirdtree.search(50,temp);
	//cout << temp;
    //REQUIRE(temp == 7);
	//thirdtree.dump(cout);
	tree.dump(cout);
	tree.search(50, y);
	x = tree[1];
	z = tree(35);
	
	cout << y << "z: " << z << endl;
		cout << "this is x: " << x;
	bstt<int, int>  thirdtree;
	thirdtree = tree;
	//thirdtree.clear();
	thirdtree.insert(1333, 6);
	thirdtree.dump(cout);
	//cout << "this is going to be begin: ";
	//tree.begin();
	//cout << " :this is going to be begin";
	//cout << tree(100);
	//int e = 35;
	tree.insert(1333, 6);
	tree.dump(cout);
	//tree.begin();
	
// 	while (tree.next(Key))
// 	{
// 		//cout << "\n" << Key << " ";
// 	}
// 	cout << endl;

	
	
  // make sure they were all inserted:
//   REQUIRE( tree.size() == values.size() );
//    for (int x : values)
//     REQUIRE(tree.search(x));
    
//   REQUIRE(!tree.search(-99));
//   REQUIRE(!tree.search(39));
//   REQUIRE(!tree.search(32));
}
