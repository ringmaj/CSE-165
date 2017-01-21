
#include <iostream>
#include <string>
#include "Animal.h"

using namespace std;


class Dog: public Animal {

public:
	
	void feed(){
		cout<<"A bone, please!"<<endl;
	}
	~Dog(){

	}
	Dog(string str, int x)
	{
		cout << "Creating Dog" << endl;
		setName(str);
		setAge(x);

		cout<<getName()<<endl;


	};












};