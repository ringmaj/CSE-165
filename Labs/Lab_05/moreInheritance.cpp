
#include <iostream>
#include <string>
#include "Animal.h"
#include "Dog.h"
#include "display.h"
#include <vector>

using namespace std;



int main()
{

	int num;
	cin >> num;


	vector<Animal*> vect;




	while(num != 0)
	{

		char c; 
		cin >> c;

		if(c == 'A')
		{
			string name;
			int age;

			cin >> name;
			cin >> age;

			Animal * an = new Animal();
			an->setName(name);
			an->setAge(age);
			vect.push_back(an);

		}
		else {

			string name;
			int age;

			cin >> name;
			cin >> age;
			Dog *myDog = new Dog(name, age);
			vect.push_back(myDog);
			




		} 
		num--;

		
	}


//display(const vector<Animal*> &list);
	display(vect);
















}