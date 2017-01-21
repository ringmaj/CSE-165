#ifndef GRRECT_H
#define GRRECT_H

#include <vector>

using namespace std;

class Vec
{
public:

	float x;
	float y;
	Vec()
	{
		x = 0;
		y = 0;
	}
	Vec(float a, float b)
	{
		x = a;
		y = b;

	}
	void add(Vec v)
	{
		x = x + v.x;
		y = y + v.y;
	}
	void print()
	{
		cout << "(" << x << ", " << y << ")" << endl;
	}

	void setX(int newX) {x =  newX;}
	void setY(int newY) {y = newY;}

	int getX() {return x;}
	int getY() {return y;}

};









class GrRect : public Vec {
public:
	float x;
	float y;
	float w = 0.5;
	float h = 0.5;

	float bl = 0.0;

	float rh = 0.0;
	float gh = 0.0;
	float bh = 0.0;

	float r = 1.0;
	float g = 1.0;
	float b = 1.0;

	float xScale = 0.5;
	float yScale = 0.5;

	float xOffset = 0.0;
	float yOffset = 0.0;

	float xDistance;
	float yDistance;

	bool getTime = true;
	bool Analog = true;

	float yDirectionSpeed = -0.0250;
	float xDirectionSpeed = 0.0;

	string powerupName = " ";

	string objectName;


	vector<GrRect*> elements;

	int score;
	int lives;
	int highScore;
	int randNum = rand() % 20 + 1;

	bool gameOver = false;

	bool started;

	bool isPowerup = false;

	float barSpeed = 0.10;

	virtual void setStarted(bool on)
	{
		started = on;
	}


	virtual void setColor(float r, float g, float b) {}
	virtual void restoreColor() {}

	void setTimeBool(bool on)
	{
		getTime = on;
	}



	bool focused;

	void setX(float newX) {x =  newX;}
	void setY(float newY) {y = newY;}
	void setW(float newW) {w = newW;}
	void setH(float newH) {h = newH;}


	float getX() {return x;}
	float getY() {return y;}
	float getW() {return w;}
	float getH() {return h;}

	virtual void setHours(int newY) {y = newY;}
	virtual void setMinutes(int newW) {w = newW;}
	virtual void setSeconds(int newH) {h = newH;}

	virtual int getHours() {}
	virtual int getMinutes() {}
	virtual int getSeconds() {}

	virtual void createBlocks() {}




	vector<Vec*>points;

	GrRect()
	{
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
	GrRect(float a, float b, float c, float d, float red, float green, float blue)
	{
		x = a;
		y = b;
		w = c;
		h = d;

		r = red;
		g = green;
		b = blue;
	}
	int contains(float xPoint, float yPoint)
	{
		if (xPoint >= x && xPoint <= x + w)
			if (yPoint <= y && yPoint >= y - h)
				return 1;
		return 0;
	}

	bool isFocused()
	{
		return focused;
	}

	void focus(bool on)
	{
		focused = on;
	}




	virtual void handle(float mx, float my)
	{
		points.push_back(new Vec(mx - x, my - y));

	}

	virtual void draw()
	{








		glColor3f(r, g, b);
		glBegin(GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y - h);
		glVertex2f(x, y - h);
		glEnd();




	}


};
#endif