#ifndef CIRCLES_H
#define CIRCLES_H
#define M_PI       3.14159265358979323846
#include <iostream>

	const double pi = 3.14159265358;

class Circle{



private:
	double x,y,r;

public:
	double area;
	


	Circle(){
		x = 0;
		y = 0;
		r =1;
	
		areaFunct(x,y);


	};

	Circle(int num1, int num2, int num3){
		x = num1;
		y = num2;
		r = num3;
	 areaFunct(x,y);


	};


	void setX(int num)
	{
		x = num;




	}

	void setY(int num)
	{

		y = num;
		
	}

	void setR(int num)
	{

		r = num;
		areaFunct(x,y);
		
	}



	double getX()
	{
		return x;


	}

	double getY()
	{

		return y;
		
	}

	double getR()
	{

		return r;
		
	}









	void areaFunct(double x, double y){


area = M_PI*r*r;


	}

	







};

#endif