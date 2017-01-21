#include <iostream>
#include <math.h>
using namespace std;

class Clock {
 

 public:
 	 int hours, minutes, seconds;
  Clock(int h, int m, int s) {
    hours = h;
    minutes = m;
    seconds = s;
  }

  void add(const Time& t) {
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


    void get (){
        time_t t = time(NULL);
        tm* tm = localtime ( &t ); // returns pointer to a static object
        hours = tm->tm_hour;
        minutes = tm->tm_min;
        seconds = tm->tm_sec;
    }

  void draw() {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (float theta = 0; theta <= 2 * M_PI; theta += 0.1) {
      glVertex2f(cos(theta), sin(theta));
    }
    glEnd();
  }
};
