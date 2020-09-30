/*hash.cpp*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <iostream>
#include <string>
#include <cctype>  /*isdigit*/
#include <regex>   /*regular expressions*/

#include "hash.h"
#include "hashmap.h"

using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
//

int string2int(string s)
{
	if (s == "")
		return 0;
	else
		return stoi(s);
}

bool isNumeric(string s)
{
	//
	// A string is numeric if it contains 1 or more digits, so let's
	// use a regular expression to check that.
	//
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [[:d:]] means match a single digit.
	// The + means match the preceding sub-expression 1 or more times.
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}


//
// Hash
// 
// Hashes the given date "mm-dd-year" and returns an array index.
// If the date falls within the range "01/01/2000" .. "12/31/2099", 
// inclusive, a valid array index is returned in the range 0..N-1.
// If the date falls outside this range, or the date is not formatted
// mm/dd/yyyy, then -1 is returned.  If N >= 37200 then the function 
// is a perfect hash function; if N < 37200 then collisions will occur.
// 
// NOTE: the actual date is not validated, e.g. the function does not
// validate that 02/29/2020 is a leap year.  Validation is limited to 
// checking that the format is mm/dd/yyyy, where 1<=mm<=12, 1<=dd<=31,
// and 2000<=yy<=2099.
// 
// NOTE: the total # of combinations is 365.25 days per year * 100 total
// years.  That's 36,525 possible permutations.  We don't need to be that
// precise.  To simplify things, we'll assume 12 months per year, 31 days
// per month, across 100 years.  That's 12 * 31 * 100 = 37,200 possible
// permutations.  If N >= 37,200, the hash function is perfect and will
// return a value in the range -1 .. 37199, inclusive.
//
int Hash(int theDate, int N)
{
	
	//int temp = string2int(theDate);
	
	int index = (theDate - 1) * 10;

	return index % N;
}

unsigned long Hashabrev(string s, int Na){
	  unsigned long hash = 5381;
    unsigned int size = s.length();
    unsigned int i = 0;
    for (i = 0; i < size; i++) {
        hash = ((hash << 5) + hash) + (s[i]); // hash * 33 + c 
    }

    return hash % Na;
}

int Hashtrip(int trip_id, int Naa){
	
// 	if(trip_id.length() < 2){
// 		return -1;
// 	}
	
	//trip_id.erase(0,2);
	
// 	if(!isNumeric(trip_id)){
// 		return -1;
// 	}
	
	//int temp1 = string2int(trip_id);
	//int inndex = trip_id % Naa;
	
	return trip_id % Naa;
}


//
// Hash
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//

