/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#ifndef EFFETBALL_APPLICATION
#define EFFETBALL_APPLICATION

#include <cmath>
#include "ofMain.h"
#include "Texture.h"
#include "Ball.h"
#include "Bat.h"
#include "Field.h"
#include "Vector.h"
#include "effetBallDrawing.h"
#include "Quaternionen.h"

class EffetBall : public ofBaseApp
{
private:
    float fieldOfView, farPlane, nearPlane;
    float sizeOfArea, depth, viewWidth;

    ofImage ballImage;
    Texture ballTexture;

    Field *area;
    Bat *player1;
    Bat *player2;
    Ball *ball;

    int mouseX, mouseY;
    ofTrueTypeFont vag, vagHeader;

    static int score1;
    static int score2;
    static int gameLength;
    static int mode;
    static int menu;
    static int option;
    static int difficulty;
    static int shadow;
    static int depthLine;
    enum options {difficultyConfiguration, shadowConfiguration, depthLineConfiguration, gameLengthConfiguration};
    enum modi {Single, Multi, Options, Menu, Win};
    enum difficultyLevel {Easy, Medium, Hard};

    bool bat1_left, bat1_right, bat1_up, bat1_down,
        bat2_left, bat2_right, bat2_up, bat2_down;

    void newGame();
    Vector simpleKI(const Ball&, const Bat&);

public:
    EffetBall();
    ~EffetBall();
    void setup();
    void update();
    void draw();

    ofTrueTypeFont 	vagRounded;

    void keyHandle(int key, bool pressed);
    void keyHandleMenu(int key);
    void keyHandleOptions(int key);
    Vector batVector();
    Vector bat2Vector();

    void batAreaCollision(Field* area, Bat* bat);
    void ballAreaCollision(Ball* ball, Field* area);
    void ballBatCollision(Ball* ball, Bat* bat);

    void drawMenu();
    void drawOptions();
    void drawWinScreen();
    void drawingScene(int player);
    void drawText(string text, bool header, float x, float y, int r, int g, int b, int a);

    void camera(Vector center, float eyeDepth=0, float eyeVertical=0, float eyeHorizontal=0);
    void viewPort(int rows, int cols, int pos, float screenWidth, float screenHeight);

    void setLight(int i, float r, float g, float b);
    void setShinyMaterial();
    void setShinyGlowMaterial(float,float,float);
    void setMatteMaterial();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
};

#endif
