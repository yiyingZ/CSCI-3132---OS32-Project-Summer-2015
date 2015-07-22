/*
 * helpme1.cpp
 *
 *  Created on: Jun 28, 2015
 *      Author: Prime
 */

#include "helpme1.h"

/**
 * Following is the helpme implementation. It contains two methods. One for just displaying all the
 * commands. Second function is for displaying specific command detail
 *
 */
helpme1::helpme1() {

}

helpme1::~helpme1() {
	// TODO Auto-generated destructor stub
}

//Following function will display the commands using the stored file.
void showCommands(){
		ifstream ifile;
		ifile.open("command-list.txt");
	    string line;
		if(!ifile.is_open()){
			exit(EXIT_FAILURE);
		}
		string keyWord;
		while(getline(ifile, line) ){
		cout<<line<<endl;
		    }
}

//Following is the no argument function that will display the command detail depending on the user request.
void commandsDetails(){
	string search;
    cout<<"Enter keyword for which you want to see command detail";
	cin>>search;
        ifstream ifile;
		ifile.open("command-help.txt");
	    string line;
		if(!ifile.is_open()){
			exit(EXIT_FAILURE);
		}

		int check;
		string keyWord;

		while(getline(ifile, line) ){
			istringstream iss(line);
			iss>>keyWord;
			if(keyWord==search){
	              cout<<line<<endl;
	              check=-1;
		    }
		}
		if(check!=-1)
			cout<<"not found";
}

//Following is the function that will display the command detail depending on the user request. User will pass his choice as argument
void commandsDetails(string search){
	//string search;
    //cout<<"Enter keyword for which you want to see command detail";
	//cin>>search;
        ifstream ifile;
		ifile.open("command-help.txt");
	    string line;
		if(!ifile.is_open()){
			exit(EXIT_FAILURE);
		}

		int check;
		string keyWord;

		while(getline(ifile, line) ){
			istringstream iss(line);
			iss>>keyWord;
			if(keyWord==search){
	              cout<<line<<endl;
	              check=-1;
		    }
		}
		if(check!=-1)
			cout<<"not found";
}
//int main(){
	//showCommands();
//    commandsDetails("currdir");
//}
