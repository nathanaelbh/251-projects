/*main.cpp*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #07: open street maps, graphs, and Dijkstra's alg
// 
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:  
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <limits>
#include <queue>
#include <set>
#include <algorithm>
#include <fstream>


#include "tinyxml2.h"
#include "dist.h"
#include "osm.h"
#include "graph.h"


using namespace std;
using namespace tinyxml2;
const double INF = numeric_limits<double>::max();


class ordering
{
   public:
   bool operator()(const pair<long long, double>& p1, const pair<long long, double>& p2) const // priority class
   {
      if (p1.second > p2.second){
         return true;
      }
      else if(p1.second < p2.second){
         return false;
      }
      else {
         return p1.first > p2.first;
      }
   }
};


vector<long long> Dijkstra(graph<long long, double>& G, 
  long long startV, 
  map<long long, double>& distances,
  map<long long, double>& predecessors)
{
  vector<long long>  visited;
  priority_queue<pair<long long, double>, vector<pair<long long, double>>, ordering> Q;
  
  for(auto& o : G.getVertices()){
      distances[o] = INF;
	  predecessors[o] = 0;
      Q.push(make_pair(o,INF));
  }
  
  
  distances[startV] = 0;
  Q.push(make_pair(startV, 0));
  long long currentV;
  while(!Q.empty()){
     
     currentV = Q.top().first;
     Q.pop();
     
     if(distances[currentV] == INF){
        break;
     }
     else if(find(visited.begin(), visited.end(), currentV) != visited.end()){
         continue; 
     }
     else{
         visited.push_back(currentV);
     }
  
  
     set<long long> setss = G.neighbors(currentV);
     double edgeWeight;
     double alernativepath;
     for(auto& s : setss){
         G.getWeight(currentV, s, edgeWeight);
         alernativepath = distances[currentV] + edgeWeight;
         
         if(alernativepath < distances[s]){
            distances[s] = alernativepath;
			predecessors[s] = currentV;
            Q.push(make_pair(s, alernativepath));
         }
     }
  }
  
  //
  // TODO: 
  //
  // NOTE: the value of INF is predefined in "util.h", so use
  // this value to initialize the distances.
  //

  return visited;
}


//////////////////////////////////////////////////////////////////
//
// main
//
int main()
{
  map<long long, Coordinates>  Nodes;     // maps a Node ID to it's coordinates (lat, lon)
  vector<FootwayInfo>          Footways;  // info about each footway, in no particular order
  vector<BuildingInfo>         Buildings; // info about each building, in no particular order
  XMLDocument                  xmldoc;
  graph<long long, double> G;
	
  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

  string def_filename = "map.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "")
  {
    filename = def_filename;
  }

  //
  // Load XML-based map file 
  //
  if (!LoadOpenStreetMap(filename, xmldoc))
  {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }
  
  //
  // Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == Nodes.size());
  assert(footwayCount == Footways.size());
  assert(buildingCount == Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;


  //
  // TODO: build the graph, output stats:
  //
  for (const auto& o : Nodes){
	  G.addVertex(o.first);
  }
  
  double weight = 0;
	
  for (const auto& k : Footways){ // loops through footways
	  for(unsigned int f = 0; f < k.Nodes.size() - 1; f++){ // loops through node and gets the weight and addes edge
		  weight = distBetween2Points(Nodes[k.Nodes[f]].Lat,Nodes[k.Nodes[f]].Lon, Nodes[k.Nodes[f + 1]].Lat, Nodes[k.Nodes[f + 1]].Lon );
		  G.addEdge(k.Nodes[f], k.Nodes[f  + 1], weight );
		  G.addEdge(k.Nodes[f + 1], k.Nodes[f], weight);
	  }
  }
	
  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;

  //
  // Navigation from building to building
  //
  string startBuilding, destBuilding;

  cout << "Enter start (partial name or abbreviation), or #> ";
  getline(cin, startBuilding);
	
  
  
  while (startBuilding != "#")
  {
	double firstlat = 0;
    double firstlong = 0;
    double secondlat = 0;
    double secondlong = 0;
    string firstn = "";
    string secondn = "";
    bool firstfound = false;
    bool secondfound = false;
    cout << "Enter destination (partial name or abbreviation)> ";
    getline(cin, destBuilding);

	for(BuildingInfo& i : Buildings){ // loops through building 
		if(startBuilding == i.Abbrev || std::string::npos != i.Fullname.find(startBuilding) ){ // checks if its the abrev or full name
			firstlat = i.Coords.Lat; // stores all the variables 
			firstlong = i.Coords.Lon; 
			firstn = i.Fullname;
			firstfound = true;
			break;
		}
		
	}
	
	for(BuildingInfo& i : Buildings){ // loops through building for end
		if(destBuilding == i.Abbrev || std::string::npos != i.Fullname.find(destBuilding) ){ // checks
			secondlat = i.Coords.Lat; // stores all variables
			secondlong = i.Coords.Lon;
			secondn = i.Fullname;
			secondfound = true;
			break;
		}
		
	}  
	  

	  
	if(firstfound && secondfound){ // out put for nodes 
		cout << "Starting point: "  << endl;
		cout << " " << firstn;
		cout << endl;
		cout << " (" << firstlat << ", " << firstlong << ")";
		cout << endl;
		cout << "Destination point: ";
		cout << endl;
		cout << " " << secondn;
		cout << endl;
		cout << " (" << secondlat << ", " << secondlong << ")";
		cout << endl << endl;
		
		double mindiststart = INF;
		double tempstart = INF;
		double latstartnear;
		double lonstartnear;
		long long tempidstart;
		for (const auto& k : Footways){ // loops through  footway
		  for(unsigned int f = 0; f < k.Nodes.size(); f++){ // loops through nodes
			  tempstart = distBetween2Points(firstlat, firstlong, Nodes[k.Nodes[f]].Lat, Nodes[k.Nodes[f]].Lon ); // finds nearest node
			  if(tempstart < mindiststart){// checks if there is a node closer then stores variables
				  mindiststart = tempstart;
				  tempidstart = k.Nodes[f];
				  latstartnear = Nodes[k.Nodes[f]].Lat;
				  lonstartnear = Nodes[k.Nodes[f]].Lon;
			  }
		  }
		}
		
		cout << "Nearest start node:" << endl;
		cout << " " << tempidstart << endl;
		cout << " (" << latstartnear << ", " << lonstartnear << ")" <<endl;
		

		double mindistend = INF; // does same thing that was done for nearest start and does for end
		double tempend = INF;
		double latendnear;
		double lonendnear;
		long long tempidend;
		for (const auto& k : Footways){
		  for(unsigned int f = 0; f < k.Nodes.size(); f++){
			  tempend = distBetween2Points(secondlat, secondlong, Nodes[k.Nodes[f]].Lat, Nodes[k.Nodes[f]].Lon );
			  if(tempend < mindistend){
				  mindistend = tempend;
				  tempidend = k.Nodes[f];
				  latendnear = Nodes[k.Nodes[f]].Lat;
				  lonendnear = Nodes[k.Nodes[f]].Lon;
			  }
		  }
		}
		
		cout << "Nearest destination node:" << endl;
		cout << " " << tempidend << endl;
		cout << " (" << latendnear << ", " << lonendnear << ")" <<endl << endl;
		
		map<long long, double> distances;
		map<long long, double> predecessors;
		cout << "Navigating with Dijkstra..." << endl;
		Dijkstra(G, tempidstart, distances, predecessors);
		
		cout << predecessors.size();
// 		while() {// print 2nd map
// 		}
		
	}
	else if (!firstfound){
		cout << "Start building not found" << endl;
	}
	else if(!secondfound) {
		cout << "Destination building not found" << endl;
	}
	else{
		 int xwq = 10;
	}
	
	
	
	
    //
    // TODO: lookup buildings, find nearest start and dest nodes,
    // run Dijkstra's alg, output distance and path to destination:
    //


    //cout << "Start building not found" << endl;
    //cout << "Destination building not found" << endl;


    //
    // another navigation?
    //
    cout << endl;
    cout << "Enter start (partial name or abbreviation), or #> ";
    getline(cin, startBuilding);
  }

  //
  // done:
  //
  cout << "** Done **" << endl;

  return 0;
}
