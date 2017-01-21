#include <iostream>
#include <math.h>
using namespace std;

class Clock : public GrRect{
 

 public:
 	 int hours, minutes, seconds;
   float xOffset = 0.0;
   float yOffset = 0.0;
 	// float scale = 1.0;
  Clock(int h, int m, int s) {
    hours = h;
    minutes = m;
    seconds = s;

    setX(-0.5);
    setY(0.5);

    setW(1.0);
   setH(1.0);

  }

  void add(const Clock& t) {
    seconds += t.seconds;
    if (seconds >= 60) {
      seconds -= 60;
      minutes += 1;
    }
    minutes += t.minutes;
    if (minutes >= 60) {
      minutes -= 60;
      hours += 1;
    }
    hours += t.hours;
  }

  void getHourCoords(float& x, float& y) {
    float h = (float)hours;
    float m = (float)minutes;
    float s = (float)seconds;
    getAngles(h, m, s);
    x = cos(h);
    y = sin(h);
  }
  void getMinuteCoords(float& x, float& y) {
    float h = (float)hours;
    float m = (float)minutes;
    float s = (float)seconds;
    getAngles(h, m, s);
    x = cos(m);
    y = sin(m);
  }
  void getSecondsCoords(float& x, float& y) {
    float h = (float)hours;
    float m = (float)minutes;
    float s = (float)seconds;
    getAngles(h, m, s);
    x = cos(s);
    y = sin(s);
  }

  void getAngles(float& a, float& b, float& c) {
    // seconds
    if (seconds >= 0 && seconds <= 15) {
      c = (15 - seconds) * (M_PI / 30);
    } else if (seconds >= 45 && seconds < 60) {
      c = (60 - seconds) * (M_PI / 30) + M_PI / 2;
    } else if (seconds > 15 && seconds < 45) {
      c = (seconds - 15) * (-M_PI / 30);
    }
    // minutes
    if (minutes >= 0 && minutes <= 15) {
      b = (15 - minutes) * M_PI / 30;
    } else if (minutes >= 45 && minutes < 60) {
      b = (60 - minutes) * M_PI / 30 + M_PI / 2;
    } else if (minutes > 15 && minutes < 45) {
      b = (minutes - 15) * -M_PI / 30;
    }

    float temp = hours + (minutes + 0.0) / 60;
    // hours
    if (temp > 12) temp /= 12;
    if (temp >= 0 && temp <= 3) {
      a = (3 - temp) * (M_PI / 6);
    } else if (temp >= 9 && temp < 12) {
      a = (12 - temp) * M_PI / 6 + M_PI / 2;
    } else if (temp > 3 && temp < 9) {
      a = (temp - 3) * (-M_PI / 6);
    }
  }

  int getHours() { return hours; }
  int getMinutes() { return minutes; }
  int getSeconds() { return seconds; }

     void setHour(int newY){hours = newY;}
     void setMinute(int newW){minutes = newW;}
     void setSecond(int newH){seconds = newH;}

 


    void get (){
        time_t t = time(NULL);
        tm* tm = localtime ( &t ); // returns pointer to a static object
        hours = tm->tm_hour;
        minutes = tm->tm_min;
        seconds = tm->tm_sec;
    }

  void draw() 
  {
	

	glColor3f(1.0,0.0,0.0);
	
	 for (float theta = 0; theta <= 2 * M_PI; theta += M_PI/6) 
	 {
	 	glBegin(GL_LINES);

 
 glVertex2f ((0.9*w)*0.5*cos(theta)+ x + (0.5*w ) , (0.9*h)*0.5*sin(theta) + y - (0.5*h));
       glVertex2f ((0.9*w)*0.5*0.78*cos(theta) + x + (0.5*w ) , (0.9*h)*0.5*0.78*sin(theta) + y - (0.5*h));

    

		glEnd();
	}





	 for (float theta = 0; theta <= 2 * M_PI; theta += M_PI/30) 
	 {
	 	glBegin(GL_LINES);

        if(theta >= -M_PI/2 && theta <= M_PI/2)
        {

         glVertex2f ((0.9*w)*0.5*cos(theta)+ x + (0.5*w ) , (0.9*h)*0.5*sin(theta)+ y - (0.5*h));
        glVertex2f ((0.9*w)*0.5*0.95*cos(theta) + x + (0.5*w ), (0.9*h)*0.5*0.95*sin(theta) + y - (0.5*h));
        }
        else
        {

         glVertex2f ((0.9*w)*0.5*cos(theta)+ x + (0.5*w ) , (0.9*h)*0.5*sin(theta)+ y - (0.5*h));
        glVertex2f ((0.9*w)*0.5*0.95*cos(theta) + x + (0.5*w ) , (0.9*h)*0.5*0.95*sin(theta) + y - (0.5*h));
        }
	 	
		glEnd();
	}


	float hourAngle;
	float minAngle;
	float secAngle;

	getAngles(hourAngle,minAngle,secAngle);


    if(getTime)
		get();
		if(hours > 12)
		hours -= 12;

  xOffset = (x+w) - (xScale*cos(0)  + x + (0.5*w ));
    yOffset = (y-h) - ((0.9*h)*0.5*cos(-M_PI/2)  + y + (0.5*h ));



		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex2f (x + 0.5*w, y - 0.5*h);
   		glVertex2f ((0.9*w)*0.5*0.4*cos(hourAngle) + x + (0.5*w ), (0.9*h)*0.5*0.4*sin(hourAngle) + y - (0.5*h));
		glEnd();

		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);
	 glVertex2f (x + 0.5*w, y - 0.5*h);
   		glVertex2f ((0.9*w)*0.5*0.7*cos(minAngle) + x + (0.5*w ), (0.9*h)*0.5*0.7*sin(minAngle) + y - (0.5*h));
		glEnd();


		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
		  glVertex2f (x + 0.5*w, y - 0.5*h);
   		glVertex2f ((0.9*w)*0.5*0.7*cos(secAngle) + x + (0.5*w ), (0.9*h)*0.5*0.7*sin(secAngle) + y - (0.5*h));
		glEnd();

		//cout << getHours() << " : " << getMinutes() << " : " << getSeconds() << endl;





	    glBegin(GL_POLYGON);
	    glColor3f(1.0, 1.0, 1.0);
	    for (float theta = 0; theta <=  2*M_PI; theta += 0.1) 
	    {

        
        if(xScale != 0)
        {
	      	glVertex2f((0.9*w)*0.5*cos(theta)  + x + (0.5*w ) , (0.9*h)*0.5*sin(theta)  + y - (0.5*h) );
          glVertex2f((0.9*w)*0.5*cos(theta)  + x + (0.5*w ) , (0.9*h)*0.5*sin(theta)  + y - (0.5*h) );
        }

	    }
	    glEnd();


	    
			glColor3f(1.0, 0.0,0.0);
			glBegin(GL_POLYGON);
			glVertex2f(x, y);
			glVertex2f(x + w, y);
			glVertex2f(x + w,y - h);
			glVertex2f(x, y - h);
			glEnd();


      // cout<<"xDistance: "<<xDistance<<endl;
      // cout<<"yDistance: "<<yDistance<<endl;

  }
};
