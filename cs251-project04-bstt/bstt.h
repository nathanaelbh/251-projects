/*bstt.h*/

//
// Threaded binary search tree
//

#pragma once

#include <iostream>
using namespace std;

template<typename KeyT, typename ValueT>
class bstt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  NODE* ptr;
  int   Size;  // # of nodes in the tree (0 if empty)
  
    void _postorder (NODE* cur) //post order helper
	{
	if (cur == nullptr){// checks if the cur is null
		return;
	}
	else
	{  
		_postorder (cur->Left); // recursive call
		if (!cur->isThreaded){ // checks if threaded
		   _postorder (cur->Right);// call recursive with the right
		}
		delete cur;// deletes
    }
	}
	

  NODE* _begin(NODE* cur){ //begin helper function
	  while(cur->Left != nullptr){ // checks to see if left is null yet
		  cur = cur->Left;// changes cur to null
	  }
	  return cur;// returns null
  }
  
  
  vector<KeyT> getKeys(function<bool(KeyT)> F){
	 vector<KeyT> v;
	 
	 _dump(F, v);
	 return v;
  }


  
  
  
  void _dump(NODE* cur, vector<KeyT>& v) const // dump function
  {
     if (cur == nullptr)// checks if cur is null
       return;
     else
     {
        _dump(cur->Left, v);// recursive call
		
        if ((!cur->isThreaded) || (cur->Right == nullptr) ) // checks to see if threaded
		{
				v.push_back(cur);
		}
		else{
			return ;
		}
		_dump(cur->Right, v);
     }
  }
  
  
  
  
  
  void _dump(ostream& output, NODE* cur) const // dump function
  {
     if (cur == nullptr)// checks if cur is null
       return;
     else
     {
        _dump(output, cur->Left);// recursive call
        output << "(" << cur->Key << "," << cur->Value;// outputs first part
        if ((!cur->isThreaded) || (cur->Right == nullptr) ) // checks to see if threaded
		{
			output << ")" << endl;// if not end out put
			//return ;
		}
		else{
			output << "," << cur->Right->Key << ")" << endl;// if it is returns next inorder
			return ;
			//_dump(output, cur->Right);
		}
		_dump(output, cur->Right);// recursive call
     }
  }
  
  
	
   void preorder(NODE* cur)// preorder helper
   {
   if (cur == nullptr)// checks if null
	   return;
   else
   {
	insert(cur->Key, cur->Value); // calls insert to copy
// 		 this->Key = other->Key;
// 		this->Value = other->Value;
// 		this->Left = other->Left;
// 		this->Right = other->Right;
	preorder(cur->Left);// recursive call
	if (cur->isThreaded){// checks if threaded
		return;
	}
	else{
		preorder(cur->Right);// recirsive call
	}
    }
    }
	


