#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <vector>
using namespace std;



class Vec {



public:
	static Vec null;
	float x;
	float y;	
	Vec();
	Vec(float a, float b);
	void add(Vec v);
	void print();

	
	


}; 


Vec::Vec(){
	x = 0;
	y = 0;
}

Vec::Vec(float a, float b){

	x = a;
	y = b;
}

void Vec::add(Vec v)
{
	x = x + v.x;
	y = y + v.y;
}

void Vec::print()
{
	cout<<"("<<x<<", "<<y<<")"<<endl;
}



#endif