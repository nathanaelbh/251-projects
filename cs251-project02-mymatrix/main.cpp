 #include <iostream>
#include "mymatrix.h"

using namespace std;

//test default
bool size_test1(){//keep
mymatrix<int> M; // creates 4x4 matrix
    cout << "Test for Default Constructor: " << endl;
    M._output();
    cout << endl;

    return true;
}

//test parameterized constructor
bool testmatrix() {//keep
   mymatrix<int> M(8,9); 
   mymatrix<int> M2(2,2);
   mymatrix<int> M3(9,2);
   cout << "Test for Parameterized Constructor: " << endl;
   cout << "8 X 9:" << endl ;
   M._output();
   cout << endl << "2 X 2:" << endl ;
   M2._output();
   cout << endl << "9 X 2:" << endl ;
   M3._output();
   cout << endl;
     
   return true;
}

//test scaler
bool scaler(){//keep
    cout << "Scaler Test:" << endl;
    mymatrix<int> M1;
    
    M1.at(0,0) = 1;               
    M1.at(0,1) = 2;               
    M1.at(1,0) = 5;
    M1.at(1,1) = 6;

    M1.growcols(0, 9);
    M1.grow(10,4);

    M1.at(6,0) = 1;               
    M1.at(6,1) = 2;               
    M1.at(6,0) = 5;
    M1.at(8,1) = 6;
   
    cout << "M1 before:" << endl ;
    M1._output();
    cout << endl;
    cout << "M1 after * 5:" << endl;
    M1 = M1 * 5;

    M1._output();
    cout << endl;

    return true;
}

bool checkgrow(){// keep
    mymatrix<int> M(2,2);
    cout << endl;
    cout << "Test grow:" << endl;

    M.at(0,0) = 1;                //1 2 3 4
    M.at(0,1) = 2;                //5 6 7 8 
    
    M.at(1,0) = 5;
    M.at(1,1) = 6; 
    M.grow(4, 4);
    cout << "M.grow(4, 4) grow to 4x4" << endl;
    M._output();
    cout << endl;
    M.at(1,3) = 8;
    M.grow(3,5);
    cout << "M.grow(3,5) grow to 3 rows to 5" << endl;
    M._output();
    cout << endl;
    M(3,3) = 8;
    M.grow(5,3);
    M.grow(1,5);
    cout << "M.grow(1,5) grow jagged matrix" << endl;
    M._output();
    
    cout << endl;
    M.grow(2,2);
    cout << "M.grow(2,2) stay the same: " << endl;
    M._output();
    cout << endl;
    mymatrix<int> M2 = M * 2;

    cout << endl;
    M2.grow(10,10);
    cout << "M2.grow(10,10) 10x10: " << endl;
    M2._output();

    cout << endl;

    return true;
}

bool checkforgrowcols() {// keep
  cout << "Testing growcols:"<< endl;
   mymatrix<int>M (6,7);

    M.at(0,0) = 1;                //1 2 3 4
    M.at(0,1) = 2;                //5 6 7 8 
    M.at(0,2) = 3;                //9 10 11 12
    M.at(0,3) = 4;                //13 14 15 16
   cout << "size:(6*7) = "<< M.size() << endl;
    M.growcols(0, 4);
    cout << "size:growcols(0, 4) should stay the same = "<< M.size() << endl;
    M.growcols(0, 15);
    cout << "size:M.growcols(0, 15)// 42 + 8 = "<< M.size() << endl;
    M.grow(5, 5);
    cout << "size:M.grow(5, 5)// stay the same = "<< M.size() << endl;
    
    M.at(1,0) = 5;
    M.at(1,1) = 6;
    M.at(1,2) = 7;
    M.at(1,3) = 8;
    
    M.at(2,0) = 9;
    M.at(2,1) = 10;
    M.at(2,2) = 11;
    M.at(2,3) = 12;
    
    M.at(3,0) = 13;
    M.at(3,1) = 14;
    M.at(3,2) = 15;
    M.at(3,3) = 16;
    M.growcols(0, 10);

    cout << endl;
   mymatrix<int> M2 = M * 2;
   cout << "size M: should be the same = "<< M.size() << endl;
   M._output();
   cout << endl;
   cout << "size M2: should stay the same = "<< M2.size() << endl;
   M2._output();

  return true;
}

bool checknumcolsandnumrows(){//keep
    cout<< "Test numcols and numrows: "<< endl;
    mymatrix<int> M(2,2);
    M.growcols(0, 8);
    M.grow(5, 5);

    M.at(0,0) = 1;                //1 2 3 4
    M.at(0,1) = 2;                //5 6 7 8 
    M.at(0,2) = 3;                //9 10 11 12
    M.at(0,3) = 4;                //13 14 15 16
    
    M.at(1,0) = 5;
    M.at(1,1) = 6;
    M.at(1,2) = 7;
    M.at(1,3) = 8;
    
    M.at(2,0) = 9;
    M.at(2,1) = 10;
    M.at(2,2) = 11;
    M.at(2,3) = 12;
    
    M.at(3,0) = 13;
    M.at(3,1) = 14;
    M.at(3,2) = 15;
    M.at(3,3) = 16;

    M._output();
    cout << endl;

    cout << "numrows: " << M.numrows() << endl << "numcols:" << M.numcols(2) << endl << endl;
  
    return true;
}


bool multtiplymatrix() {//keep
  cout << "Check Matrix Multipy: " << endl;
  mymatrix<int> M1(2, 4);
  mymatrix<int> M2(4, 5);
 
  M1(0, 0) = 1;
  M1(0, 1) = 3;
  M1(0, 2) = 5;
  M1(1, 0) = 2;
  M1(1, 1) = 4;
  M1(1, 2) = 6;
 
  M2(0, 0) = 1;
  M2(0, 1) = 2;
  M2(0, 2) = 3;
  M2(1, 0) = 4;
  M2(1, 1) = 5;
  M2(1, 2) = 6;
  M2(2, 0) = 7;
  M2(2, 1) = 8;
  M2(2, 2) = 9;
 
  mymatrix<int> M3;
 
  M1._output();
  cout << endl;
  M2._output();
  cout << endl;
  
  M3 = M1 * M2;
  M3._output();

  return true;
}


int main(){
    size_test1(); //test default constructor
    testmatrix(); // test parameterized matrix
    scaler(); // tests scaler function
    checknumcolsandnumrows(); //test numcols and rows
    checkforgrowcols(); //checks growcols
    checkgrow(); // checks grow
    multtiplymatrix();
  
    return 0;
}