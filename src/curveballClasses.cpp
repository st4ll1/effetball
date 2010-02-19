#include "curveballClasses.h"
#include <cmath>

//Vector Class{

Vector::Vector(float xvalue, float yvalue, float zvalue): x(xvalue), y(yvalue), z(zvalue) {};

float Vector::GetX()
{
    return x;
}
float Vector::GetY()
{
    return y;
}
float Vector::GetZ()
{
    return z;
}
void Vector::SetX(float xvalue)
{
    x=xvalue;
}
void Vector::SetY(float yvalue)
{
    y=yvalue;
}
void Vector::SetZ(float zvalue)
{
    z=zvalue;
}
void Vector::SetNull()
{
    x,y,z=0;
}

bool Vector::Add(float xvalue, float yvalue, float zvalue)
{
    x += xvalue;
    y += yvalue;
    z += zvalue;
}
bool Vector::Add(Vector added)
{
    x+=added.GetX();
    y+=added.GetY();
    z+=added.GetZ();
    return true;
}
float Vector::length()
{
    return sqrt(x*x+y*y+z*z);
}

void Vector::Normalize()
{
    float l = length();
    x/=l;
    y/=l;
    z/=l;
}
void Vector::Scale(float factor)
{
    x*=factor;
    y*=factor;
    z*=factor;
}

Vector Vector::Difference(Vector v)
{
    return Vector(x-v.GetX(),y-v.GetY(),z-v.GetZ());
}

float Vector::Distance(Vector v)
{
    Vector a = Difference(v);
    return a.length();
}
//End Vector Class


//Box Class
Box::Box(Vector position, Vector sizeofBox) : pos(position), diag(sizeofBox){}
float Box::GetXmin()
{
    return pos.GetX();
}
float Box::GetYmin()
{
    return pos.GetY();
}
float Box::GetZmin()
{
    return pos.GetZ();
}
float Box::GetXmax()
{
    return pos.GetX()+diag.GetX();
}
float Box::GetYmax()
{
    return pos.GetY()+diag.GetY();
}
float Box::GetZmax()
{
    return pos.GetZ()+diag.GetZ();
}

void Box::SetBox(Vector position, Vector diagonal)
{
    pos = position;
    diag = diagonal;
}

//End Box Class

//Bat Class
Bat::Bat(Vector position, float s, Box area)
{
    pos = position;
    size = s;
    speed = 10.0;
    xmax = area.GetXmax();
    ymax = area.GetYmax();
    dir = Vector(0,0,0);
}
void Bat::SetZ(float zvalue)
{
    pos.SetZ(zvalue);
}
void Bat::SetDirection(Vector direction)
{
    dir = direction;
}
void Bat::AddDirection(Vector direction)
{
    dir.Add(direction);
}
void Bat::SetRange(Box range)
{
    xmax = range.GetXmax();
    ymax = range.GetYmax();
}
float Bat::GetX()
{
    return pos.GetX();
}
float Bat::GetY()
{
    return pos.GetY();
}
float Bat::GetZ()
{
    return pos.GetZ();
}
float Bat::GetSize()
{
    return size;
}

void Bat::move()
{
    if (dir.length())
    {
        dir.Normalize();
        dir.Scale(speed);
        if (abs(pos.GetX()+dir.GetX()) < xmax-size/2 || abs(pos.GetY()+dir.GetY()) < ymax-size/2)
        {
            if (abs(pos.GetX()+dir.GetX()) > xmax-size/2)
            {
                dir.SetX(0);
                if (dir.GetY())dir.Normalize();
                dir.Scale(speed);
            }
            if (abs(pos.GetY()+dir.GetY()) > ymax-size/2)
            {
                dir.SetY(0);
                if (dir.GetX())dir.Normalize();
                dir.Scale(speed);
            }
            pos.Add(dir);
        }
    }
}
//End Bat Class

//Ball Class

Ball::Ball(Vector position, Vector direction, float radius) : pos(position), dir(direction), rad(radius){}

float Ball::GetX()
{
    return pos.GetX();
}
float Ball::GetY()
{
    return pos.GetY();
}
float Ball::GetZ()
{
    return pos.GetZ();
}
float Ball::GetNextX()
{
    return pos.GetX()+dir.GetX();
}
float Ball::GetNextY()
{
    return pos.GetY()+dir.GetY();
}
float Ball::GetNextZ()
{
    return pos.GetZ()+dir.GetZ();
}
float Ball::GetRadius()
{
    return rad;
}
char Ball::Move(Box room)
{
    char c = Colid(abs(room.GetXmax()),abs(room.GetYmax()),abs(room.GetZmax()));
    pos.Add(dir);
    return c;
}

char Ball::Colid(float x, float y, float z)
{
    char c = '0';
    if (x < abs(GetNextX())+rad)
    {
        dir.SetX(-dir.GetX());
        //b=true;
    }
    if (z+200 < abs(GetNextZ())+rad)
    {
        if(pos.GetZ()<0)
        {
            c='1';
            Reset(0);
        }
        else
        {
            c='2';
            Reset(1);
        }

    }
    if (y < abs(GetNextY())+rad)
    {
        dir.SetY(-dir.GetY());
        //b= true;
    }
    return c;
}

bool Ball::Colid(Bat b)
{
    bool r = false;
    //still in work
    if(abs(b.GetZ()-GetNextZ()) < rad && (GetNextX() > b.GetX()-b.GetSize()/2-rad/2 && GetNextX() < b.GetX()+b.GetSize()/2+rad/2) && (GetNextY() > b.GetY()-b.GetSize()/2-rad/2 && GetNextY() < b.GetY()+b.GetSize()/2+rad/2)){
        dir.SetZ(-dir.GetZ());
    }
    return r;
}
void Ball::Reset(bool d){
    pos = Vector(0,0,0);
    dir = Vector(ofRandom(-5,5),ofRandom(-5,5),ofRandom(5,8)*(d ? (-1) : 1));
    dir.Normalize();
    dir.Scale(5);
}
//End Ball Class
