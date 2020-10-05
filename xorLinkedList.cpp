#include <iostream>
#include <string>
#include <vector>
#include "xorLinkedList.hpp"
using namespace std;




int main(){
	string tst = "TEST DRIVER\n";
	cout << tst;
	
	XORLinkedList<int> a(0);
	a.add(1);
	a.add(2);
	a.add(3);
	a.add(4);
	a.add(5);

	XORLinkedList<int> a2(11);
	a2.add(22);
	a2.add(33);
	a2.add(44);
	a2.add(55);
	a2.add(66);
	a2.add(77);
	a2.add(88);
	a2.add(99);

	a = a2;
	//cout << "a: ";
	//a.printAll();
	//cout << "\na2: ";
	//a2.printAll();

	//cout << "\nIndexing test: " << a[5] << endl;

	cout << "INSERT TEST" << endl;
	a2.insert(222, 4);
	a2.insert(111,2);
	a2.insert(333,0);
	a2.printAll();

	/*
	cout << "PRINT: \n";
	a.printAll();
	cout << "\nREVERSE PRINT: \n";
	a.reversePrintAll();
	cout << '\n';
	cout << "Length: " << a.getLength() << endl;
	
	XORLinkedList<string> b;
	b.add("hello");
	b.add("world");
	b.printAll();
	
	XORLinkedList<char> c;
	c.add('a');
	c.add('b');
	c.add('c');
	c.printAll();
	
	string s[5] = {"hello", "world", "i", "am", "XOR"};
	XORLinkedList<string> d(s, 5);
	d.printAll();
	
	{
		vector<int> vec;
		for(int i = 0; i < 21; ++i){
			if(i % 2 == 0) vec.push_back(i);
		}
		XORLinkedList<int> e(vec);
		e.printAll();
	}
	*/

	XORLinkedList<string> b;
	b.add("hello");
	b.add("world");
	b.add("fun");
	b.add("times");

	cout << "\nPOP TEST" << endl;
	cout << b.pop() << ' ';
	cout << b.pop() << ' ';
	cout << b.pop() << ' ';
	cout << b.pop() << ' ';
	cout << endl;
	

	//a2.printAll();

}

