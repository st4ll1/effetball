/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#include "EffetBall.h"

//#define DEBUG_KEYBOARD_CONTROL
//#define DEBUG_KI
//#define DEBUG

#define PLAYER1_RED 255
#define PLAYER1_GREEN 0
#define PLAYER1_BLUE 0

#define PLAYER2_RED 0
#define PLAYER2_GREEN 255
#define PLAYER2_BLUE 0

#define DEPTHLINE_COLOR_RED 0
#define DEPTHLINE_COLOR_GREEN 0
#define DEPTHLINE_COLOR_BLUE 0

#define TEXT_COLOR_RED 255
#define TEXT_COLOR_GREEN 0
#define TEXT_COLOR_BLUE 0

#define SELECTED_TEXT_COLOR_RED 255
#define SELECTED_TEXT_COLOR_GREEN 255
#define SELECTED_TEXT_COLOR_BLUE 0

#define WALL_BALL_FRICTION 0.0f
#define BAT_BALL_FRICTION 1.0f

#define FONT_HEADER 120
#define FONT_NORMAL 50

//connected to areasize (areasize/x)
#define BALL_SIZE 20
#define BALL_SPEED 50

#define BAT_SIZE 5
#define BAT_SPEED 30
#define BAT_POS 10

//options
int EffetBall::mode = EffetBall::Menu;
int EffetBall::menu = EffetBall::Single;
int EffetBall::difficulty = EffetBall::Easy;
int EffetBall::shadow = 2;
int EffetBall::option = 0;
int EffetBall::depthLine = 1;
int EffetBall::gameLength = 10;
int EffetBall::score1 = 0;
int EffetBall::score2 = 0;

EffetBall::EffetBall(){

}

EffetBall::~EffetBall(){
    delete area;
    delete ball;
    delete player1;
    delete player2;
}

