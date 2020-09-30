/*hash.h*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <string>

using namespace std;

bool isNumeric(string s);
int Hash(int theDate, int N);
unsigned long Hashabrev(string abrv, int Na);
int Hashtrip(int trip_id, int Naa);