#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <vector>
#include <GL/glut.h>
#include <string>
#include <sstream>

using namespace std;




class Block : public GrRect {
public:

    Block(float a, float b, float c, float d, float red, float green, float blue)
    {
        x = a;
        y = b;
        w = c;
        h = d;
        objectName = "Block";

        r = red;
        g = green;
        b = blue;
        yDirectionSpeed = 0.0;
    }

    void draw()
    {

        if (randNum % 3 == 0 && isPowerup == true)
        {
            y += yDirectionSpeed;

            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex2f(x - 0.015, y + 0.015);
            glVertex2f(x + w + 0.015, y + 0.015);

            glVertex2f(x + w + 0.015, y - h - 0.015);
            glVertex2f(x - 0.015, y - h - 0.015);




            glEnd();

            glColor3f(r, g, b);
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
            glEnd();

            // glColor3f(0.0, 0.0, 0.0);
            // glBegin(GL_POLYGON);
            // glVertex2f(x + 0.015, y - 0.015);
            // glVertex2f(x + w + 0.015, y - 0.015);
            // glVertex2f(x + w + 0.015, y - h - 0.015);
            // glVertex2f(x + 0.015, y - h - 0.015);
            // glEnd();


        }
        else
        {

            y += yDirectionSpeed;

            glColor3f(r, g, b);
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
            glEnd();
        }
    }
};



class Ball : public GrRect {
public:
    bool deleteThis = false;
    Ball()
    {
        setStarted(false);
        objectName = "Ball";
        yDirectionSpeed = -0.0250;
        w = 0.03;
        h = 0.03;
        y = 0.0;
        x = -0.015;
        lives = 3;
        score = 0;
        highScore = 0;

    }

    Ball(float xSpeed, float xPosition)
    {
        objectName = "Ball";
        yDirectionSpeed = +0.0250;
        w = 0.03;
        h = 0.03;
        y = -0.7;
        x = xPosition;
        xDirectionSpeed = xSpeed;
        deleteThis = true;

    }

    static void timer(int id)
    {
        glutPostRedisplay();
    }

    void draw()
    {
        // glutTimerFunc(10,timer,1);

        y += yDirectionSpeed;
        x += xDirectionSpeed;

        if (y < -1.0 && deleteThis == false) {
            yDirectionSpeed = 0.0;
            xDirectionSpeed = 0.0;
            y = 0.0;
            x = 0.0;
            lives -= 1;
            system("cd sounds; python playwav.py loseLife.wav > /dev/null 2> /dev/null &");
        }
        else
        {

        }

        if (y > 1.0)
            yDirectionSpeed *= -1.0;

        if (x < -0.9 || x > 0.9)
            xDirectionSpeed *= -1.0;

        glColor3f(r, g, b);
        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y - h);
        glVertex2f(x, y - h);
        glEnd();
    }
};

class Paddle : public GrRect {
public:
    float rc = 1.0;
    float gc = 1.0;
    float bc = 1.0;

    Paddle()
    {
        w = 0.5;
        h = 0.03;
        y = -0.8;
        x = -0.25;
    }

    void setColor(float red, float blue, float green)
    {
        rc = red;
        bc = blue;
        gc = green;
    }

    void restoreColor()
    {
        // rc = 1.0;
        // gc = 1.0;
        // bc = 1.0;

        if (rc <= 1)
            rc += 0.01;

        if (bc <= 1)
            bc += 0.01;

        if (gc <= 1)
            gc += 0.01;
    }
    void draw()
    {
        // deflect();
        glColor3f(rc, gc, bc);
        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y - h);
        glVertex2f(x, y - h);
        glEnd();
    }
};

class Game : public GrRect {
public:
    int numBlocks = 10;
    int level = 1;
    float blockWidth = 0.30;

    Game()
    {
        Paddle* pad = new Paddle();
        elements.push_back(pad);
        Ball* ball = new Ball();
        elements.push_back(ball);
        createBlocks();
    }

