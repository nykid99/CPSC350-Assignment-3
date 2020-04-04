// # Cpsc350-Assignment-3
// Kenneth Cho
// 2325383
// kecho@chapman.edu
// cpsc350-1
// This is the main.cpp file for the program


#include <iostream>
#include "GenStack.h"
#include <string>
#include <fstream>
using namespace std;

bool closed(char opener,char closer) //checks if the closer and the opener are the correct pair
{
if(opener == '(' && closer == ')'){
	return true;
}
else if(opener == '{' && closer == '}'){
	return true;
}
else if(opener == '[' && closer == ']'){
	return true;
}
return false;
}


void errorCheck(string filename){ //checks the error of a file
ifstream inFile;                  //ifsteram created
GenStack<char> X;                 //GenStack created
string line;                      //holds every line in the file as a string
int errorLine = 0;								//errorLine
inFile.open(filename);           //attempts to open the file
if (inFile.fail()){               //if opening the file fails, it promtps the user and exits
	cerr << "Error opening file" << endl;
	cout << "exiting program" << endl;
	exit(1);
}

if(inFile){                         //if file is opened
	while(getline(inFile, line)){     //while the end of file hasn't been reached yet
		errorLine++;          //errorline incremented
		if(X.isFull()){       //if stack is full
			while(X.isFull()){
				X.dynamicStack();  //stack is increased through dynamicStack
			}
		}
		else{//if stack isn't full
			for(int i = 0; i < line.length(); i++){
				if(line[i] == '(' || line[i] == '{' || line[i] == '['){ //if a character in a line is an opener, it pushes to X stack
					X.push(line[i]);
				}
				else if(line[i] == ')' || line[i] == '}' || line[i] == ']'){ // if character is a closer it proceeds to this
					if(X.isEmpty()){
						cout << "there may be standalone closers or openers on line " << errorLine << endl; //prepares the code from getting stuck on things like )( or only having closers
						exit(1); //exits program
					}
					else if((!closed(X.peek(),line[i]))){ //checks if closers and openers are the correct pair
						if(X.peek() == '('){
							cout << "line: " << errorLine << " expected ) and found " << line[i] << endl;
						}
						else if(X.peek() == '{'){
							cout << "line: " << errorLine << " expected } and found " << line[i] << endl;
						}
						else if(X.peek() == '['){
							cout << "line: " << errorLine << " expected ] and found " << line[i] << endl;
						}
						exit(1);
					}
					else{ //if nothing's wrong, it removes the element at the top
						X.pop();
					}
				}
			}
		}
	}
	if(inFile.eof() && !X.isEmpty()){ //if the file has reached the end but there are still elements in X, it moves to this
		cout << "Reached the end of line. missing a closer for " << X.peek() << endl;
		exit(1); //exits
	}
	inFile.close();//file closed
	cout << endl; //if nothing was wrong, it prompts the user that the source code is balanced
	cout << "Source code is balanced" << endl;
}

}


//"/home/CPSC350/CPSC350-Assignment-3/input.txt";

int main(int argc, char *argv[]) //main starts here
{
string fileName = argv[1]; //stores argument as a string
char decision;             //character that decides whether a program should continue
int flag = 0;              //integer that allows the program to enter the while loop
errorCheck(fileName);      //errorcheck is run with the filename provided through the argument
while(flag == 0){
	string contFile; //string that stores filename that the user will specify again
	cout << endl;
	cout << "Would you like to process another list?" << endl;
	cout << "type y to continue, or n to exit the program:";
	cin >> decision; //if user types in y, it processes another list
	if(decision == 'y' || decision == 'Y'){
		cout << "you have decided to process another list" << endl;
		cout << endl;
		cout << "please enter the Absolute or the relative path of the input file: ";
		cin >> contFile;
		errorCheck(contFile);
	}
	else if(decision == 'n' || decision == 'N'){ //if user types in n, it exits the while loop
		cout << "Exiting Program" << endl;
		flag = 1;
	}
	else{ //if the input was neither a y or an n, it asks the user to try again
		cout << "Wrong Input! Try again.";
		cout << endl;
	}
}

return 0;
}
