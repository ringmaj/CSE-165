#ifndef GRPLOT_H
#define GRPLOT_H

#include "GrRect.h"
#include "Clock.h"
#include <vector>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

using namespace std;

class GrPlot : public GrRect 
{
	 public:
	 	float a,b,c,d;
		virtual void generate(float xini, float xend, float inc) {}
		virtual void regenerate(){}

		virtual float getX(){}
		virtual float getY(){}
		virtual void setX(float a){}
		virtual void setY(float a){}

		virtual void setA(float a){}
		virtual void setB(float b){}
		virtual void setC(float c){}
		virtual void setD(float D){}

		virtual void scale(){}


		virtual float getA(){}
		virtual float getB(){}
		virtual float getC(){}
		virtual float getD(){}
		void add(float x1, float y1);
};


class QuadraticCurve : public GrPlot 
{
	public:
		float a, b, c;
		bool generated = false;


		virtual float getX(){return x;}
		virtual float getY(){return y;}
		virtual void setX(float x){this->x = x;}
		virtual void setY(float y){this->y = y;}


		void setA(float a){this->a = a;}
		void setB(float b){this->b = b;}
		void setC(float c){this->c = c;}

		virtual float getA(){return a;}
		virtual float getB(){return b;}
		virtual float getC(){return c;}
		

		void add(float x1, float y1) 
		{
		Vec *b = new Vec(x1, y1);
		points.push_back(b);
		}

		void generate(float xini, float xend, float inc) 
		{

		
		float yPt = 0;
		float xPt = xini;
		while (xPt <= xend) 
			{
				yPt = (a * xPt * xPt) + (b * xPt) + c;
				add(xPt, yPt);
				xPt += inc;
			}
		}

		void scale()
		{

				int end = points.size() - 1;
	
			

			float minY = 0;
			float maxY = 0;
			float yLength = 0;

			for (int i = 0; i < points.size(); i++) 
			{
				if(points[i]->y > maxY)
					maxY = points[i]->y;

				if(points[i]->y < minY)
					minY = points[i]->y;
			}

			// yLength = maxY - minY;
			// if(yLength < 0){ yLength *= -1;}

			yLength = (maxY - (y - h)) - h;
			float offset = yLength/h;

		//	cout<<"minY:\t"<<minY<<"\tmaxY:\t"<<maxY<<"\tlength: "<<yLength<<"\theight: "<<h<<"\t offset: "<<offset<<endl;

			float xSize = points[end]->x - points[0]->x;
			float xOffset = (w/xSize);

			//cout<<"xSize: "<<xSize<<endl;

			//cout<<"xoffset: "<<xOffset<<endl;

			float offsetYInit = points[0]->y - y;

			for (int i = 0; i < points.size(); i++) 
			{
				//points[i]->y = points[i]->y - offsetYInit;
			}



			float ySize = (maxY - (y - h)) - h;
			float yOffset = (ySize/w);

			//cout<<"yoffset = ("<<h<<" / "<<ySize<<") = "<<yOffset<<endl;

			for(int i = 0; i < points.size(); i++)
			{
				// if(yOffset != 0)
				points[i]->y = points[i]->y - (points[i]->y *yOffset);
				// if(xOffset != 0)
				points[i]->x = points[i]->x *xOffset;
				
			}




			float restoreX = x - points[0]->x;

			if(restoreX < 0)
			{
				restoreX = points[end]->x - (x + w);
			}

			float restoreY = maxY - y;

			if(restoreY < 0)
			{
				restoreY = points[end]->y - (y - w);
			}

			for (int i = 0; i < points.size(); i++) 
			{
				points[i]->x = points[i]->x + restoreX;
				points[i]->y = points[i]->y - restoreY;
			}
		}


