/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#ifndef QUATERNION_H_INCLUDE
#define QUATERNION_H_INCLUDE



#include <cstdio>
#include "Vector.h"
#include <cmath>

class Quaternion
{

public:
    float r;
    float i;
    float j;
    float k;

    Quaternion(float r=1, float i=0, float j=0, float k=0);
    Quaternion(Vector axis, float angle);

    float angle();

    Quaternion operator+ (const Quaternion& o);
    Quaternion operator* (const Quaternion& o);

    Quaternion conj()const;

    void print();
};


#endif
