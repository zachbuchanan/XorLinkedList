#ifndef xorlinkedlist_hpp
#define xorlinkedlist_hpp

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class xNode {
public:
	xNode(T _data = 0) : data(_data) {}
	xNode<T>* getNpx() { return npx; }
	void assignNpx(xNode<T>* ptr){ npx = ptr; }
	T getData(){ return data; }
private:
	T data;
	xNode<T>* npx;
};

template<typename T>
class XORLinkedList {
public:
	XORLinkedList() : head(nullptr), tail(nullptr), length(0) {}
	XORLinkedList(T data);
	XORLinkedList(T ar[], int size);
	XORLinkedList(vector<T> v);
	XORLinkedList(XORLinkedList<T>& actual);
	~XORLinkedList();
	void add(T data);
	T pop();
	void printHeadAndTail();
	void printAll();
	void reversePrintAll();
	T getAtIndex(int idx);
	int getLength(){ return length; }
	void swap(XORLinkedList<T>& rhs);
	void insert(T data, int idx);
	//operators
	XORLinkedList<T>& operator=(XORLinkedList<T> rhs);
	T operator[](int idx);
private:
	xNode<T>* head;
	xNode<T>* tail;
	int length;
	//funcs
	xNode<T>* getNodeAtIndex(int idx);
	xNode<T>* XOR(xNode<T>* a, xNode<T>* b);
	xNode<T>* reverseTraverse(int j);
	xNode<T>* getPrevious(xNode<T> *current, xNode<T> *next);
	xNode<T>* getNext(xNode<T> *current, xNode<T> *previous);
};

template<typename T>
XORLinkedList<T>::XORLinkedList(T data){
	xNode<T>* temp = new xNode<T>(data);
	head = tail = temp;
	length = 1;
}
template<typename T>
XORLinkedList<T>::XORLinkedList(T ar[], int size){
	xNode<T>* temp = new xNode<T>(ar[0]);
	head = tail = temp;
	length = 1;
	for(int i = 1; i < size; ++i){
		this->add(ar[i]);
	}
}

template<typename T>
XORLinkedList<T>::XORLinkedList(vector<T> v){
	for(auto it = v.begin(); it != v.end(); ++it){
		this->add(*it);
	}
}

template<typename T>
XORLinkedList<T>::~XORLinkedList(){
	xNode<T> *prev = nullptr;
	while(head != tail){
		xNode<T> *temp = head;
		head = XOR(prev,head->getNpx());
		if(prev != nullptr){
			delete prev;
		} 
		prev = temp;
	}
	delete prev;
	delete tail;
}

template <typename T>
XORLinkedList<T>::XORLinkedList(XORLinkedList<T>& actual){
	int size = actual.getLength();
	for(int i = 0; i < size; ++i){
		this->add(actual.getAtIndex(i));
	}
}

template<typename T>
T XORLinkedList<T>::getAtIndex(int idx){
	try{
		if(idx >= length){
			throw idx;
		} else {
			xNode<T>* current = head;
			xNode<T>* prev = nullptr;
			for(int i = 0; i < idx; ++i){
				xNode<T>* temp = current;
				current = XOR(prev, current->getNpx());
				prev = temp;
			}
			return current->getData();
		}
	}
	catch(int x){
		cout << "OUT OF RANGE\n";
	}
	return 0;
}

template<typename T>
void XORLinkedList<T>::add(T data){
	xNode<T>* temp = new xNode<T>(data);
	if(head == nullptr){
		head = tail = temp;
		temp->assignNpx(nullptr);
	} else {
		if(tail->getNpx() == nullptr){	//there is only one node
			tail->assignNpx(XOR(nullptr, temp));
		} else {
			xNode<T> *prev = XOR(tail->getNpx(), nullptr);
			tail->assignNpx(XOR(prev, temp));
		}
		temp->assignNpx(XOR(tail, nullptr));
		tail = temp;
	}
	++length;
}

