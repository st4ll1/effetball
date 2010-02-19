#include "testApp.h"

#define BORDER 50.0
#define Zfactor width/2

//options
#define TASTATUR
static float rot = 0;

#ifdef TASTATUR
Keyboard k;
#endif

int score1 = 0;
int score2 = 0;

//Box size
static int          width;
static int          height;
static int          depth;

Vector bpos(0,0,0);//Startposition of the ball
Vector bdir(4,2,3);//Startdirection of the ball
Ball cball(bpos,bdir,20);//Ball
Vector cpos(0,0,0);//Vector to create the box, bat1 and bat2
Vector cdir(0,0,0);//Vector to create the box, bat1 and bat2
Box cbox(cpos, cdir);//playarea
Bat bat_player1(cpos, 100.0f,cbox);//bat of player 1
Bat bat_player2(cpos, 100.0f,cbox);//bat of player 2

void initScene()
{

}

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground(255, 255, 255);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    score1, score2 = 0;

    ofSetWindowTitle("Curveballvariante(alpha)");

    //load our typeface
    vagRounded.loadFont("vag.ttf", 50);

    //set the box
    setTheBox();
    // setup lighting
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0, height/2, 0.0, 0.0 };
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    // enable back-face culling (so we can see through the walls)
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void toggleMouseAttract()
{
}

void testApp::setTheBox()
{
    width = ofGetWidth();
    height = ofGetHeight();
    depth = Zfactor;
    cpos.SetX(-width/2+BORDER);
    cpos.SetY(-height/2+BORDER);
    cpos.SetZ(depth);
    cdir.SetX(width-BORDER*2);
    cdir.SetY(height-BORDER*2);
    cdir.SetZ(-depth*2);
    cbox.SetBox(cpos, cdir);
    bat_player1.SetZ(depth-30);
    bat_player2.SetZ(-depth+30);
    bat_player1.SetRange(cbox);
    bat_player2.SetRange(cbox);
}

//--------------------------------------------------------------
void testApp::update()
{
    setTheBox();
    bat_player1.SetDirection(k.batVector());
    bat_player1.move();
    bat_player2.SetDirection(k.bat2Vector());
    bat_player2.move();
    cball.Colid(bat_player1);
    cball.Colid(bat_player2);
    char c = cball.Move(cbox);
    switch (c)
    {
    case '1':
        score1++;
        break;
    case '2':
        score2++;
        break;
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    Drawing d;//Drawing-Object
    ofEnableAlphaBlending();
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    glViewport(0,0,width,height);
    glTranslatef(width/2, height/2, -depth); // center scene
    glRotatef(rot, 0, 1, 0);            // rotate scene
    glDisable(GL_LIGHTING);
    //draw box
    d.box(cbox);
    glEnable(GL_LIGHTING);
    // draw particles
    glColor4f(1, 1, 1, 0.8);
    // draw ball
    d.ball(cball);
    //draw bat
    d.bat(bat_player1);
    //draw bat player 2
    d.bat(bat_player2);
    // draw shadow ball
    d.ballShadow(cball, cbox);
    // draw shadow bat player 1
    d.batShadow(bat_player1, cbox);
    // draw shadow bat player 2
    d.batShadow(bat_player2, cbox);
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor4f(0, 0, 0, 1);
    //score display
    ofSetColor(0xFFFF00);
    vagRounded.drawString(ofToString(score1), 150, 50);
    ofSetColor(0x00FFFF);
    vagRounded.drawString(ofToString(score2), width-250, 50);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key)
{
    switch (key)
    {
    case OF_KEY_F11:
        ofToggleFullscreen();
        break;
    case '1':
        rot = 0;
        break;
    case '2':
        rot = 180;
        break;
    case 'n':
        ofAppGlutWindow test;
        ofSetupOpenGL(&test, 800,640, OF_WINDOW);			// <-------- setup the GL context

        // this kicks off the running of my app
        // can be OF_WINDOW or OF_FULLSCREEN
        // pass in width and height too:
        ofRunApp( new testApp());
        break;
    }
    k.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key)
{
    k.keyReleased(key);
}

//--------------------------------------------------------------

void testApp::windowResized(int w, int x){};
void testApp::mouseMoved(int x, int y){};
void testApp::mouseReleased(int x, int y, int b){};

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
}

