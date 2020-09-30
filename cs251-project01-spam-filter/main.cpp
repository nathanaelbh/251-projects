#include <iostream>
#include <fstream>
#include <string>

#include "ourvector.h"

using namespace std;

string filename;

//ourvector<string> inputWords(string filename);

void load(ourvector<string>& words, string filename)
{


	//
	if (words.size() > 0) {
		words.clear();
	}
	ifstream infile(filename);
	string word;
	infile >> word;
	while (!infile.eof()) {

		words.push_back(word);
		infile >> word;

	}
}


void display(ourvector<string>& V) {
	for (int i = 0; i < V.size(); i++) {
		cout << V[i] << endl;
	}


	return;
}

/*
//bool binarySearch(string domain, string username, ourvector<string>& words)
bool binarySearch(string domain, string username)

{
	//
	// TODO:
	//

  string domaint;
  string usernamet;




	 int mid = 0;
   int low = 0;
   int high = binaryvec.size() - 1  ;
   string temp;
   //cout << "this is the word size" << high << endl;
   while (high >= low) {
	  mid = (high + low) / 2;
	  temp = binaryvec[mid];

	  size_t pos = temp.find(":");
	  usernamet = temp.substr (pos+1);
	  domaint = temp.substr (0, pos);
	  //string input=username+"@"+domain;
	  //string candidate=usernamet+":"+domaint;
	  //cout << domain << " " << domaint << " " << username << " " << usernamet << endl;
	  if( (domain==domaint && username==usernamet) || (usernamet=="*" && domain==domaint) )
	  {
	  return true;
	  }
	  // else if(input<candidate)
	  // {
	  //     high=mid-1;
	  // }
	  // else
	  // {
	  //     low=mid+1;
	  // }


	  //cout << domaint << "this is domaint" << endl;

	  // if ((domain == domaint) && (username == usernamet)) {
	  //   return true;
	  //    //low = mid + 1;
	  // }

	  // else if(domain == domaint)
	  // {
	  //   if(username < usernamet) {
	  //       low = mid + 1;
	  //      }
	  //   else if(username > usernamet) {
	  //     high = mid - 1;
	  //   }
	  // }

	  // else if(username == usernamet)
	  // {
	  //    if(domain < domaint)
	  //    {
	  //       low = mid + 1;
	  //     }
	  //    else if ( domain > domaint) {
	  //      high = mid-1;
	  //    }
	  // }
	  //  else{
	  //   return false;

		 // high = mid-1;
		//low = mid + 1;

	  //}




	  else if (((domain > domaint) || (domain == domaint)) && (username > usernamet)) {

		 low = mid+1;
	  }
	  else {// (((domain < domaint) || (domain == domaint)) && (username < usernamet)){
	   //low = mid+1;
		high = mid - 1;
	  }
	  //else {      //}
   }


	return false;
}
*/

bool newsearch(ourvector<string>& list, string input) {
	int mid = 0;
	int low = 0;
	int high = list.size() - 1;
	string templist;

	size_t pos = input.find('@');
	string usernamet = input.substr(0, pos);
	string domaint = input.substr(pos+1);
	input = domaint + ":" + usernamet;

	while (low <= high) {
		mid = (high + low) / 2;
		templist = list[mid];
		pos = templist.find(':');
		string usernamet = templist.substr(pos + 1);
		string domaint = templist.substr(0, pos);
		
		if (templist < input) {
			low = mid + 1;
		}
		else if (templist > input) {
			high = mid - 1;
		}
		else if ((templist == input) || (usernamet == "*")) {
			return true;
		}

	}
  if(usernamet != "*")
  {
    newsearch(list, "*:" + usernamet);
  }
	return false;


}



void check(string input, ourvector<string>& list) {
	//string domain;
   // string username;

	//ourvector<string> theCheck;
	//string checkEmail;

	//cin >> checkEmail;
	//cout << checkEmail << endl;

	//theCheck = inputWords(filename);

	// size_t pos = checkEmail.find("@");
	// domain = checkEmail.substr (pos+1); 
	// username = checkEmail.substr (0, pos);

	//cout << domain << " the split " << username<< endl;
	string search;


	//newsearch

	if (newsearch(list, input)) {
		cout << ": found! by usernane 1" << endl;
	}
	else
	{
		if (newsearch(list, input)) {
			cout << ": found! y star" << endl;
		}
		else {
			cout << ": not found?" << endl;
		}
	}


	return;
}


int filter(ourvector<string>& filtervec) {

	string emailList;
	string outputList;
	string index, email, title, tempword;
	string domainf, usernamef;
	int spam = 0;
	int pross = 0;

	cin >> emailList;
	cin >> outputList;

	//cout << "hey";

	//cout << emailList << outputList << endl;
	ifstream infile;
	infile.open(emailList);

	if (!infile.is_open()) {
		cout << "**Error, unable to open" << endl;
		return 1;
	}


	ofstream output;
	output.open(outputList);

	size_t posf = email.find("@");
	domainf = email.substr(posf + 1);
	usernamef = email.substr(0, posf);


	while (!infile.eof()) {
		infile >> index;
		infile >> email;
		getline(infile, title);

		// size_t posf = email.find("@");
		// domainf = email.substr (posf+1); 
		// usernamef = email.substr (0, posf);


		// size_t posf = email.find("@");
		//  domainf = email.substr (posf+1); 
		//  usernamef = email.substr (0, posf);


		if (!infile.fail()) {

      
			if (!newsearch(filtervec, email))
			{
        //if ()
				// cout << "hello";
				// outputList << index << " " << email << title << endl;
				output << index << " " << email << title << endl;
				spam++;
			}
			pross++;
		}




		//infile >> tempword; 

	}
	cout << "not spam: " << spam << "pross:" << pross << endl;
	output.close();
	infile.close();
	return 2;
}



int main() {

	ifstream inFS;
	string filename;
	string command;
	string textFile;
	bool end = 1;
	ourvector<string>  V;

	//username = email.substr (0, pos);



	   // cout << "Enter a command or # to exit>";  
	   // cin >> command; 
	   // cin >> textFile; 

	while (end) {
		cout << "Enter a command or # to exit>";
		cin >> command;

		if (command == "load") {
			// cout << "you typed load" << endl;
			cin >> filename;
			load(V, filename);


			//cout << command << textFile << endl; 
			//cout << command << endl;
		}
		else if (command == "display") {
			// cout << "you typed display" << endl;
			display(V);

		}
		else if (command == "check") {
			//cout << "you typed check" << endl;
			string domain;
			string username;

			string checkEmail;
			cin >> checkEmail;

			// size_t pos = checkEmail.find("@");
			// domain = checkEmail.substr (pos+1); 
			// username = checkEmail.substr (0, pos);

			check(checkEmail, V);

		}
		else if (command == "filter") {
			cout << "you typed filter" << endl;
			filter(V);

		}
		else if (command == "#") {
			end = 0;
		}
		else {
			cout << "**invalid command" << textFile << endl << endl;
		}
	}


	//     cout << "please enter filename> ";
	//  cin >> filename;  // input filename:
	//  cout << endl;
	//   inFS.open(filename);
	//    while (!inFS.eof()) {
	//     inFS >> filename;
	//     if (!inFS.fail()) {
	//        cout << ": " <<  filename << endl;
	//     }



	//  }


	return 0;
}