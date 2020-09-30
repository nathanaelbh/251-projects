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
    bstt<int, int>  tree, tree3;

	REQUIRE(tree.size() == 0);
	tree.insert(30, 1);
	tree.insert(50, 2);
	tree.insert(15, 3);
	tree.insert(8, 4);
	tree.insert(25, 5);
	tree.insert(27, 6);
	tree.insert(15, 7);
	
	REQUIRE(tree.size() == 6);
	int x;
	REQUIRE(tree.search(15, x));
	REQUIRE(x == 3);
	REQUIRE(tree.search(8, x));
	REQUIRE(!tree.search(7, x));
	
	tree.dump(cout);
	tree.begin();
	while (tree.next(x)) {
		cout << x << ' ';
	}
	cout << endl;
	
	REQUIRE(tree[27] == 6);
	REQUIRE(tree(8) == 15);
	REQUIRE(tree(27) == 30);
	REQUIRE(tree(30) == 50);
	REQUIRE(tree(50) == 0);
	
	bstt<int, int>  tree2 = tree;
	REQUIRE(tree2.size() == 6);
	tree.clear();
	REQUIRE(tree.size() == 0);
	REQUIRE(tree2.size() == 6);
	
	tree3 = tree2;
	tree3.dump(cout);
}