template <typename T>
T XORLinkedList<T>::pop(){
	T val = tail->getData();
	xNode<T> *temp = tail;
	tail = this->getPrevious(tail, nullptr);
	if(tail){
		tail->assignNpx(XOR(XOR(tail->getNpx(), temp), nullptr));
		delete temp;
		return val;
	} else {
		delete temp;
		return val;
	}
	
}

template<typename T>
void XORLinkedList<T>::printHeadAndTail(){ 
	cout << "Head: " << head->getData() << " Tail: " << tail->getData() << endl; 
}

template<typename T>
void XORLinkedList<T>::printAll(){
	//cout << "1" << endl;
	xNode<T>* current = head;
	//cout << "2" << endl;
	xNode<T>* prev = nullptr;
	//cout << "3" << endl;
	while(current != nullptr){
		//cout << "loop" << endl;
		cout << current->getData() << ' ';
		xNode<T>* temp = current;
		//cout << "4" << endl;
		current = XOR(prev, current->getNpx());
		//cout << "5" << endl;
		prev = temp;
		//cout << "6" << endl;
	}
}

template<typename T>
void XORLinkedList<T>::reversePrintAll(){
	xNode<T>* current = tail;
	xNode<T>* prev = nullptr;
	while(current != nullptr){
		cout << current->getData() << ' ';
		xNode<T>* temp = current;
		current = XOR(current->getNpx(), prev);
		prev = temp;
	}
}

template<typename T>
xNode<T>* XORLinkedList<T>::XOR(xNode<T>* a, xNode<T>* b){ 
	return (xNode<T>*)((uintptr_t)(a) ^ (uintptr_t)(b)); 
}

template<typename T>
void XORLinkedList<T>::swap(XORLinkedList<T>& rhs){
	xNode<T> *temp = rhs.head;
	rhs.head = head;
	head = temp;
	temp = rhs.tail;
	rhs.tail = tail;
	tail = temp;
}

template <typename T>
void XORLinkedList<T>::insert(T data, int idx){
	if(head == tail || idx == (length-1)){
		this->add(data);
	} else if(idx == 0) {
		xNode<T> *before = nullptr;
		cout << "here" << endl;
		
	} else {
		xNode<T> *before = this->getNodeAtIndex(idx-1), *after = this->getNodeAtIndex(idx); //need function to get node here, not data
		xNode<T> *temp = new xNode<T>(data);
		temp->assignNpx(XOR(before, after)); //?
		before->assignNpx(XOR(XOR(before->getNpx(), after),temp));
		after->assignNpx(XOR(temp, XOR(before, after->getNpx())));
	}
	length++;
}

//private functions
template <typename T>
xNode<T>* XORLinkedList<T>::getNodeAtIndex(int idx){
	if(idx >= length || idx <= 0){
		return nullptr;
	} else {	
		xNode<T>* current = head;
		xNode<T>* prev = nullptr;
		for(int i = 0; i < idx; ++i){
			xNode<T>* temp = current;
			current = XOR(prev, current->getNpx());
			prev = temp;
		}
		return current;
	}
}

template <typename T>
xNode<T>* XORLinkedList<T>::reverseTraverse(int j){
	xNode<T> *current = tail;
	xNode<T> *prev = nullptr;
	for(int i = 0; i < j; ++i){
		xNode<T> *temp = current;
		current = XOR(prev, current->getNpx());
		prev = temp;
	}
	return current;
}

template <typename T>
xNode<T>* XORLinkedList<T>::getPrevious(xNode<T> *current, xNode<T> *next){
	return XOR(current->getNpx(), next);
}

template <typename T>
xNode<T>* XORLinkedList<T>::getNext(xNode<T> *current, xNode<T> *previous){
	return XOR(current->getNpx(), previous);
}

//OPERATORS
template<typename T>
XORLinkedList<T>& XORLinkedList<T>::operator=(XORLinkedList<T> rhs){
	this->swap(rhs);
	return *this;
}

template<typename T>
T XORLinkedList<T>::operator[](int idx){
	return this->getAtIndex(idx);
}

#endif