    void deflect()
    {



        for (int i = 2; i < elements.size(); i++) {
            if (elements[0]->contains(elements[i]->x + 0.5 * elements[i]->w, elements[i]->y - elements[i]->h) == 1 && elements[i]->objectName != "Ball") //Checks if powerup hits paddle
            {

                //cout << elements[i]->randNum << endl;

                system("cd sounds; python playwav.py absorbPowerUp.wav > /dev/null 2> /dev/null &");

                elements[0]->setColor(0.0, 1.0, 0.0);

                if (elements[i]->randNum == 0) {
                    elements[0]->powerupName = "2X LENGTH";
                    elements[0]->w *= 2;
                    //cout << elements[0]->powerupName << endl;
                }
                if (elements[i]->randNum == 3) {
                    elements[0]->powerupName = "MULTI BALLS";
                    //cout << elements[0]->powerupName << endl;
                    Ball* ball1 = new Ball(-0.01, elements[0]->x + 0.5 * elements[0]->w);
                    Ball* ball2 = new Ball(0.01, elements[0]->x + 0.5 * elements[0]->w);
                    Ball* ball3 = new Ball(0.02, elements[0]->x + 0.5 * elements[0]->w);
                    elements.push_back(ball1);
                    elements.push_back(ball2);
                    elements.push_back(ball3);

                }

                if (elements[i]->randNum == 6) {                //remove later
                    elements[0]->powerupName = "2X BAR SPEED";
                    //cout << elements[0]->powerupName << endl;
                }

                if (elements[i]->randNum == 9) {                //done
                    elements[0]->powerupName = "DOUBLE POINTS";
                    elements[1]->score *= 2;
                    //cout << elements[0]->powerupName << endl;
                }

                if (elements[i]->randNum == 12) {               //done
                    elements[0]->powerupName = "EXTRA LIFE";
                    elements[1]->lives += 1;
                    //cout << elements[0]->powerupName << endl;
                }

                if (elements[i]->randNum == 15) {
                    elements[0]->powerupName = "EASY MODE";
                    elements[1]->yDirectionSpeed *= 0.5;
                    //cout << elements[0]->powerupName << endl;
                }

                if (elements[i]->randNum == 18) {
                    elements[0]->powerupName = "HARD MODE";
                    elements[1]->yDirectionSpeed *= 2.0;
                    //cout << elements[0]->powerupName << endl;
                }

                elements.erase(elements.begin() + i);
            }
        }


        for (int i = 1; i < elements.size(); i++)

        {


            if (elements[i]->objectName == "Ball") {
                if (elements[0]->contains(elements[i]->x + 0.5 * elements[i]->w, elements[i]->y - elements[i]->h) == 1 && elements[i]->objectName == "Ball") //Checks if ball hits paddle, changes direction
                {


                    elements[i]->yDirectionSpeed *= -1.0;
                    elements[0]->setColor(1.0, 0.0, 0.0);

                    // if (elements[i]->x + 0.5 * elements[i]->w > elements[0]->x + 0.5 * elements[0]->w)
                    //     elements[i]->xDirectionSpeed = (elements[i]->x + 0.5 * elements[i]->w) - (elements[0]->x + 0.5 * elements[0]->w);
                    // else
                    //     elements[i]->xDirectionSpeed = -1.0 * (elements[0]->x + 0.5 * elements[0]->w) - (elements[i]->x + 0.5 * elements[i]->w);

                    // if (elements[i]->xDirectionSpeed > 0.01 && elements[i]->xDirectionSpeed > 0.0)
                    //     elements[i]->xDirectionSpeed *= 0.0125;

                    // if (elements[i]->xDirectionSpeed < 0.01 && elements[i]->xDirectionSpeed < 0.0)
                    //     elements[i]->xDirectionSpeed *= 0.0125;

                    // cout<<"Ball: "<<(elements[i]->x + 0.5 * elements[i]->w)<<"\tPaddle: "<< (elements[i]->x + 0.5 * elements[i]->w)<<endl;
                    // float x = (elements[i]->x + 0.5 * elements[i]->w) - (elements[0]->x + 0.5 * elements[0]->w);
                    // cout<<x<<endl;


                    if (elements[i]->x + 0.5 * elements[i]->w > elements[0]->x + 0.5 * elements[0]->w) {
                        elements[i]->xDirectionSpeed = (elements[i]->x + 0.5 * elements[i]->w) - (elements[0]->x + 0.5 * elements[0]->w);

                    }
                    else
                        elements[i]->xDirectionSpeed = -1.0 * (elements[0]->x + 0.5 * elements[0]->w) - (elements[i]->x + 0.5 * elements[i]->w);

                    if (elements[i]->xDirectionSpeed > 0.01 && elements[i]->xDirectionSpeed > 0.0)
                        elements[i]->xDirectionSpeed *= 0.0300;

                    if (elements[i]->xDirectionSpeed < 0.01 && elements[i]->xDirectionSpeed < 0.0)
                        elements[i]->xDirectionSpeed *= 0.0300;

                    // cout<<"xSpeed: "<<elements[i]->xDirectionSpeed<<endl;
                }

            }


        }

        for (int i = 1; i < elements.size(); i++)
        {
            if (elements[i]->y < -1.0)
            {
                elements.erase(elements.begin() + i);
            }
        }

        for (int j = 1; j < elements.size(); j++)
        {
            for (int i = 2; i < elements.size(); i++) //Checks if ball hits block and changes direction if top or bottom of the ball  the touches block.

            {

                if (elements[i]->objectName != "Ball" && elements[j]->objectName == "Ball") {


                    bool topOfBall = elements[i]->contains(elements[j]->x + 0.5 * elements[j]->w, elements[j]->y);
                    bool bottomOfBall = elements[i]->contains(elements[j]->x + 0.5 * elements[j]->w, elements[j]->y - elements[j]->h);

                    if (topOfBall || bottomOfBall && elements[i]->isPowerup == false) {

                        // system("gnome-terminal -e \"python playwav.py clang.wav &;\"");
                        system("cd sounds; python playwav.py break.wav > /dev/null 2> /dev/null &");

                        //system("./example");

                        //cout << "Destroyed! " <<endl;

                        elements[1]->score += 20;

                        if (elements[i]->randNum % 3 == 0) //special nums are: 0, 3, 6, 9, 12, 18
                        {
                            elements[i]->isPowerup = true;
                            elements[i]->x += 0.5 * elements[i]->w;
                            elements[i]->w = 0.025;
                            elements[i]->h = 0.025;
                            elements[i]->objectName = "Powerup";
                            elements[i]->yDirectionSpeed = -0.01;
                            //cout<<"randNum: "<<elements[i]->randNum<<endl;
                            elements[i]->isPowerup = true;
                        }
                        else {
                            elements.erase(elements.begin() + i);
                        }

                        if (elements[i]->isPowerup == false)
                            elements[j]->yDirectionSpeed *= -1.0;
                    }
                }



            }
        }


        if (elements[1]->score > elements[1]->highScore)
            elements[1]->highScore = elements[1]->score;

        elements[0]->restoreColor();
    }


