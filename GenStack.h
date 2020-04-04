// # Cpsc350-Assignment-3
// Kenneth Cho
// 2325383
// kecho@chapman.edu
// cpsc350-1
// This is the header file for the GenStack template class

#include <iostream>
#include <string>
using namespace std;

class StackException{ //stack exception class that will be used if user is trying to pop an empty stack
public:
  StackException(const string &error)
  :errMsg(error){}
  string getError(){return errMsg;}
private:
  string errMsg;
};

template <typename T>
class GenStack{
private:
  int mSize;               //max size of GenStack
  int top;                 //variable to keep track of indexes representing the top of our stack
public:
  GenStack();             //default constructor
  GenStack(int maxSize);  //overloaded constructor with 1 argument
  ~GenStack();
  void push(T data);     // insert
  void dynamicStack();   //increases size of stack
  T pop();               //returns top and removes it
  bool isFull();         //checks if stack is full//"/home/CPSC350/CPSC350-Assignment-3/input.txt";
  bool isEmpty();        //checks if stack is empty
  T peek();              //returns the top
  T *myArray;            //pointer to myArray
};

//this here is the cpp

template <typename T>
GenStack<T>::GenStack()//default constructor
{
  myArray = new T[128]; //myArray with size 128
  mSize = 128;          //size is 128
  top = -1;//top is -1
};

template <typename T>
GenStack<T>::GenStack(int maxSize){ //overloaded constructor
  myArray = new T[maxSize];
  mSize = maxSize;
  top = -1;
}
template <typename T>
GenStack<T>::~GenStack() //destructor
{
  delete [] this->myArray;
};

template <typename T>
void GenStack<T>::push(T data){ //pushes data to stack
  if(isFull()){
    dynamicStack(); //if stack is full it calls dynamicStack
    }
  else{
    myArray[++top] = data;
  }
}
template <typename T>
T GenStack<T>::peek(){ //peeks the top
  if(top==-1){
    cout << "Stack is empty"<< endl;
  }
  return myArray[top];
}
template <typename T>
T GenStack<T>::pop(){ //returns top and removes it
  if(isEmpty()){
    throw StackException("Stack Exception:Attempting to pop an empty stack");;
  }
  else{
    return myArray[top--];
    top --;
  }
  //must check if this is empty
}

template <typename T>
bool GenStack<T>::isEmpty(){ //checks if stack is empty
  if (top == -1){
    return true;
  }
  else{
    return false;
  }
}
template <typename T>
bool GenStack<T>::isFull(){ //checks if stack is full
  return (top == mSize-1);
}

template <typename T>
void GenStack<T>::dynamicStack(){ //creates a new array, copies values from myArray and makes that array myArray.
  T *newArray = new T[mSize+6];
  for (int i = 0; i < mSize; ++i){
    newArray[i] = myArray[i];
  }
}
