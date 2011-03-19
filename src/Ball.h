/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#ifndef EFFETBALLBALL_H_INCLUDE
#define EFFETBALLBALL_H_INCLUDE

#include "Vector.h"
#include "Field.h"
#include "Bat.h"
#include "Quaternionen.h"
#include "ofMain.h"

class Ball
{

public:
    Ball(Vector position, Vector direction, float radius, float startspeed);
    void turnX(Vector v, float friction);
    void turnY(Vector v, float friction);
    void turnZ(Vector v, float friction);
    float GetNextX() const;
    float GetNextY() const;
    float GetNextZ() const;
    float GetRadius() const;
    void Move();
    void Reset(bool);
    float GetSpeed();
    Vector GetDirection();
    Vector pos;
    Quaternion currentRotation;
    void print();

private:
    Vector startpos;

    Vector dir;
    Quaternion rotation;
    float rad;
    float speed;
    float startspeed;
};

#endif
