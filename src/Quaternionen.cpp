/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#include "Quaternionen.h"

Quaternion::Quaternion(float r, float i, float j, float k)
{
    this->r = r;
    this->i = i;
    this->j = j;
    this->k = k;
}

Quaternion::Quaternion(Vector axis, float angle)
{
    axis.Normalize();
    angle = angle * PI / 180;
    r = cos(angle);
    i = sin(angle)*axis.x;
    j = sin(angle)*axis.y;
    k = sin(angle)*axis.z;
}

float Quaternion::angle()
{
    return (2.0 * atan2(sqrt(i*i+j*j+k*k),r))* 180 / PI;
}

Quaternion Quaternion::operator+ (const Quaternion& o)
{
    return Quaternion(
               r + o.r,
               i + o.i,
               j + o.j,
               k + o.k
           );
}

Quaternion Quaternion::operator* (const Quaternion& o)
{
    return Quaternion(
               r * o.r - i * o.i - j * o.j - k * o.k,
               r * o.i + i * o.r + j * o.k - k * o.j,
               r * o.j + j * o.r + k * o.i - i * o.k,
               r * o.k + k * o.r + i * o.j - j * o.i
           );
}

Quaternion Quaternion::conj()const
{
    return Quaternion(r, -i, -j, -k);
}

void Quaternion::print()
{
    printf("r: %f, i: %f, j: %f, k: %f \n", r, i,j,k);
}


