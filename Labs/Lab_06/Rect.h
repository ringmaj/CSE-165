#ifndef RECT_H
#define RECT_H

#include <iostream>
#include "Vec.h"

using namespace std;

class Rect: public Vec{

public:
	int x1;
	int x2;
	int y1;
	int y2;

	Rect();
	Rect(float a, float b, float c, float d);
	int contains(Vec v);











};

Rect::Rect(){
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;



}

Rect::Rect(float a, float b, float c, float d){
	x1 = a;
	y1 = b;
	x2 = c;
	y2 = d;

}
int Rect::contains(Vec v){



}


#endif