    void createBlocks() //Creates our blocks
    {

        // cout << "numBlocks: " << numBlocks << endl;
        float xPos = -0.9;
        float yPos = 0.9;
        float offset = 0.0;

        for (int i = 0; i < numBlocks; i++) {
            float r1 = ((float(rand()) / float(RAND_MAX)));
            float r2 = ((float(rand()) / float(RAND_MAX)));
            float r3 = ((float(rand()) / float(RAND_MAX)));


            // if(numBlocks == 10)
            // {

            //     if(yPos > -0.2)
            //     {
            //         yPos -= 0.1;
            //     }
            //     else
            //     {
            //         yPos = 0.9;
            //         xPos  += blockWidth + 0.2;
            //     }
            // }
            // else
            // {

            // int modNum = (numBlocks / 10) * 6;

            // int numPerRow = numBlocks % modNum;
            // cout << numPerRow << endl;


            // bool newLayer = xPos + blockWidth > (-0.9 + (blockWidth * numPerRow));

            // cout << "Block: " << i << "\t" << newLayer << endl;
            // cout << xPos + blockWidth << " > " << -0.9 + (blockWidth * numPerRow) << endl;


            // if (xPos + blockWidth >= (-0.9 + (blockWidth * numPerRow)))
            // {
            //     elements.push_back(new Block(xPos, yPos, blockWidth, 0.1, r1, r2, r3));
            //     offset += blockWidth / 2;
            //     xPos = -0.9 + offset;
            //     yPos -= 0.1;
            //     numPerRow = numPerRow - 1;
            // }

            // }
            if (xPos + 0.30 > 1 )
            {
                offset += 0.2;
                xPos = -0.9 + offset;
                yPos -= 0.1;
            }


            elements.push_back(new Block(xPos, yPos, blockWidth, 0.1, r1, r2, r3));
            xPos += blockWidth;


            // // if(numBlocks == 10)
            // // {

            // //     if(yPos > -0.2)
            // //     {
            // //         yPos -= 0.1;
            // //     }
            // //     else
            // //     {
            // //         yPos = 0.9;
            // //         xPos  += blockWidth + 0.2;
            // //     }
            // // }
            // // else
            // // {

            // if (xPos + blockWidth > 1 - offset && (xPos + offset) != (1 - offset))
            // {
            //     offset += 0.2;
            //     xPos = -0.9 + offset;
            //     yPos -= 0.1;
            // }

            // // }
            // //   if(xPos + 0.30 > 1 )
            // // {
            // //     offset += 0.2;
            // //     xPos = -0.9 + offset;
            // //     yPos -= 0.1;
            // // }

            // elements.push_back(new Block(xPos, yPos, blockWidth, 0.1, r1, r2, r3));
            // xPos += blockWidth;
        }
    }

