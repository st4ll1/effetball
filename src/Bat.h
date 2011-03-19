/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#ifndef EFFETBALLBAT_H_INCLUDE
#define EFFETBALLBAT_H_INCLUDE

#include "Vector.h"
#include "Field.h"

class Bat
{
public:
    Bat(Vector position, float size, float maxSpeed);
    void SetY(float y);
    void SetDirection(Vector);
    void AddDirection(Vector);
    void SetRange(Field range);
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    Vector GetSize() const;
    Vector GetDirection() const;
    void Move();
    void Accelerate();
    void Slowdown();

    Vector pos;

private:
    Vector dir;
    Vector size;
    float speed;
    float maximumSpeed;
};

#endif
