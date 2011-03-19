/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#include "Bat.h"

Bat::Bat(Vector position, float size, float maxSpeed)
{
    pos = position;
    this->size = Vector(size, 5, size);
    this->speed = 0.0f;
    this->maximumSpeed = maxSpeed;
    dir = Vector(0,0,0);
}
void Bat::SetY(float y)
{
    pos.y = y;
}
void Bat::SetDirection(Vector direction)
{
    dir = direction;
}
void Bat::AddDirection(Vector direction)
{
    dir.Add(direction);
}
Vector Bat::GetDirection() const{
    return dir;
}

float Bat::GetX() const
{
    return pos.x;
}
float Bat::GetY() const
{
    return pos.y;
}
float Bat::GetZ() const
{
    return pos.z;
}

Vector Bat::GetSize() const
{
    return size;
}

void Bat::Slowdown(){
    speed -= maximumSpeed/200;
    if(speed < 0) speed = 0;
}

void Bat::Accelerate(){
    if(speed < maximumSpeed/2) speed = maximumSpeed/2 + maximumSpeed/20;
    else speed += maximumSpeed/20;
    if(speed > maximumSpeed) speed = maximumSpeed;
}

void Bat::Move()
{
    if(speed > 0){
        dir.Normalize();
        dir.Scale(speed);
		pos.Add(dir);
    }
    else
    {
        SetDirection(Vector());
    }
}
