#include <iostream>
#include "Stack.h"

using namespace std;


int main()
{
	Stack stack;
	Stack tmp;

	stack.initialize();


	int num;
	cin >> num;
	int size = num;

	while (num != 0)
	{
		double x;
		cin >> x;

		double* p;

		p = new double;
		*p = x;

	

		  void *ptr = p;

		stack.push(ptr);
		tmp.push(ptr);

		

		num--;
	}


	for(int i = 0; i < size; i++)
	{


		void *voidPtr2 = tmp.pop();



		double b = *((double*)voidPtr2);

		cout<<b<<endl;
		



	}

	Stack:: Link *temp = stack.head;

	for(int i = 0; i < size; i++)
	{





	}



	return 0;




}