		QuadraticCurve(float a, float b, float c, float rh, float gh, float bh) 
		{
			this->a = a;
			this->b = b;
			this->c = c;

			this->r = rh;
			this->g = gh;
			this->bl = bh;

			this->w = 0.5;
			this->h = 0.5;

			generate(-0.5, 0.5, 0.1);

			//cout<<"point[0]->x = "<<points[0]->x<<endl;

				for (int i = 0; i < points.size(); i++) 
			{
				points[i]->y = points[i]->y - 0.5 * h;
				points[i]->x = points[i]->x + 0.5 * w;
			}
			scale();

			
			




		


		}

		virtual void regenerate() 
		{

			float xini = x;
			float xend = x + w;
			float inc = 0.1;
		points.clear();
		generate(-0.5,0.5, 0.1);

		

				for (int i = 0; i < points.size(); i++) 
			{
				points[i]->y = points[i]->y - 0.5 * h;
				points[i]->x = points[i]->x + 0.5 * w;
			}
			scale();

		//draw();

			}

		virtual void draw() 
		{

			Clock* t = new Clock(0,0,0);
			t->get();
			t->draw();




			

			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex2f(x, y);
			glVertex2f(x + w, y);
			glVertex2f(x + w, y - 0.1*h);
			glVertex2f(x, y - 0.1*h);
			glEnd();



			// if(focused)
			// {
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_LINES);

				glVertex2f (x, y);
				glVertex2f (x +w , y);

				glVertex2f (x, y - h);
				glVertex2f (x + w, y - h);

				glVertex2f (x, y);
				glVertex2f (x, y - h );

				glVertex2f (x + w, y);
				glVertex2f (x + w, y - h);
			//}



			



			glColor3f(r, g, bl);
			glBegin(GL_POLYGON);
			glVertex2f(x, y);
			glVertex2f(x + w, y);
			glVertex2f(x + w, y - h);
			glVertex2f(x, y - h);
			glEnd();
		}
};

class CubicCurve : public GrPlot 
{
	public:
		float a, b, c,d;
		bool generated = false;


		virtual float getX(){return x;}
		virtual float getY(){return y;}
		virtual void setX(float x){this->x = x;}
		virtual void setY(float y){this->y = y;}


		void setA(float a){this->a = a;}
		void setB(float b){this->b = b;}
		void setC(float c){this->c = c;}
		void setD(float d){this->d = d;}

		virtual float getA(){return a;}
		virtual float getB(){return b;}
		virtual float getC(){return c;}
		virtual float getD(){return d;}

		void add(float x1, float y1) 
		{
		Vec *b = new Vec(x1, y1);
		points.push_back(b);
		}

		void generate(float xini, float xend, float inc) 
		{
		float yPt = 0;
		float xPt = xini;
		while (xPt <= xend) 
			{
				yPt = (a * xPt * xPt * xPt) + (b * xPt - xPt) + (c * xPt) + d;
				add(xPt, yPt);
				xPt += inc;
			}
		}

		void scale()
		{

				int end = points.size() - 1;
	
			

			float minY = 0;
			float maxY = 0;

			for (int i = 0; i < points.size(); i++) 
			{
				if(points[i]->y > maxY)
					maxY = points[i]->y;

				if(points[i]->y < minY)
					minY = points[i]->y;
			}

			//cout<<"minY:\t"<<minY<<"\tmaxY:\t"<<maxY<<endl;

			float xSize = points[end]->x - points[0]->x;
			float xOffset = (w/xSize);

			float offsetYInit = points[0]->y - y;

			for (int i = 0; i < points.size(); i++) 
			{
				if(offsetYInit > 0)
				points[i]->y = points[i]->y - offsetYInit;
				else
					points[i]->y = points[i]->y + offsetYInit;

			}



			float ySize = maxY - minY;
			float yOffset = (h/ySize);

			//cout<<"yoffset = ("<<w<<" / "<<ySize<<") = "<<yOffset<<endl;

			for(int i = 0; i < points.size(); i++)
			{
				points[i]->y = points[i]->y *yOffset;
				points[i]->x = points[i]->x *xOffset;
				
			}




			float restoreX = x - points[0]->x;

			if(restoreX < 0)
			{
				restoreX = points[end]->x - (x + w);
			}

			float restoreY = maxY - y;

			if(restoreY < 0)
			{
				restoreY = points[end]->y - (y - w);
			}

			for (int i = 0; i < points.size(); i++) 
			{
				//points[i]->y = points[i]->y - 0.5 * h;
				points[i]->x = points[i]->x + restoreX;
				//points[i]->y = points[i]->y - restoreY;
			}
		}