    void createHUD()
    {

        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-0.9, -0.95);

        stringstream s1;
        s1 << elements[1]->score;
        string scoreString = s1.str();

        stringstream s2;
        s2 << elements[1]->lives;
        string livesString = s2.str();

        stringstream s3;
        s3 << elements[1]->highScore;
        string highScoreString = s3.str();

        stringstream s4;
        s4 << level;
        string levelString = s4.str();


        string output = "Score: " + scoreString + "      Lives: " + livesString;
        glutBitmapString(GLUT_BITMAP_HELVETICA_12,
                         (const unsigned char*)output.c_str());

        glRasterPos2f(0.60, -0.95);

        string output2 = "High Score: " + highScoreString;
        glutBitmapString(GLUT_BITMAP_HELVETICA_12,
                         (const unsigned char*)output2.c_str());


        glRasterPos2f(0.40, -0.95);

        string output3 = "Level: " + levelString;
        glutBitmapString(GLUT_BITMAP_HELVETICA_12,
                         (const unsigned char*)output3.c_str());



        glRasterPos2f(-0.25, -0.95);

        string powerString = "Powerup: " + elements[0]->powerupName;
        glutBitmapString(GLUT_BITMAP_HELVETICA_12,
                         (const unsigned char*)powerString.c_str());


        if (elements[1]->x == 0.0 && elements[1]->y == 0.0 && elements[1]->lives != 0)
        {


            elements[0]->x = -0.25;
            glRasterPos2f(-0.10, -0.3);
            string pressSpace = "Press space";
            glutBitmapString(GLUT_BITMAP_HELVETICA_12,
                             (const unsigned char*)pressSpace.c_str());

        }


        float currentNumberOfBlocks = 0;

        for (int i = 2; i < elements.size(); i++)
        {
            if (elements[i]->objectName == "Block")
                currentNumberOfBlocks++;
        }

        float percentComplete =  (-1 + (1 - (currentNumberOfBlocks / numBlocks)) * 2);

        // cout << percentComplete << endl;




        glColor3f(0.0, 1.0, 0.0); //left bar
        glBegin(GL_POLYGON);
        glVertex2f(-1.0, -0.98);
        glVertex2f(percentComplete, -0.98);
        glVertex2f(percentComplete, -1.0);
        glVertex2f(-1.0, -1.0);
        glEnd();


        glColor3f(1.0, 0.2, 0.0); //left bar
        glBegin(GL_POLYGON);
        glVertex2f(-1.0, 1.0);
        glVertex2f(-0.96, 1.0);
        glVertex2f(-0.96, -1.0);
        glVertex2f(-1.0, -1.0);
        glEnd();

