#ifndef RECT_H
#define RECT_H

#include <iostream>
#include "Vec.h"

using namespace std;

class Rect : public Vec {
public:
  float x;
  float y;
  float width;
  float height;
  float r = 0.0;
  float g = 0.0;
  float b = 0.0;

  Rect();
  Rect(float a, float b, float c, float d, float red, float green, float blue);
  int contains(float xPoint, float yPoint);
  void color(float r, float g, float b);
};

Rect::Rect() {
  x = 0;
  y = 0;
  width = 0;
  height = 0;
}

Rect::Rect(float a, float b, float c, float d, float red, float green,
           float blue) {
  x = a;
  y = b;
  width = c;
  height = d;

  r = red;
  g = green;
  b = blue;
}

void Rect::color(float newR, float newG, float newB) {
  r = newR;
  g = newG;
  b = newB;
}
int Rect::contains(float xPoint, float yPoint) {
  int inbounds = 0;

  if (width < 0) {
    if (xPoint <= x && xPoint >= (x + width)) inbounds++;

  } else {
    if (xPoint >= x && xPoint <= (x + width)) inbounds++;
  }

  if (height < 0) {
    if (yPoint <= y && yPoint >= (y + height)) inbounds++;
  } else {
    if (yPoint <= y && yPoint >= (y  height)) inbounds++;
  }

  // cout<<"INBOUNDS: "<<inbounds<<endl;

  if (inbounds == 2)
    return 1;
  else
    return 0;
}



#endif