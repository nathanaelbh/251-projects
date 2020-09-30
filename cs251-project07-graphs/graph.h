/*graph.h*/

//
// Nathanael Bhooshi
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
// original author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <list>


using namespace std;


template<typename VertexT, typename WeightT>
class graph
{
private:

  int countedge = 0; // edge counter
  map<VertexT, map<VertexT, WeightT>> adjacencyList; // map of map
  
  //
  // _LookupVertex
  //
  // Finds the vertex in the Vertices vector and returns it's 
  // index position if found, otherwise returns -1.
  //
  
  bool _LookupVertex(VertexT v) const
  { // checks if vertex is in the map
    if(adjacencyList.find(v) != adjacencyList.end()) // iterator
        return false;

    // if get here, not found:
    return true;
  }


public:
  //
  // constructor:
  //
  // Constructs an empty graph where n is the max # of vertices 
  // you expect the graph to contain.
  //
  // NOTE: the graph is implemented using an adjacency matrix.
  // If n exceeds the dimensions of this matrix, an exception 
  // will be thrown to let you know that this implementation
  // will not suffice.
  //
  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  graph(){} // constructor 
  
  
  int NumVertices() const // return size
  {
    return adjacencyList.size();
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const // return edges
  {
 
    return countedge;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v)
  {
	
	if(_LookupVertex(v)){ // calls look up
		adjacencyList[v] = map<VertexT, WeightT>(); // inserts vertex with empty value
		return true;
	}
	
	return false;
	
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight)
  {
  WeightT temp; // temp
  //cout << from << "to" << to;
    if(!_LookupVertex(from) && !_LookupVertex(to)){ // checks to and from exist
		if(getWeight(from, to, temp)){ // checks if edge exists
			adjacencyList[from][to] = weight; //just updates weight
		}
		
		else {
			adjacencyList[from][to] = weight; // updates both weight and edges
			countedge++;
		}
		return true;
	}

    return false;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const
  {
    auto iter1 = adjacencyList.find(from); // creates iter starting from from
	if (iter1 != adjacencyList.end()){ //searches 
		auto iter2 = iter1->second.find(to); // creates iter of 2nd map
		if(iter2 != iter1->second.end()){ // if it does not reach end
			weight = iter2->second; // gets weight 
			return true;
		}
	}

    return false;
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const
  {
    set<VertexT>  S; // set

    if(!_LookupVertex(v)){ // searches for vertex
		for(const auto& x : adjacencyList.at(v)){ // goes to neighbors
			S.insert(x.first); // inserts neighbors
		}
	}
	 
    return S;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const
  {
	vector<VertexT>  Vertices; // creates vector
	for(const auto& y : adjacencyList){ // get all vertices
		Vertices.push_back(y.first);// inserts vertex
	}
  
    return Vertices;  // returns a copy:
  }

  //
  // dump
  // 
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const
  {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << NumVertices() << endl;
    output << "**Num edges: " << NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
	int i = 0;
    for (const auto& o : adjacencyList)
    {
      output << " " << i++ << ". " << o.first << endl;
    }

    output << endl;
    output << "**Edges:" << endl;
    for (const auto& z : adjacencyList)
    {
      //output << " row " << row << ": ";
	  output << z.first << "'s edges " << endl;
      for (const auto& i : z.second)
      {
		output << z.first << " " << i.first << " " << i.second << endl;
        
      }

      output << endl;
    }

    output << "**************************************************" << endl;
  }

};