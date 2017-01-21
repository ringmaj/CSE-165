
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

# include "glut_window.h"
//# include "GrRect.h"
# include "GrPlot.h"
#include "Elements.h"
//#include "Rect.h"
# include <vector>

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
{ 
    private :
        enum MenuEv { evOption0, evOption1 };
        float _markx, _marky;
        int _w, _h;

        std::vector<GrRect*> stash;


    public :
        AppWindow ( const char* label, int x, int y, int w, int h );
        void windowToScene ( float& x, float &y );
        float width;
        bool mouseDown = false;
        bool dragging = false;
        bool resized = false;
        int index = 0;
        float offsetX = 0;
        float offsetY = 0;

    private : // functions derived from the base class
        virtual void handle ( const Event& e );
        virtual void draw ();
        virtual void resize ( int w, int h );
};

#endif // APP_WINDOW_H