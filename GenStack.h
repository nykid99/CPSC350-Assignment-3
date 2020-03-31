#include <iostream>
#include <string>
using namespace std;

template <typename T>
class GenStack{
private:
  int mSize; //max size of myStack
  int top; //variable to keep track of indeces representing the top of our stack
public:
  GenStack();//default constructor
  GenStack(int maxSize);//overloaded constructor
  ~GenStack();
  void push(T data); // insert
  T pop(); //remove
  bool isFull();
  bool isEmpty();
  T peek();
  T *myArray;
};

//this here is the cpp

template <typename T>
GenStack<T>::GenStack()//default constructor
{
  myArray = new T[128];
  mSize = 128;
  top = -1;
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
void GenStack<T>::push(T data){ //push method
  if(isFull()){
    cout << "it is full" << endl;
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
T GenStack<T>::pop(){ //pop
  if(isEmpty()){
    cout << "Stack is empty" << endl;
  }
  else{
    return myArray[top--];
    top --;
  }
  //must check if this is empty
}

template <typename T>
bool GenStack<T>::isEmpty(){
  if (top == -1){
    return true;
  }
  else{
    return false;
  }
}
template <typename T>
bool GenStack<T>::isFull(){
  return (top == mSize-1);
}
