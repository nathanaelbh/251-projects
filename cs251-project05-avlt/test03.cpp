#include <iostream>
#include <vector>

#include "avlt.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("(2) case 1 at the root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 80, 60,40,20 };
  vector<int> heights = { 4,3,2,1,0 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    //cout << i << " " << (tree % keys[i]) << " " << heights[i]<< endl;
    REQUIRE((tree % keys[i]) == heights[i]);
  }

    tree.dump(cout);
}