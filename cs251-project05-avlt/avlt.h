

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
  int   Size;  // # of nodes in the tree (0 if empty)
  NODE* Next;  // used by threaded inorder traversal to denote next key

  //
  // helper functions to return the Left and Right pointers; in
  // particular the ptr returned for the Right is controlled by 
  // the "isThreaded" field:  if "isThreaded" is true then nullptr
  // pointer is returned, otherwise the actual underyling ptr
  // is returned.
  //
  NODE* _getActualLeft(NODE* cur) const
  {
    return cur->Left;
  }

  NODE* _getActualRight(NODE* cur) const
  {
    if (cur->isThreaded)  // then actual Right ptr is null:
      return nullptr;
    else  // actual Right is contents of Right ptr:
      return cur->Right;
  }

  //
  // _free
  // 
  // Frees the memory associated with the tree.
  //
  void _free(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      // 
      // use post-order traversal since need to free
      // sub-trees first, then we can free the root:
      // 
      _free(_getActualLeft(cur));
      _free(_getActualRight(cur));
      delete cur;
    }
  }

  //
  // _copy
  //
  // Makes a copy of "othercur" into "this" tree.
  //
  void _copy(NODE* othercur)
  {
    if (othercur == nullptr)
      return;
    else
    {
      //
      // preorder: copy root, then we can copy left and right:
      //
      this->insert(othercur->Key, othercur->Value);

      _copy(_getActualLeft(othercur));
      _copy(_getActualRight(othercur));
    }
  }

  // 
  // _dump
  //
  void _dump(ostream& output, NODE* cur) const
  {
    if (cur == nullptr)
      return;
    else
    {
      //
      // inorder traversal, with one output per line: either 
      // (key,value) or (key,value,THREAD)
      //
      // (key,value) if the node is not threaded OR thread==nullptr
      // (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
      //
      _dump(output, _getActualLeft(cur));

      output << "(" << cur->Key << "," << cur->Value;

      if ((!cur->isThreaded) || (cur->Right == nullptr))
      {
        output << ")" << endl;
      }
      else
      {
        output << "," << cur->Right->Key << ")" << endl;
      }

      _dump(output, _getActualRight(cur));
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
    Next = nullptr;
  }

  //
  // copy constructor
  //
  bstt(const bstt& other)
  {
    //
    // construct an empty tree, then let's make a copy of other:
    //
    Root = nullptr;
    Size = 0;
    Next = nullptr;

    _copy(other.Root);

    this->Next = other.Next;  // to be safe, copy this state as well:
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
    _free(Root);
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  bstt& operator=(const bstt& other)
  {
    //
    // we have an existing tree, so clear it:
    //
    this->clear();

    //
    // now copy the other one:
    //
    _copy(other.Root);

    this->Next = other.Next;  // to be safe, copy this state as well:

    return *this;
  }

  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    _free(Root);

    // now reset to empty:
    Root = nullptr;
    Size = 0;
    Next = nullptr;
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
    return Size;
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
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        value = cur->Value;
        return true;
      }

      if (key < cur->Key)  // search left:
      {
        cur = _getActualLeft(cur);
      }
      else
      {
        cur = _getActualRight(cur);
      }
    }//while  

    // if get here, not found
    return false;
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
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = _getActualLeft(cur);
      }
      else
      {
        prev = cur;
        cur = _getActualRight(cur);
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 
    NODE* n = new NODE();
    n->Key = key;
    n->Value = value;
    n->Left = nullptr;
    n->Right = nullptr;
    n->isThreaded = false;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr)
    {
      Root = n;
      //
      // we are the only node in the tree, and thus 
      // the last node inorder: so threaded is true
      // and ptr is null:
      //
      n->isThreaded = true;
      n->Right = nullptr;
    }
    else if (key < prev->Key)
    {
      prev->Left = n;
      //
      // we are to the left of our parent, which means
      // our parent is next inorder --- so threaded 
      // points to our parent:
      //
      n->isThreaded = true;
      n->Right = prev;
    }
    else
    {
      //
      // we are to the right of our parent, which means
      // our successor is our parent's successor --- so
      // copy that threaded pointer before we change it:
      //
      n->isThreaded = true;
      n->Right = prev->Right;

      // parent is no longer threaded since they link to us:
      prev->isThreaded = false;
      prev->Right = n;
    }

    // 
    // 4. update size and we're done:
    //
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
    ValueT  value = ValueT{};

    //
    // perform search, and either we find it --- and value is 
    // updated --- or we don't and we'll return default value:
    //
    this->search(key, value);

    return value;
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
    NODE* cur = Root;

    //
    // we have to do a traditional search, and then work from
    // there to follow right / thread:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // found it:
      {
        // 
        // we want the key to the right, either immediately right
        // or the threaded inorder key.  Just need to make sure
        // we have a pointer first:
        if (cur->Right == nullptr)  // threaded but null:
          return KeyT{ };
        else
          return cur->Right->Key;
      }

      if (key < cur->Key)  // search left:
      {
        cur = _getActualLeft(cur);
      }
      else
      {
        cur = _getActualRight(cur);
      }
    }//while  

    //
    // if get here, not found, so return default key:
    //
    return KeyT{ };
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
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  void begin()
  {
    Next = Root;

    if (Next != nullptr)  // advance as left as possible:
    {
      while (Next->Left != nullptr)
        Next = Next->Left;
    }
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
    if (Next == nullptr)
    {
      //
      // no more keys:
      //
      return false;
    }

    //
    // we have at least one more, so grab it now,
    // advance, and return true:
    //
    key = Next->Key;

    if (_getActualRight(Next) == nullptr)
    {
      // follow the thread:
      Next = Next->Right;
    }
    else
    {
      Next = Next->Right;  // go right, and then left as far as we can:
      
      while (Next->Left != nullptr)
        Next = Next->Left;
    }

    return true;
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

    output << "** size: " << this->size() << endl;

    //
    // inorder traversal, with one output per line: either 
    // (key,value) or (key,value,THREAD)
    //
    // (key,value) if the node is not threaded OR thread==nullptr
    // (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //
    _dump(output, Root);

    output << "**************************************************" << endl;
  }

};