        glColor3f(1.0, 0.2, 0.0); //right bar
        glBegin(GL_POLYGON);
        glVertex2f(0.96, 1.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(1.0, -1.0);
        glVertex2f(0.96, -1.0);
        glEnd();

        glColor3f(1.0, 0.0, 0.0); //Powerup bar
        glBegin(GL_POLYGON);
        glVertex2f(-0.30, -0.89);
        glVertex2f(0.25, -0.89);
        glVertex2f(0.25, -1.0);
        glVertex2f(-0.30, -1.0);
        glEnd();

        glColor3f(1.0, 0.2, 0.0); //center bar
        // glBegin(GL_POLYGON);
        // glVertex2f(-1.0, -0.89);
        // glVertex2f(1.0, -0.89);
        // glVertex2f(1.0, -1.0);
        // glVertex2f(-1.0, -1.0);
        // glEnd();

        //glColor3f(0.8, 0.4, 0.0); //center bar
        glBegin(GL_POLYGON);
        glVertex2f(-1.0, -0.89);
        glVertex2f(1.0, -0.89);
        glVertex2f(1.0, -1.0);
        glVertex2f(-1.0, -1.0);
        glEnd();



        // glColor3f(0.2, 0.4, 0.2);    //background color
        // glBegin(GL_POLYGON);
        // glVertex2f(-1.0, 1.0);
        // glVertex2f(-1.0, -1.0);
        // glVertex2f(1.0, -1.0);
        // //glVertex2f(-1.0, -1.0);
        // glEnd();

        glColor3f(0.2, 0.2, 0.0); //background color
        glBegin(GL_POLYGON);
        glVertex2f(-1.0, 1.0);
        glVertex2f(1.0, 1.0);
        glColor3f(1.0, 0.2, 0.0);
        glVertex2f(1.0, -1.0);
        glVertex2f(-1.0, -1.0);
        glEnd();
    }

    void draw() //Draws all elements inside of the element vector, (paddles, ball, blocks, etc...)
    {

        int blockNums = 0;
        for (int i = 2; i < elements.size(); i++)
        {

            if (elements[i]->objectName == "Block")
            {
                blockNums++;
            }

        }

        if (blockNums == 0)
        {
            level++;
            system("cd sounds; python playwav.py newLevel.wav > /dev/null 2> /dev/null &");
            numBlocks += 10;
            if (blockWidth > 0.1)
                blockWidth -= 0.05;
            for (int i = 2; i < elements.size(); i++)
            {
                if (elements[i]->objectName == "Ball")
                    elements.erase(elements.begin() + i);
            }


            elements[1]->x = 0;
            elements[1]->y = 0;
            elements[1]->xDirectionSpeed = 0.0;
            elements[1]->yDirectionSpeed = 0.0;
            createBlocks();
        }

        if (elements[1]->lives != 0)
        {
            deflect();
            for (int i = 0; i < elements.size(); i++) {
                elements[i]->draw();
            }

            createHUD();
        }

        else
        {


            // if (gameOver == true)
            // {
            //system("cd sounds; python playwav.py gameOver.wav > /dev/null 2> /dev/null &");
            //     gameOver = false;
            // }
            elements[0]->x = -0.25; //move paddle back to middle
            level = 1;
            numBlocks = 10;
            blockWidth = 0.30;

            for (int i = elements.size() - 1; i > 1; i--)
            {
                elements.erase(elements.begin() + i);

            }
            createBlocks();

            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2f(-0.15, 0);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>("Game Over!"));

            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2f(-0.16, -0.10);
            glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>("Press Space to start"));

            createHUD();
            glColor3f(0.2, 0.2, 0.0); //background color
            glBegin(GL_POLYGON);
            glVertex2f(-1.0, 1.0);
            glVertex2f(1.0, 1.0);
            glColor3f(1.0, 0.2, 0.0);
            glVertex2f(1.0, -1.0);
            glVertex2f(-1.0, -1.0);
            glEnd();
        }
    }
};

#endif