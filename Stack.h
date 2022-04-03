#include<iostream>
#include<fstream>
#include<string>
using namespace std;

template<typename T>
class Stack{
	T *Arr;
	int size;
	int capacity;
	bool isFixed;

public:
	Stack();
	Stack(int);
	Stack(const Stack<T> &Other);
	void Copy(const Stack<T> &Other);
	bool push(T val);
	T pop();
	bool isEmpty();
	bool isFull();
	void ClearS();
	T Top();
	~Stack();
};

template<typename T>
Stack<T>::Stack(){
	this->capacity = 1;
	this->Arr = new T[capacity];
	this->size = 0;
	this->isFixed = false;
}

template<typename T>
Stack<T>::Stack(const Stack<T>& Other){
	Copy(Other);
}

template<typename T>
Stack<T>::Stack(int C){
	this->capacity = C;
	this->Arr = new T[capacity];
	this->size = 0;
	this->isFixed = true;
}

template<typename T>
void Stack<T>::Copy(const Stack<T>& Other){
	this->capacity = Other.capacity;
	this->size = Other.size;
	this->isFixed = Other.isFixed;
	this->Arr = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->Arr[i] = Other.Arr[i];
}

template<typename T>
bool Stack<T>::push(T Val){
	if (this->size == this->capacity){
		if (this->isFixed)
			return false;
		this->capacity *= 2;
		T* temp = new T[this->capacity];
		for (int i = 0; i < this->size; i++)
			temp[i] = this->Arr[i];
		delete[] this->Arr;
		Arr = temp;
	}
	this->Arr[this->size++] = Val;
	return true;
}

template<typename T>
T Stack<T>::pop(){
	return this->Arr[--this->size];
}

template<typename T>
bool Stack<T>::isEmpty(){
	return this->size == 0;
}

template<typename T>
bool Stack<T>::isFull(){
	return this->size == capacity;
}

template<typename T>
T Stack<T>::Top(){
	return this->Arr[this->size - 1];
}

template<typename T>
void Stack<T>::ClearS(){
	while (!this->isEmpty())
		this->pop();
}

template<typename T>
Stack<T>::~Stack(){
	delete[] this->Arr;
}