public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  bstt()
  {
    Root = nullptr;
    Size = 0;
  }
  
	 
  


  //
  // copy constructor
  //
  bstt(const bstt& other)
  {
	  // clear();
	  //NODE* cur = Root;
	  Root = nullptr; // sets root to null
	  Size = 0; // size 0
	  preorder(other.Root); //calls preorder helper
    //
    // TODO
    //
  }

	//
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~bstt()
  {
    _postorder(Root);// calls postoder helper
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  bstt& operator=(const bstt& other)
  {
	clear(); // clears
	preorder(other.Root);// call preorder helper
    return *this;// returns this
  }

  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    _postorder(Root);// calls postoder helper
	Root = nullptr;// sets root to null 
	Size = 0; // size 0
  }

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  // Time complexity:  O(1) 
  //
  int size() const
  {
    return Size; // returns size
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) on average
  //
  bool search(KeyT key, ValueT& value) const
  {
    NODE* cur = Root; // creates new ptr

    while (cur != nullptr)// untill cur is not null
    {
      if (key == cur->Key)  {// already in tree
	  value = cur->Value; // gets the value from node
        return true;
        }
     if (key < cur->Key){// if key is less than cur key
      cur = cur->Left;// sets cur to be left ptr
	  }
         else{// greater than cur key
            if (cur->isThreaded){// checks if threaded
      // there is noRightpointer in traditional traversal:
            cur = nullptr;
			}
         else{
            cur = cur->Right;
			}
            }
    }
    return false;
  }


	
  NODE* search2(NODE* cur, KeyT& key) const// search to return node
  {
    //NODE* cur = Root;

    while (cur != nullptr)// while ! null ptr
    {
      if (key == cur->Key)  {// already in tree
        return cur->Right; // goto right
        }
     if (key < cur->Key){ // checks if key is less make cur left
      cur = cur->Left;
	  }
         else{
            if (cur->isThreaded){// checks if threaded
      // there is noRightpointer in traditional traversal:
            cur = nullptr;
			}
         else{
            cur = cur->Right; // set right
			}
            }
    }
    return nullptr;
  }



  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  // Time complexity:  O(lgN) on average
  //
  void insert(KeyT key, ValueT value)
  {
  
	NODE* prev = nullptr;
    NODE* cur = Root;
    
    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr) // if not null ptr
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur; // savle ptrs
        cur = cur->Left;
      }
      else
      {
        prev = cur;
		if (cur->isThreaded) // checks threaded
      // there is noRightpointer in traditional traversal:
            cur = nullptr;
         else
            cur = cur->Right;
      }
    }//while
	
	
	NODE* newNode = new NODE();// creates newnode
    newNode->Key = key;// stores new key, value, ptr, and is threaded
	newNode->Value = value;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
	newNode->isThreaded = true;
	
	

   if(prev == nullptr){// tracks old ptr
      Root = newNode;
   }
   else if(key < prev->Key){// if old ptr is bigger go right copy from new node
      prev->Left = newNode;
	  newNode->Right = prev;
	  newNode->isThreaded = true;
   }
   else{
 	   NODE* oldptr = prev->Right; // else
		//newNode->Right = prev->Right;
      prev->Right = newNode;
	  prev->isThreaded = false;
	  newNode->Right = oldptr;
	  newNode->isThreaded = true;

	  
   }
  Size++;
  

  }

  //
  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  ValueT operator[](KeyT key) const
  {

    ValueT x;
	search(key, x);// searches and stores value in x
	if(search(key, x)){ // if found return the key
		return x;
	}
	else {
    return ValueT{ };// defualt 
	}
  }

  //
  // ()
  //
  // Finds the key in the tree, and returns the key to the "right".
  // If the right is threaded, this will be the next inorder key.
  // if the right is not threaded, it will be the key of whatever
  // node is immediately to the right.
  //
  // If no such key exists, or there is no key to the "right", the
  // default key value KeyT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  KeyT operator()(KeyT key) const
  {
  
    NODE* cur = Root;// stores root
    //KeyT x;
	cur = search2(cur, key);// calls node function
	if(cur == nullptr){// check if null else return key
		return KeyT{};
	}
	return cur->Key;
  }

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the 
  // call to begin(), the internal state denotes the first inorder
  // key; this ensure that first call to next() function returns
  // the first inorder key.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key)) go to the left smallest
  //      cout << key << endl;
  //
  void begin()
  {
	  if (Root)//passes root
		  ptr = _begin(Root); // calls begin helper and stores in ptr
	   else
		   ptr = nullptr; // condition if tree is empty
  }

  //
  // next
  //
  // Uses the internal state to return the next inorder key, and 
  // then advances the internal state in anticipation of future
  // calls.  If a key is in fact returned (via the reference 
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more keys are available.  This is the end of the
  // inorder traversal.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  bool next(KeyT& key)
  {
    if (ptr != nullptr) { // check if null ptr
		key = ptr->Key; // stores key
		if (ptr->isThreaded || ptr->Right == nullptr)// checks if threaded or right is null
			ptr = ptr->Right;
		else
			ptr = _begin(ptr->Right); // calls helper
		return true;
	}

    return false;
  }

  //
  // dump
  // 
  // Dumps the contents of the tree to the output stream, using a
  // recursive inorder traversal.
  //
  void dump(ostream& output) const
  {
    output << "**************************************************" << endl;
    output << "********************* BSTT ***********************" << endl;

    output << "** size: " << Size << endl;

    //
    // inorder traversal, with one output per line: either 
    // (key,value) or (key,value,THREAD)
    //
    // (key,value) if the node is not threaded OR thread==nullptr
    // (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //
	  _dump(output ,Root); // calls dump helper
    output << "**************************************************" << endl;
  }
	
};