		CubicCurve(float a, float b, float c, float d, float rh, float gh, float bh) 
		{
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;

			this->r = rh;
			this->g = gh;
			this->bl = bh;

			this->w = 0.5;
			this->h = 0.5;

			generate(-0.5, 0.5, 0.1);

			//cout<<"point[0]->x = "<<points[0]->x<<endl;

				for (int i = 0; i < points.size(); i++) 
			{
				points[i]->y = points[i]->y - 0.5 * h;
				points[i]->x = points[i]->x + 0.5 * w;
			}
			scale();

		


		}

		virtual void regenerate() 
		{

			float xini = x;
			float xend = x + w;
			float inc = 0.1;
		points.clear();
		generate(-0.5,0.5, 0.1);

		

				for (int i = 0; i < points.size(); i++) 
			{
				points[i]->y = points[i]->y - 0.5 * h;
				points[i]->x = points[i]->x + 0.5 * w;
			}
			//scale();

		//draw();

			}

		virtual void draw() 
		{

			if(focused)
			{
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_LINES);

				glVertex2f (x, y);
				glVertex2f (x +w , y);

				glVertex2f (x, y - h);
				glVertex2f (x + w, y - h);

				glVertex2f (x, y);
				glVertex2f (x, y - h );

				glVertex2f (x + w, y);
				glVertex2f (x + w, y - h);
			}


			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			glVertex2f(x, y - (0.1 * h));
			glVertex2f(x + w, y - (0.1 * h));
			glEnd();


			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			for (int i = 0; i < points.size() - 1; i++) 
			{
				glVertex2f(points[i]->x + x, points[i]->y + y);
				glVertex2f(points[i + 1]->x + x, points[i + 1]->y + y);
			}
			glEnd();



			glBegin(GL_POINTS);
			glColor3f(1.0, 1.0, 1.0);
			for (vector<Vec *>::iterator i = points.begin(); i != points.end(); i++) 
			{
				glVertex2f((*i)->x + x, (*i)->y + y);
			}
			glEnd();


			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			glVertex2f(x, y - (0.5 * h));
			glVertex2f(x + w, y - (0.5 * h));
			glEnd();

			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			glVertex2f(x + (0.5 * w), y);
			glVertex2f(x + (0.5 * w), y - h);
			glEnd();

			 glColor3f(0.0, 0.0, 0.0); 
  glRasterPos2f(x + 0.1*w, y - 0.1*h);



  glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>("Cubic Curve"));

  glColor3f(1.0, 1.0, 1.0); 
  glRasterPos2f(x  , (y - h) - 0.2);

char aPtr[8];
sprintf(aPtr,"%.2f", a);

char bPtr[8];
sprintf(bPtr,"%.2f", b);

char cPtr[8];
sprintf(cPtr,"%.2f", c);

char dPtr[8];
sprintf(dPtr,"%.2f", d);


string aValue(aPtr);
string bValue(bPtr);
string cValue(cPtr);
string dValue(dPtr);


string output = aValue+ "x^3 + "+ bValue + "x^2 + "+ cValue + "x + "+ dValue;



  glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char *)output.c_str());






			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex2f(x, y);
			glVertex2f(x + w, y);
			glVertex2f(x + w, y - 0.1*h);
			glVertex2f(x, y - 0.1*h);
			glEnd();

			glColor3f(r, g, bl);
			glBegin(GL_POLYGON);
			glVertex2f(x, y);
			glVertex2f(x + w, y);
			glVertex2f(x + w, y - h);
			glVertex2f(x, y - h);
			glEnd();
		}
};



#endif