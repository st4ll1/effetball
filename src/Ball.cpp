/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#include "Ball.h"

Ball::Ball(Vector position, Vector direction, float radius, float ballspeed) :
    pos(position),
    startpos(position),
    dir(direction),
    rad(radius),
    speed(ballspeed),
    startspeed(ballspeed) {}

void Ball::turnX(Vector vector, float friction)
{
    Vector rot(0,dir.y-vector.y,dir.z-vector.z);
    float ve = rot.length()*friction/5;
    rotation = Quaternion(rot.cross(Vector(ofSign(dir.x),0,0)),ve) * rotation;
    dir.x *= -1;
}
void Ball::turnY(Vector vector, float friction)
{
    Vector rot(dir.x-vector.x,0,dir.z-vector.z);
    float ve = rot.length()*friction/5;
    rotation = Quaternion(rot.cross(Vector(0,ofSign(dir.y),0)),ve) * rotation;
    dir.y *= -1;
}
void Ball::turnZ(Vector vector, float friction)
{
    Vector rot(dir.x-vector.x,dir.y-vector.y,0);
    float ve = rot.length()*friction/5;
    rotation = Quaternion(rot.cross(Vector(0,0,ofSign(dir.z))),ve) * rotation;
    dir.z *= -1;
}
float Ball::GetNextX() const
{
    return pos.x+dir.x;
}
float Ball::GetSpeed(){
    return speed;
}
float Ball::GetNextY() const
{
    return pos.y+dir.y;
}
float Ball::GetNextZ() const
{
    return pos.z+dir.z;
}
Vector Ball::GetDirection()
{
    return dir;
}
float Ball::GetRadius() const
{
    return rad;
}

void Ball::Move()
{
    currentRotation = rotation * currentRotation;
    // rotate the direction vector caused by the rotation
    dir.rotate(rotation.angle()/100,Vector(rotation.i,rotation.j,rotation.k));
    pos.Add(dir);
}

void Ball::Reset(bool direction)
{
    pos = startpos;
    dir = Vector(ofRandom(-0.3f,0.3f),(direction ? (-1.0f): 1.0f),ofRandom(-0.3f, 0.3f));
    currentRotation = rotation = Quaternion();
    dir.Normalize();
    dir.Scale(startspeed);
}

void Ball::print()
{
    printf("koord:%f,%f,%f, r:%f, \nrot:%f,%f,%f,%f\n", pos.x,pos.y,pos.z,rad, rotation.i,rotation.j,rotation.k,rotation.r);
}
