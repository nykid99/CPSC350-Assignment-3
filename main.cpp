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

int main(int argc, char *argv[]) //main starts here
{
  string line;
  string filename = "input.txt";
  int errorLine = 0;
  ifstream inFile;
	GenStack<char> X;
  inFile.open(filename);


  if (inFile.fail()){
    cerr << "Error opening file" << endl;
    cout << "exiting program" << endl;
    exit(1);
  }
  else if(inFile.is_open()){  //adds the openers to the stack
		 //file is reopnede here
    while(getline(inFile, line)){
			errorLine++;          //errorline incremented
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
		if(inFile.eof() && !X.isEmpty()){
			cout << "Reached the end of line. missing a closer for " << X.peek() << endl;
			exit(1);
		}
    inFile.close();
		cout << "source code balanced" << endl;
  }
	///////////////////

  string sample = argv[1];
  return 0;
}
