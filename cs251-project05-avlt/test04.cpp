/*test.cpp*/

//
// An AVL unit test based on Catch framework
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "avlt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) empty tree")
{
  avlt<int, int>  tree;

  REQUIRE(tree.size() == 0);
  REQUIRE(tree.height() == -1);
}


TEST_CASE("(2) case 1 at the root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 80, 60 };
  vector<int> heights = { 0, 1, 0 };

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
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(3) case 333 at the root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 1,5,11,8,15,18,7,9,6,14,10,4,3,2,17,13 };
  vector<int> heights = { 1,1,3,0,2,1,4,1,0,1,0,0,2,0,0,0 };

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
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(4) case 444333 at the root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100,150,160,90,85,111,112,110,109,108,83,81,79,77,75,73,71,92,94,96,107,113,114,200,148,105,82,86,87,98,52 };
  vector<int> heights = { 5,3,1,0,2,4,0,0,2,0,1,4,0,1,0,2,1,3,0,1,1,2,1,0,0,0,0,0,1,0,0 };

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
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}









  
//   while(cur !=nullptr){
//   preRoot =cur;
//       if(lower == cur->Key ){
//         break;
//          }
//       if(lower < cur->Key){
//          cur=cur->Left;
//       }
//       else{
//       if(cur->isThreaded ){
//             break;  
//          }
//          cur = cur->Right;
//       }
//   }
  