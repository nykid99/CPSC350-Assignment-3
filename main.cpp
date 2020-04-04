#include <iostream>
#include "GenStack.h"
#include <string>
#include <fstream>
using namespace std;

bool closed(char opener,char closer)
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
	ifstream inFile;
	GenStack<char> X;
	string line;
	int errorLine = 0;
  inFile.open(filename);
	if (inFile.fail()){
    cerr << "Error opening file" << endl;
    cout << "exiting program" << endl;
    exit(1);
  }

  if(inFile){  //adds the openers to the stack
		 //file is reopnede here
    while(getline(inFile, line)){
			errorLine++;          //errorline incremented
			if(X.isFull()){
				while(X.isFull()){
					X.dynamicStack();
				}
			}
			else{
				for(int i = 0; i < line.length(); i++){
	        if(line[i] == '(' || line[i] == '{' || line[i] == '['){
						X.push(line[i]);
	        }
					else if(line[i] == ')' || line[i] == '}' || line[i] == ']'){
						if(X.isEmpty()){
							cout << "there may be standalone closers or openers on line " << errorLine << endl; //prepares the code from getting stuck on )(
							exit(1);
						}
						else if((!closed(X.peek(),line[i]))){
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
						else{
							X.pop();
						}
					}
	      }
			}
    }
		if(inFile.eof() && !X.isEmpty()){
			cout << "Reached the end of line. missing a closer for " << X.peek() << endl;
			exit(1);
		}
    inFile.close();
		cout << endl;
		cout << "Source code is balanced" << endl;
  }

}


//"/home/CPSC350/CPSC350-Assignment-3/input.txt";

int main(int argc, char *argv[]) //main starts here
{
	string fileName = argv[1];
  string contFile;
	char decision;
	int flag = 0;
  errorCheck(fileName);
	while(flag == 0){
		string contFile;
		cout << endl;
		cout << "Would you like to process another list?" << endl;
		cout << "type y to continue, or n to exit the program:";
		cin >> decision;
		if(decision == 'y' || decision == 'Y'){
			cout << "you have decided to process another list" << endl;
			cout << endl;
			cout << "please enter the Absolute or the relative path of the input file: ";
			cin >> contFile;
			errorCheck(contFile);
		}
		else if(decision == 'n' || decision == 'N'){
			cout << "Exiting Program" << endl;
			flag = 1;
		}
		else{
			cout << "Wrong Input! Try again.";
			cout << endl;
		}
	}

  return 0;
}