//--------------------------------------------------------------
void  EffetBall::setup(){
    ofSetWindowTitle("Effet Ball v0.5");
    ofSetVerticalSync(true);
    ofDisableSetupScreen();
    ofSetFrameRate(60);
    viewWidth = sizeOfArea = ofGetWidth();
    if(ofGetWidth()>ofGetHeight()) sizeOfArea = ofGetWidth();
	depth = 4*sizeOfArea;
    fieldOfView = ofRadToDeg(1.2*atan(sizeOfArea/depth));
    nearPlane = 0.1;
    farPlane = depth*3;

    //create the elements for the game
    area = new Field( Vector( 0,0,0), Vector( sizeOfArea, depth, sizeOfArea));
    ball = new Ball( area->GetMiddle(), Vector(), sizeOfArea/BALL_SIZE, sizeOfArea/BALL_SPEED);
    float batSize = sizeOfArea/BAT_SIZE;
    player1 = new Bat(area->GetMiddle()+Vector(-batSize/2,-depth/2+sizeOfArea/BAT_POS,-batSize/2),batSize,sizeOfArea/BAT_SPEED);
    player2 = new Bat(area->GetMiddle()+Vector(-batSize/2,depth/2-sizeOfArea/BAT_POS,-batSize/2),batSize,sizeOfArea/BAT_SPEED);

    //load font
    vag.loadFont("vag.ttf", FONT_NORMAL);
    vagHeader.loadFont("vag.ttf", FONT_HEADER);
    //load ball texture
    bool result = ballImage.loadImage("BeachBall.jpg");
    if(!result){
        ofLog(OF_LOG_ERROR, "Failed to load image");
    }
    ballTexture.load(ballImage, GL_REPEAT, GL_LINEAR);

    // enable back-face culling
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void EffetBall::newGame(){
    sizeOfArea = ofGetWidth();

	depth = 4*sizeOfArea;
	if(mode == Multi) fieldOfView = ofRadToDeg(1.8*atan(sizeOfArea/depth));
	else fieldOfView = ofRadToDeg(1.1*atan(sizeOfArea/depth));
    score1 = score2 = 0;
    bat1_left = bat1_right = bat1_up = bat1_down = bat2_left = bat2_right = bat2_up = bat2_down = false;

    ball->Reset(ofRandom(0,1)<0.5 ? true : false);
}

void toggleMouseAttract() {

}

//--------------------------------------------------------------
void EffetBall::update() {
    if(mode == Multi) viewWidth=ofGetWidth()/2;
    else viewWidth=ofGetWidth();
    if(mode == Single || mode == Multi){
            //handle bat of player2
            player2->Slowdown();
            if(mode == Multi){
                player2->SetDirection(bat2Vector());
                if(bat2_right || bat2_left || bat2_up || bat2_down)
                    player2->Accelerate();
            }
            else
            {
                player2->SetDirection(simpleKI(*ball,*player2));
                player2->Accelerate();
            }
            player2->Move();
            batAreaCollision(area, player2);

            //handle bat of player1
            player1->Slowdown();
            player1->SetDirection(batVector());
            if(bat1_right || bat1_left || bat1_up || bat1_down)
                player1->Accelerate();
            player1->Move();
            batAreaCollision(area, player1);

            ballBatCollision(ball, player1);
            ballBatCollision(ball, player2);
            ballAreaCollision(ball, area);
            ball->Move();

            #ifdef DEBUG
                cout << "speed: " << ball->GetSpeed() << " directionLenght: "
                    << ball->GetDirection().length() << endl;
                cout << "ball position: " << endl
                    << "x: " << ball->pos.x << " y : " << ball->pos.y << " z:" << ball->pos.z << endl;

            #endif
    }

    #ifdef DEBUG_KEYBOARD_CONTROL
        cout << "bat1: " << endl
        << "right: " << bat1_right
        << " left: " << bat1_left
        << " up: " << bat1_up
        << " down: " << bat1_down << endl;

        cout << "bat2: " << endl
        << "right: " << bat2_right
        << " left: " << bat2_left
        << " up: " << bat2_up
        << " down: " << bat2_down << endl;
    #endif
}

void EffetBall::batAreaCollision(Field* area, Bat* bat){
    if(area->GetXmin() > bat->pos.x) bat->pos.x = area->GetXmin();
    if(area->GetYmin() > bat->pos.y) bat->pos.y = area->GetYmin();
    if(area->GetZmin() > bat->pos.z) bat->pos.z = area->GetZmin();
    if(area->GetXmax()-bat->GetSize().x <= bat->pos.x) bat->pos.x = area->GetXmax()-bat->GetSize().x;
    if(area->GetYmax()-bat->GetSize().y <= bat->pos.y) bat->pos.y = area->GetYmax()-bat->GetSize().y;
    if(area->GetZmax()-bat->GetSize().z <= bat->pos.z) bat->pos.z = area->GetZmax()-bat->GetSize().z;
}

void EffetBall::ballAreaCollision(Ball* ball, Field* area){
    float rad = ball->GetRadius();
    if ((area->GetXmin() + rad) > ball->GetNextX() || (area->GetXmax() - rad) < ball->GetNextX())
    {
        ball->turnX(Vector(),WALL_BALL_FRICTION);
    }
    if ((area->GetZmin() + rad) > ball->GetNextZ() || (area->GetZmax() - rad) < ball->GetNextZ())
    {
        ball->turnZ(Vector(),WALL_BALL_FRICTION);
    }
    if ((area->GetYmin() + rad) > ball->GetNextY() || (area->GetYmax() - rad) < ball->GetNextY())
    {
        if((area->GetYmax() + area->GetYmin())/2 < ball->pos.y)
        {
            score1++;
            if(score1 == gameLength) mode = Win;
            ball->Reset(true);
        }
        else
        {
            score2++;
            if(score2 == gameLength) mode = Win;
            ball->Reset(false);
        }
    }
}

void EffetBall::ballBatCollision(Ball* ball, Bat* bat){
    Vector batSize = bat->GetSize();
    batSize.x += 2*ball->GetRadius();
    batSize.y += 2*ball->GetRadius();
    batSize.z += 2*ball->GetRadius();
    Vector batPosition = bat->pos;
    batPosition.x -= ball->GetRadius();
    batPosition.y -= ball->GetRadius();
    batPosition.z -= ball->GetRadius();
    Vector batDirection = bat->GetDirection();
    Vector ballDirection = ball->GetDirection();
    Vector ballPosition = ball->pos;

    Vector tempBatPosition;
    //minT only have to be over 1.0f
    float minT = 2.0f;
    char dimension;

    //begin of detection
    //Y Dimension
    //Calculate when ball reaches y of bat
    float t = (batPosition.y-ball->pos.y)/ballDirection.y;
    if(t<=1 && t>=0 && ball->pos.y < batPosition.y){
        tempBatPosition = batPosition + (batDirection*t);
        //check if ball hit at time t the bat
        if( ball->pos.x <= tempBatPosition.x+batSize.x && ball->pos.x >= tempBatPosition.x &&
            ball->pos.z <= tempBatPosition.z+batSize.z && ball->pos.z >= tempBatPosition.z)
        {
            //check if it is the first contact
            if(minT > t){
                minT = t;
                dimension='y';
            }
        }
    }
    //following code is for the other five sides of the bat
    t = (batPosition.y+batSize.y-ball->pos.y)/ballDirection.y;
    if(t<=1 && t>=0 && ball->pos.y > batPosition.y+batSize.y){
        tempBatPosition = batPosition + (batDirection*t);
        if( ball->pos.x <= tempBatPosition.x+batSize.x && ball->pos.x >= tempBatPosition.x &&
            ball->pos.z <= tempBatPosition.z+batSize.z && ball->pos.z >= tempBatPosition.z)
        {
            if(minT > t){
                minT = t;
                dimension='y';
            }
        }
    }

    //Z Dimension
    t = (batPosition.z+batSize.z-ball->pos.z)/ballDirection.z;
    if(t<=1 && t>=0){
        tempBatPosition = batPosition + (batDirection*t);
        if( ball->pos.y <= tempBatPosition.y+batSize.y && ball->pos.y >= tempBatPosition.y &&
            ball->pos.x <= tempBatPosition.x+batSize.x && ball->pos.x >= tempBatPosition.x)
        {
            if(minT > t){
                minT = t;
                dimension='z';
            }
        }
    }
    t = (batPosition.z-ball->pos.z)/ballDirection.z;
    if(t<=1 && t>=0){
        tempBatPosition = batPosition + (batDirection*t);
        if( ball->pos.y <= tempBatPosition.y+batSize.y && ball->pos.y >= tempBatPosition.y &&
            ball->pos.x <= tempBatPosition.x+batSize.x && ball->pos.x >= tempBatPosition.x)
        {
            if(minT > t){
                minT = t;
                dimension='z';
            }
        }
    }
    //X Dimension
    t = (batPosition.x-ball->pos.x)/ballDirection.x;
    if(t<=1 && t>=0){
        tempBatPosition = batPosition + (batDirection*t);
        if( ball->pos.y <= tempBatPosition.y+batSize.y && ball->pos.y >= tempBatPosition.y &&
            ball->pos.z <= tempBatPosition.z+batSize.z && ball->pos.z >= tempBatPosition.z)
        {
            if(minT > t){
                minT = t;
                dimension='x';
            }
        }
    }
    t = (batPosition.x+batSize.x-ball->pos.x)/ballDirection.x;
    if(t<=1 && t>=0){
        tempBatPosition = batPosition + (batDirection*t);
        if( ball->pos.y <= tempBatPosition.y+batSize.y && ball->pos.y >= tempBatPosition.y &&
            ball->pos.z <= tempBatPosition.z+batSize.z && ball->pos.z >= tempBatPosition.z)
        {
            if(minT > t){
                minT = t;
                dimension='x';
            }
        }
    }
    //end of detection

    if(minT < 1){
        if(dimension == 'y')
            ball->turnY(bat->GetDirection(),BAT_BALL_FRICTION);
        if(dimension == 'x')
            ball->turnX(bat->GetDirection(),BAT_BALL_FRICTION);
        if(dimension == 'z')
            ball->turnZ(bat->GetDirection(),BAT_BALL_FRICTION);
    }
}

//--------------------------------------------------------------
void EffetBall::draw() {
    //clear screen
    glClearColor(0.0,0.0,0.5,1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    float windowWidth = ofGetWidth();
    float windowHeight = ofGetHeight();
    switch(mode){
        case Win:
            drawWinScreen();
            break;
        case Menu:
            drawMenu();
            break;
        case Options:
            drawOptions();
            break;
        case Single:
            //Screen Player
            viewPort(1,1,1,windowWidth, windowHeight);
            camera(area->GetMiddle(), -depth*1.5);
            drawingScene(1);
            drawText(ofToString(score2),false,100,100,PLAYER2_RED,PLAYER2_GREEN,PLAYER2_BLUE,255);
            drawText(ofToString(score1),false,windowWidth-200,100,PLAYER1_RED,PLAYER1_GREEN,PLAYER1_BLUE,255);
            break;
        case Multi:
            //Screen Player 2
            viewPort(1,2,1,windowWidth, windowHeight);
            camera(area->GetMiddle(), depth*1.5);
            drawingScene(2);
            drawText(ofToString(score1),false,30,100,PLAYER1_RED,PLAYER1_GREEN,PLAYER1_BLUE,255);
            //Screen Player 1
            viewPort(1,2,2,windowWidth, windowHeight);
            camera(area->GetMiddle(), -depth*1.5);
            drawingScene(1);
            drawText(ofToString(score2),false,30,100,PLAYER2_RED,PLAYER2_GREEN,PLAYER2_BLUE,255);
            break;
    }
}

void EffetBall::drawMenu(){
    float height = ofGetHeight();
    float width = ofGetWidth();
    drawText("Effet Ball", true, (width-vagHeader.stringWidth("Effet Ball"))/2, vagHeader.getLineHeight(), 0, 150, 0,255);
    if(menu==Single) drawText("Singleplayer", false, 100, height/2,
                              SELECTED_TEXT_COLOR_RED, SELECTED_TEXT_COLOR_GREEN, SELECTED_TEXT_COLOR_BLUE,255);
    else drawText("Singleplayer", false, 100, height/2, TEXT_COLOR_RED, TEXT_COLOR_GREEN, TEXT_COLOR_BLUE,255);
    if(menu==Multi) drawText("Multiplayer", false, 100, height/2+vag.getLineHeight(),
                             SELECTED_TEXT_COLOR_RED, SELECTED_TEXT_COLOR_GREEN, SELECTED_TEXT_COLOR_BLUE ,255);
    else drawText("Multiplayer", false, 100, height/2+vag.getLineHeight(), TEXT_COLOR_RED, TEXT_COLOR_GREEN, TEXT_COLOR_BLUE ,255);
    if(menu==Options)drawText("Options", false, 100, height/2+2*vag.getLineHeight(),
                              SELECTED_TEXT_COLOR_RED, SELECTED_TEXT_COLOR_GREEN, SELECTED_TEXT_COLOR_BLUE ,255);
    else drawText("Options", false, 100, height/2+2*vag.getLineHeight(), TEXT_COLOR_RED, TEXT_COLOR_GREEN, TEXT_COLOR_BLUE ,255);
    drawText("by Andreas Stallinger", false, width-10-vag.stringWidth("by Andreas Stallinger"),height-vag.getLineHeight()/2,255,165,0,255);
}

void EffetBall::drawWinScreen(){
    if(score1==gameLength) drawText("Player1",false, ofGetWidth()/2-vag.stringWidth("Player1")/2, ofGetHeight()/2,PLAYER1_RED,PLAYER1_GREEN,PLAYER1_BLUE,255);
            else drawText("Player2",false, ofGetWidth()/2-vag.stringWidth("Player2")/2, ofGetHeight()/2,PLAYER2_RED,PLAYER2_GREEN,PLAYER2_BLUE,255);
            drawText("wins",false, ofGetWidth()/2-vag.stringWidth("wins")/2, ofGetHeight()/2+vag.getLineHeight(),255,255,0,255);
}

void EffetBall::drawOptions(){
    float height = ofGetHeight();
    float width = ofGetWidth();
    float lineHeight = vag.getLineHeight();
    drawText("Options", true, (width-vagHeader.stringWidth("Options"))/2, vagHeader.getLineHeight(), 0, 150, 0,255);

    drawText("Difficulty", false, 10, height/2, 255, (menu==Multi?255:0),0,(option==difficultyConfiguration?255:150));
    drawText("Easy", false, width/4+100, height/2, 255, (difficulty==Easy?255:0), 0, (option==difficultyConfiguration?255:150));
    drawText("Medium", false, width/2, height/2, 255, (difficulty==Medium?255:0), 0, (option==difficultyConfiguration?255:150));
    drawText("Hard", false, width/4*3, height/2, 255, (difficulty==Hard?255:0), 0, (option==difficultyConfiguration?255:150));

    drawText("Shadow", false, 10, height/2+lineHeight, 255, (menu==Multi?255:0),0, (option==shadowConfiguration?255:150));
    drawText("Non", false, width/4+100, height/2+lineHeight, 255, (shadow==0?255:0), 0, (option==shadowConfiguration?255:150));
    drawText("Bottom", false, width/2, height/2+lineHeight, 255, (shadow==1?255:0), 0, (option==shadowConfiguration?255:150));
    drawText("AllSides", false, width/4*3, height/2+lineHeight, 255, (shadow==2?255:0), 0, (option==shadowConfiguration?255:150));

    drawText("Depth", false, 10, height/2+2*lineHeight, 255, (menu==Options?255:0), 0, (option==depthLineConfiguration?255:150));
    drawText("Non", false, width/4+100, height/2+2*lineHeight, 255, (depthLine==0?255:0), 0, (option==depthLineConfiguration?255:150));
    drawText("Line", false, width/2, height/2+2*lineHeight, 255, (depthLine==1?255:0), 0, (option==depthLineConfiguration?255:150));

    drawText("Gamelength", false, 10, height/2+3*lineHeight, 255, (depthLine==2?255:0), 0, (option==gameLengthConfiguration?255:150));
    drawText("4", false, width/2, height/2+3*lineHeight, 255, (gameLength==4?255:0), 0, (option==gameLengthConfiguration?255:150));
    drawText("6", false, width/2+75, height/2+3*lineHeight, 255, (gameLength==6?255:0), 0, (option==gameLengthConfiguration?255:150));
    drawText("8", false, width/2+150, height/2+3*lineHeight, 255, (gameLength==8?255:0), 0, (option==gameLengthConfiguration?255:150));
    drawText("10", false, width/2+225, height/2+3*lineHeight, 255, (gameLength==10?255:0), 0, (option==gameLengthConfiguration?255:150));

    drawText("(M)enu", false, 100, height-50, 255,0,0,255);
}

void EffetBall::viewPort(int rows, int cols, int pos, float screenWidth, float screenHeight){
    if(rows && cols && pos && pos <= cols*rows){
        glViewport(
            screenWidth/cols*((pos-1)%cols),
            screenHeight/rows*((pos-1)/cols),
            screenWidth/cols,
            screenHeight/rows);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fieldOfView, (float)(screenWidth/cols) / (screenHeight/rows),nearPlane, farPlane);
    }
}

void EffetBall::camera(Vector center, float eyeDepth, float eyeVertical, float eyeHorizontal){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    ofPoint eye, up;
    eye.x=center.x+eyeHorizontal;
    eye.y=center.y+eyeDepth;
    eye.z=center.z+eyeVertical;
    up.x = 0.0;
    up.y = 0.0;
    up.z = 1.0;
    gluLookAt(eye.x,eye.y,eye.z,center.x,center.y,center.z,up.x,up.y,up.z);
}
//--------------------------------------------------------------

void EffetBall::drawText(string text, bool header, float x, float y, int r, int g, int b, int a){
    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	    glLoadIdentity();
		glOrtho(0, viewWidth, ofGetHeight(), 0, 0.0f, 10.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			ofSetColor(r,g,b,a);
			if(header)vagHeader.drawString(text, x, y);
			else vag.drawString(text, x, y);
        glPopMatrix();
	glPopMatrix();
}

void EffetBall::drawingScene(int player){
    glPushMatrix();
        drawField(*area);
        //draw ball and ballshadow
        ballTexture.bind();
        drawBall(*ball);
        ballTexture.unbind();

        //ball depth
        drawDepthLine(*area, ball->pos.y, depthLine, 0,0,0);
        //player1 depth
        drawDepthLine(*area, player1->pos.y, depthLine, (float)PLAYER1_RED/255,(float)PLAYER1_GREEN/255,(float)PLAYER1_BLUE/255);
        //player2 depth
        drawDepthLine(*area, player2->pos.y, depthLine, (float)PLAYER2_RED/255,(float)PLAYER2_GREEN/255,(float)PLAYER2_BLUE/255);

        //draw elements with alpha
        glEnable(GL_BLEND);
        drawBallShadow(*ball, *area, shadow);
        drawBatShadow(*player1, *area, shadow);
        drawBatShadow(*player2, *area, shadow);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if(player == 1)
            drawBat(*player2, (float)PLAYER2_RED/255,(float)PLAYER2_GREEN/255,(float)PLAYER2_BLUE/255);
        drawBat(*player1, (float)PLAYER1_RED/255,(float)PLAYER1_GREEN/255,(float)PLAYER1_BLUE/255);
        if(player == 2)
            drawBat(*player2, (float)PLAYER2_RED/255,(float)PLAYER2_GREEN/255,(float)PLAYER2_BLUE/255);

        glEnable(GL_LIGHTING);

        setLight(0,1,0,0);

        glDisable(GL_BLEND);
        glDisable(GL_LIGHTING);
    glPopMatrix();

}

//--------------------------------------------------------------

void EffetBall::setLight(int i, float r, float g, float b){
    glEnable(GL_LIGHT0 + i);
    float diffuse[] = {r,g,b, 1.0};
    float specular[] = {r,g,b, 1.0};
    float ambient[] = {0.1*r,0.1*g,0.1*b,1.0};
    float position[] = {0.0,0.0,0.0,0.5};
    glLightfv(GL_LIGHT0 + i, GL_DIFFUSE,diffuse);
    glLightfv(GL_LIGHT0 + i, GL_SPECULAR,specular);
    glLightfv(GL_LIGHT0 + i, GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0 + i, GL_POSITION,position);
    //glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 0.8f);
    //glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0.08f);
    glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 0.08f);
}

void EffetBall::setShinyMaterial(){
    float specular[] = {1.0,1.0,1.0,0.5};
    float emission[] = {0.0,0.0,0.0,1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 40);
    glEnable(GL_COLOR_MATERIAL);
}

void EffetBall::setShinyGlowMaterial(float r,float g, float b){
    float specular[] = {1.0,1.0,1.0,1.0};
    float emission[] = {r,g,b,1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 40);
    glEnable(GL_COLOR_MATERIAL);
}

void EffetBall::setMatteMaterial(){
    float specular[] = {0.8,0.8,0.8,0.5};
    float emission[] = {0.0,0.0,0.0,0.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glEnable(GL_COLOR_MATERIAL);
}

//--------------------------------------------------------------
void EffetBall::keyPressed(int key){
    if(key=='p' || key == 'P'){
        ofImage screenShot;
        screenShot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        screenShot.saveImage("screenShot.png");
    }
    switch(mode){
        case Multi:
        case Single:
            keyHandle(key, true);
            break;
        case Menu:
            keyHandleMenu(key);
            break;
        case Options:
            keyHandleOptions(key);
            break;
        case Win:
            mode = Menu;
            break;
    }
}

void EffetBall::keyReleased  (int key){
    if(mode == Multi || mode == Single){
        keyHandle(key, false);
    }
}
//--------------------------------------------------------------

void EffetBall::windowResized(int w, int x){};
void EffetBall::mouseMoved(int x, int y){
	mouseX = x;
	mouseY = y;
};
void EffetBall::mouseReleased(int x, int y, int b){

};

void EffetBall::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void EffetBall::mousePressed(int x, int y, int button){

}

void EffetBall::keyHandle(int key, bool pressed){
    switch (key)
    {
        case OF_KEY_LEFT:
            bat1_left = pressed;
            break;
        case OF_KEY_RIGHT:
            bat1_right = pressed;
            break;
        case OF_KEY_UP:
            bat1_up = pressed;
            break;
        case OF_KEY_DOWN:
            bat1_down = pressed;
            break;
        case 'a':
        case 'A':
            bat2_right = pressed;
            break;
        case 'd':
        case 'D':
            bat2_left = pressed;
            break;
        case 'w':
        case 'W':
            bat2_up = pressed;
            break;
        case 's':
        case 'S':
            bat2_down = pressed;
            break;
        case 'm':
        case 'M':
            mode = Menu;
            break;
    }
}

void EffetBall::keyHandleMenu(int key){
    switch(key){
        case OF_KEY_DOWN:
            menu++;
            if(menu==3)menu = 0;
            break;
        case OF_KEY_UP:
            if(menu==0)menu = 3;
            menu--;
            break;
        case OF_KEY_RETURN:
            mode = menu;
            newGame();
            break;
    }
}

void EffetBall::keyHandleOptions(int key){
    switch(key){
        case OF_KEY_DOWN:
            option++;
            if(option==4)option = 0;
            break;
        case OF_KEY_UP:
            if(option==0)option = 4;
            option--;
            break;
        case OF_KEY_LEFT:
            switch(option){
                case difficultyConfiguration:
                    if(difficulty==0)difficulty = 3;
                    difficulty--;
                    break;
                case shadowConfiguration:
                    if(shadow==0)shadow = 3;
                    shadow--;
                    break;
                case depthLineConfiguration:
                    if(depthLine==0)depthLine=2;
                    depthLine--;
                    break;
                case gameLengthConfiguration:
                    if(gameLength==4) gameLength=12;
                    gameLength-=2;
                    break;
            }
            break;
        case OF_KEY_RIGHT:
            switch(option){
                case difficultyConfiguration:
                    difficulty++;
                    if(difficulty==3)difficulty = 0;
                    break;
                case shadowConfiguration:
                    shadow++;
                    if(shadow==3)shadow = 0;
                    break;
                case depthLineConfiguration:
                    depthLine++;
                    if(depthLine==2)depthLine=0;
                    break;
                case gameLengthConfiguration:
                    gameLength+=2;
                    if(gameLength==12)gameLength=4;
                    break;
            }
            break;
        case 'm':
        case 'M':
            mode = Menu;
            break;
    }
}

//direction of player1
Vector EffetBall::batVector(){
    Vector v(0,0,0);
    if (bat1_left)v.Add(Vector(-1,0,0));
    if (bat1_right)v.Add(Vector(1,0,0));
    if (bat1_up)v.Add(Vector(0,0,1));
    if (bat1_down)v.Add(Vector(0,0,-1));
    return v;
}

//direction of player2 (multiplayer)
Vector EffetBall::bat2Vector(){
    Vector v(0,0,0);
    if (bat2_left)v.Add(Vector(-1,0,0));
    if (bat2_right)v.Add(Vector(1,0,0));
    if (bat2_up)v.Add(Vector(0,0,1));
    if (bat2_down)v.Add(Vector(0,0,-1));
    return v;
}

//direction of player2 (singleplayer)
Vector EffetBall::simpleKI(const Ball& ball, const Bat& bat){
    Vector direction(0,0,0);
    Vector batSize = bat.GetSize();
    float move = ofRandom(0,30);
    if(move < (difficulty+1)*3){
        //left
        if(ball.pos.x < bat.pos.x + batSize.x/4 ) direction.Add(Vector(-1,0,0));
        //right
        else if(ball.pos.x > bat.pos.x + batSize.x/4*3) direction.Add(Vector(1,0,0));
        //top
        if(ball.pos.z < bat.pos.z + batSize.z/4) direction.Add(Vector(0,0,-1));
        //bottom
        else if(ball.pos.z > bat.pos.z + batSize.z/4*3)direction.Add(Vector(0,0,1));
    }

    #ifdef DEBUG_KI
        cout << "direction:" << endl
            << "x: " << direction.x
            << " y: " << direction.y
            << " z: " << direction.z << endl
            << " difficulty: " << difficulty << endl;
    #endif

    return direction;
}
