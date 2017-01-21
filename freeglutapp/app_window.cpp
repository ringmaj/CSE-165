
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <vector>
#include "app_window.h"

using namespace std;

AppWindow::AppWindow(const char* label, int x, int y, int w, int h)
  : GlutWindow(label, x, y, w, h) {
  _markx = 0;
  _marky = 0;
  w = 0.5;
  addMenuEntry("Option 0", evOption0);
  addMenuEntry("Option 1", evOption1);

  Game* game = new Game();

  stash.push_back(game);
}

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed

void AppWindow::windowToScene(float& x, float& y) {
  x = (2.0f * (x / float(_w))) - 1.0f;
  y = 1.0f - (2.0f * (y / float(_h)));
}

// Called every time there is a window event

void AppWindow::handle(const Event& e) {
  bool rd = true;
  float x1;
  float y1;

  if (e.type == Keyboard || e.type == SpecialKey) switch (e.key) {
    case GLUT_KEY_LEFT:
      if (stash[0]->elements[0]->x > -1.0) {
        stash[0]->elements[0]->restoreColor();
        stash[0]->elements[0]->x -= stash[0]->elements[0]->barSpeed;
      }

      else
        stash[0]->elements[0]->setColor(1.0, 0.6, 0.2);
      break;

    case GLUT_KEY_RIGHT:
      if ((stash[0]->elements[0]->x + stash[0]->elements[0]->w) < 1.0) {
        stash[0]->elements[0]->restoreColor();
        stash[0]->elements[0]->x += stash[0]->elements[0]->barSpeed;
      }

      else
        stash[0]->elements[0]->setColor(1.0, 0.6, 0.2);
      break;

    case ' ':

      if (stash[0]->elements[1]->x == 0 && stash[0]->elements[1]->y == 0) {
        stash[0]->elements[1]->yDirectionSpeed = -0.0250;
      }
      if (stash[0]->elements[1]->lives == 0) {
        stash[0]->elements[1]->score = 0;
        stash[0]->elements[1]->lives = 3;
      }
      break;

    case 'r':
      stash[0]->createBlocks();
      break;

    case 'z':
      //int size = stash[0]->elements.size() - 1;
      for (int i = 2; i > 1; i--)
      {

        stash[0]->elements.erase(stash[0]->elements.begin() + i);
      }
      break;

    case 27:  // Esc was pressed
      exit(1);
    }

  if (e.type == MouseDown || e.type == Motion) {
    _markx = (float)e.mx;
    _marky = (float)e.my;
    windowToScene(_markx, _marky);

    int selected = 0;
    float r;
    float b;
    float g;

    stash[0]->elements[0]->x = _markx - 0.5 * stash[0]->elements[0]->w;
  }

  if (e.type == Menu) {
    std::cout << "Menu Event: " << e.menuev << std::endl;
  }
  rd = false;  // no need to redraw

  const float incx = 0.02f;
  const float incy = 0.02f;
  if (e.type == SpecialKey) switch (e.key) {
      // case GLUT_KEY_LEFT:
      // _markx -= incx;
      // break;
      // case GLUT_KEY_RIGHT:
      // _markx += incx;
      // break;
      // case GLUT_KEY_UP:
      // _marky += incy;
      // break;
      // case GLUT_KEY_DOWN:
      // _marky -= incy;
      // break;
      // default:
      rd = false;  // no redraw
    }

  if (rd) redraw();  // ask the window to be rendered when possible
}

void AppWindow::resize(int w, int h) {
  // Define that OpenGL should use the whole window for rendering
  glViewport(0, 0, w, h);
  _w = w;
  _h = h;
}

// here we will redraw the scene according to the current state of the
// application.

void AppWindow::draw() {
  // Clear the rendering window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Clear the trasnformation stack
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();


  stash[0]->draw();


  redraw();
  glFlush();          // flush the pipeline (usually not necessary)
  glutSwapBuffers();  // we were drawing to the back buffer, now bring it to the
  // front
}
