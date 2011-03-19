/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#include "ofMain.h"
#include "EffetBall.h"
#include "Texture.h"
#include "ofAppGlutWindow.h"


//========================================================================

int main( ){
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_GAME_MODE);			// <-------- setup the GL context
	ofSetWindowPosition((ofGetScreenWidth()-1024)/2,(ofGetScreenHeight()-768)/2);
	ofRunApp( new EffetBall());
}
