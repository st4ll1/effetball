#include "control.h"
//Keyboard Class
void Keyboard::keyReleased(int key){
    switch (key)
    {
        case OF_KEY_LEFT:
            bat1_left = false;
            break;
        case OF_KEY_RIGHT:
            bat1_right = false;
            break;
        case OF_KEY_UP:
            bat1_up = false;
            break;
        case OF_KEY_DOWN:
            bat1_down = false;
            break;
        case 'a':
            bat2_right = false;
            break;
        case 'd':
            bat2_left = false;
            break;
        case 'w':
            bat2_up = false;
            break;
        case 's':
            bat2_down = false;
            break;
    }
}

void Keyboard::keyPressed(int key){
    switch (key)
    {
        case OF_KEY_LEFT:
            bat1_left = true;
            break;
        case OF_KEY_RIGHT:
            bat1_right = true;
            break;
        case OF_KEY_UP:
            bat1_up = true;
            break;
        case OF_KEY_DOWN:
            bat1_down = true;
            break;
        case 'a':
            bat2_right = true;
            break;
        case 'd':
            bat2_left = true;
            break;
        case 'w':
            bat2_up = true;
            break;
        case 's':
            bat2_down = true;
            break;
    }
}
Vector Keyboard::batVector(){
    Vector v(0,0,0);
    if (bat1_left)v.Add(Vector(-1,0,0));
    if (bat1_right)v.Add(Vector(1,0,0));
    if (bat1_up)v.Add(Vector(0,-1,0));
    if (bat1_down)v.Add(Vector(0,1,0));
    return v;
}
Vector Keyboard::bat2Vector(){
    Vector v(0,0,0);
    if (bat2_left)v.Add(Vector(-1,0,0));
    if (bat2_right)v.Add(Vector(1,0,0));
    if (bat2_up)v.Add(Vector(0,-1,0));
    if (bat2_down)v.Add(Vector(0,1,0));
    return v;
}
//End Keyboard Class
