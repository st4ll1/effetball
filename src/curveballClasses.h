#ifndef CURVEBALLCLASSES_H_INCLUDED
#define CURVEBALLCLASSES_H_INCLUDED


#include "ofMain.h"
class Vector{
    public:
    Vector(float xvalue=0, float yvalue=0, float zvalue=0);
    //get the koordinates
    float GetX();
    float GetY();
    float GetZ();
    //set the koordinates
    void SetX(float xvalue);
    void SetY(float yvalue);
    void SetZ(float zvalue);
    //reset vector (0,0,0)
    void SetNull();
    //addition to the vector
    bool Add(float xvalue=0, float yvalue=0, float zvalue=0);
    bool Add(Vector added);

    float length();
    void Normalize();
    void Scale(float);
    Vector Difference(Vector);
    float Distance(Vector);
  /* Vector Diff(Vector d){
        Vector vec;
        vec.SetX(d.GetX());
        vec.SetY(d.GetY());
        vec.SetZ(d.GetZ());
        return true;
    }*/

    private:

    float x;
    float y;
    float z;
};

class Box{
    public:
    Box(Vector position, Vector sizeofBox);
    float GetXmin();
    float GetYmin();
    float GetZmin();
    float GetXmax();
    float GetYmax();
    float GetZmax();

    void SetBox(Vector position, Vector diagonal);

    private:

    Vector pos;
    Vector diag;

};

class Bat{
    public:
    Bat(Vector position, float s, Box area);
    void SetZ(float zvalue);
    void SetDirection(Vector);
    void AddDirection(Vector);
    void SetRange(Box range);
    float GetX();
    float GetY();
    float GetZ();
    float GetSize();
    void move();

    private:
    Vector pos;
    Vector dir;
    float size;
    float speed;
    float xmax;
    float ymax;
};

class Ball{

    public:

    Ball(Vector position, Vector direction, float radius);
    float GetX();
    float GetY();
    float GetZ();
    float GetNextX();
    float GetNextY();
    float GetNextZ();
    float GetRadius();
    char Move(Box room);
    char Colid(float x, float y, float z);
    bool Colid(Bat);
    void Reset(bool);

    private:
    Vector pos;
    Vector dir;
    float rad;
};

#endif // CURVEBALLCLASSES_H_INCLUDED
