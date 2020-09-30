/*main.cpp*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "hash.h"
#include "hashmap.h"

using namespace std;


//
// LotteryData
// 
// Mega millions lottery winning numbers which is 
// 5 numbers + mega ball number + possible multiplier.
// 

struct TripData // trip struct
{
	int tripid;
	string starttime;
	string stoptime;
	string bikeid;
	int duration;
	int from;
	int to;
	string identifies;
	int birthyear;
	
	TripData()
	{
		tripid = 0;
		starttime = "";
		stoptime = "";
		bikeid = "";
		duration = 0;
		from = 0;
		to = 0;
		identifies = "";
		birthyear = 0;
	}
	
};

struct StationData // station struct 
{
	//string id,abbrev,fullname,latitude,longitude,capacity,online_date;
	int id;
	string abbrev;
	string fullname;
	double latitude;
	double longitude;
	int capacity;
	string online_date;
	
	StationData()
	{
		id = 0;
		abbrev = "";
		fullname = "";
		latitude = 0;
		longitude = 0;
		capacity = 0;
		online_date = "";
		
// 		id = "";
// 		abbrev = "";
// 		fullname = "";
// 		latitude = "";
// 		longitude = "";
// 		capacity = "";
// 		online_date = "";
	}
};

//
// string2int
// 
// Converts a string to an integer, unless string is empty, in
// which case 0 is returned.
// 
int string2intm(string s) // string to int
{
	if (s == "")
		return 0;
	else
		return stoi(s);
}

int string2double(string s)
{
	if (s == "")
		return 0;
	else
		return stod(s);
}


//
// inputData
// 
// Given a filename denoting lottery winning numbers,
// inputs that data into the given hash table.
// 
bool inputData2(string filename, hashmap<int, TripData>& tripsById, hashmap<int, int>& bikesById, int& counttrip, int& countB){
	ifstream  infile(filename); // read file
	
	//cout << "Reading " << filename << endl;
	
	if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	//int count = 0;
	
	while (getline(infile, line))
	{
		stringstream s(line); // stores every member into struct
		
		string tripid2, starttime2, stoptime2, bikeid2, duration2, from2, to2, identifies2, birthyear2;
		
		getline(s, tripid2, ',');  // first value => region
		getline(s, starttime2, ',');
		getline(s, stoptime2, ',');
		getline(s, bikeid2, ',');
		getline(s, duration2, ',');
		getline(s, from2, ',');
		getline(s, to2, ',');
		getline(s, identifies2, ',');
		getline(s, birthyear2, ',');
		
		TripData fd;
		
		tripid2.erase(0,2); // seperate to int
		
		fd.tripid = string2intm(tripid2); // turn to int
		fd.starttime = starttime2 ;
		fd.stoptime = stoptime2;
		fd.bikeid = bikeid2;
		fd.duration = string2intm(duration2); // store members
		fd.from = string2intm(from2);
		fd.to = string2intm(to2);
		fd.identifies = identifies2;
		fd.birthyear = string2intm(birthyear2);
		
		int temp1 = string2intm(tripid2); // temp
		
		tripsById.insert(temp1, fd, Hashtrip); // inserts into map
		
		bikeid2.erase(0,1);  // turns to int
		int temp2 = string2intm(bikeid2);
		int store = 0; 
		if(!bikesById.search(temp2, store, Hashtrip)){ // checks if bike is in map
			countB++;
		}
		bikesById.insert(temp2, store + 1, Hashtrip); // stores in map
		
		
		
		counttrip++; // trip counter
	}
	
	return true;
}



bool inputData(string filename, hashmap<int, StationData>& stationsById, hashmap<string, StationData>& stationsByAbbrev, int& countfs)
{
	ifstream  infile(filename);
	
	//cout << "Reading " << filename << endl;
	
	if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	//int count = 0;
	
	while (getline(infile, line)) // reads file
	{
		stringstream s(line); // stores the members
		
		string id2, abbrev2, fullname2, latitude2, longitude2, capacity2, online_date2;
		
		//
		// format: date,xx xx xx xx xx,yy,z
		// 
		// NOTE: z may be missing (the multiplier)
		// 
		getline(s, id2, ',');  // first value => region
		getline(s, abbrev2, ',');   // second value => country
		getline(s, fullname2, ','); // stores into struct
		getline(s, latitude2, ',');
		getline(s, longitude2, ',');   // second value => country
		getline(s, capacity2, ',');
		getline(s, online_date2, ',');
		
		// we have input the 4 values, and since we are not
		// doing any arithmetic, we can just store them as
		// strings.  If the multiplier is missing then the
		// string is "", which is fine.
		
		//
		// store into hash table
		// 
		StationData ld; // makes temp struct
		
		ld.id = string2intm(id2); //stores members 
		ld.abbrev = abbrev2;
		ld.fullname = fullname2;
		ld.latitude = stod(latitude2);
		ld.longitude = stod(longitude2);
		ld.capacity = string2intm(capacity2);
		ld.online_date = online_date2;
		
		int temp = string2intm(id2); // changes type

		stationsById.insert(temp, ld, Hash); // inserts to map
		stationsByAbbrev.insert(abbrev2, ld, Hashabrev);
		
		countfs++; // count
	}
	
	
	//cout << "# data lines: " << countfs << endl;
	
	return true;  // we have data to be processed:
}


int main()
{
	hashmap<int, StationData> stationsById(10000);// all maps
	hashmap<string, StationData> stationsByAbbrev(10000);
  hashmap<int, TripData> tripsById(2500000);
  hashmap<int, int> bikesById(50000);
	
	cout << "** DIVVY analysis program **" << endl;
	cout << endl;
	
	int countfs = 0; // counts
	int counttrip = 0;
	int countB = 0;
	
	string sfile = "stations.csv"; // file names
	string tfile = "trips.csv";
	string filenotenters, filenotentert;
	
	
	cout << "Enter stations file> "; //enter files
	getline(cin, filenotenters);
	cout << "Enter trips file> ";
	getline(cin, filenotentert);
	
	if (filenotenters != "")// checks if empty
		sfile = filenotenters;
	
	if (filenotentert != "")
		tfile = filenotentert;
	
	bool success1 = inputData(sfile, stationsById, stationsByAbbrev, countfs); // inserts data
	bool success2 = inputData2(tfile, tripsById, bikesById, counttrip, countB);
	
	if (!success1)
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}
	
	if (!success2)
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}
	
	cout << endl;
	
	cout << "Reading " << sfile << endl;
	cout << "Reading " << tfile << endl;
	
	cout << endl;
	
	
	cout << "# of stations: " << countfs << endl;
	cout << "# of trips: " << counttrip << endl;
  cout << "# of bikes: " << countB << endl;
	
	cout << endl;
	
	string command;
	cout << "Please enter a command, help, or #> "; 
	getline(cin, command);
	
	
	
	while (command != "#")
	{
		
		StationData st;
		TripData ot;
		
		if (command == "help"){                                               // help
			cout << "Avalible commands:" << endl;
			cout << " Enter a station id (e.g. 341)" << endl;
			cout << " Enter a station abbreviations (e.g. Adler)" << endl;
			cout << " Enter a trip id (e.g. Tr10426561)" << endl;
			cout << " Enter a bike id (e.g. B5218)" << endl;
			cout << " Nearby stations (e.g. nearby 41.85 -87.62 0.5)" << endl;
			cout << " Similar trips (e.g. similar Tr10424639 0.3)" << endl;
		}
		
		else if (isNumeric(command)){                                        // station id
			int isnumsearch = string2intm(command);
			bool found = stationsById.search(isnumsearch, st, Hash);
			if(!found){
				cout << "Station not found";
			}
			else {
				cout << "Station: " << endl;
				cout << " ID: " << st.id << endl;
				cout << " Abbrev: " << st.abbrev << endl;
				cout << " Fullname: " << st.fullname << endl;
				cout << " Location: (" << st.latitude << ", " << st.longitude << ")" << endl;
				cout << " Capacity: " << st.capacity << endl;
				cout << " Online date: " << st.online_date << endl;
			}	
		}
		
		else if ( (command.length() >= 3) && (command.substr(0,2) == "Tr") && isNumeric(command.substr(2)) ){ // trip id
			command.erase(0,2);
			int isnumtrip = string2intm(command);
			bool foundtrid = tripsById.search(isnumtrip, ot, Hashtrip);
			if(!foundtrid){
				cout << "Trip not found";
			}else {
				cout << "Trip:" << endl;
				cout << " ID: Tr" << ot.tripid << endl;
				cout << " Starttime: " << ot.starttime << endl;
				cout << " Bikeid: " << ot.bikeid << endl;
				
				cout << " Duration: ";
						int total, seconds, hours, minutes;
						total = ot.duration;
						minutes = total / 60;
						seconds = total % 60;
						hours = minutes / 60;
						minutes = minutes % 60;
						if (hours > 0)
							cout << hours << " hours, ";
						if (minutes > 0)
							cout << minutes << " minutes, ";
						cout << seconds << " seconds" << endl;
				
				stationsById.search(ot.from, st, Hash);
				cout << " From station: " << st.abbrev << " (" << ot.from << ")" << endl;
				stationsById.search(ot.to, st, Hash);
				cout << " To station: " << st.abbrev << " (" << ot.to << ")" <<  endl;
				
				cout << " Rider identifies as: " << ot.identifies << endl;
				if (ot.birthyear == 0)
					cout << " Birthyear: " << endl;
				else
				cout << " Birthyear: " << ot.birthyear << endl;
			}
			//cout << " <<trip id: " << command;
			
		}
		
		else if ( (command.length() >= 2) && (command.substr(0,1) == "B") && isNumeric(command.substr(1))){ // bike id
			//cout << "bike id: " << command;
			int tempint;
			command.erase(0,1);
			int isnumbike = string2intm(command);
			bool foundbikeid = bikesById.search(isnumbike, tempint, Hashtrip);
			if(!foundbikeid){
				cout << "Bike not found";
			}
			else {
				cout << "Bike:" << endl;
				cout << " ID: B" << command << endl;
				cout << " Usage: " << tempint << endl;
			}
		}
		
		else if(command.substr(0,6) == "nearby"){
			string str1, str2, str3, str4;
			stringstream s(command);
			getline(s, str1, ' ');
			getline(s, str2, ' ');
			getline(s, str3, ' ');
			getline(s, str4, ' ');
			cout << "Stations within " << str4 << " miles of (" << str3 << ", " << str2 << ")" << endl;
			
		}
		
		else { // station abbreviations
			bool foundabr = stationsByAbbrev.search(command, st, Hashabrev);
			if(!foundabr){
				cout << "Station not found";
			}
			else {
				cout << "Station: " << endl;
				cout << " ID: " << st.id << endl;
				cout << " Abbrev: " << st.abbrev << endl;
				cout << " Fullname: " << st.fullname << endl;
				cout << " Location: (" << st.latitude << ", " << st.longitude << ")" << endl;
				cout << " Capacity: " << st.capacity << endl;
				cout << " Online date: " << st.online_date << endl;
			}
			
			//cout << "string: " << command;
		}
		
		
		
		cout << endl;
	  cout << "Please enter a command, help, or #> ";
	  getline(cin, command);
		
	}
	
	return 0;
}
