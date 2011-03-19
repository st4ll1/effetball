/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include "Vector.h"
#include "ofMain.h"

class Keyboard{
    public:
    Keyboard(){
        bat1_down, bat1_left, bat1_ht, bat1_up = false;
        bat2_down, bat2_left, bat2_right, bat2_up = false;
    }

    void keyPressed(int key);
    void keyReleased(int key);
    Vector batVector();
    Vector bat2Vector();
    private:

    bool bat1_left;
    bool bat1_right;
    bool bat1_up;
    bool bat1_down;
    bool bat2_left;
    bool bat2_right;
    bool bat2_up;
    bool bat2_down;
};

#endif // CONTROL_H_INCLUDED
