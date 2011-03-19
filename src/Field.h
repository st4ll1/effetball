/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#ifndef EFFETBALLFIELD_H_INCLUDE
#define EFFETBALLFIELD_H_INCLUDE

#include "Vector.h"

class Field
{
public:
    Field(Vector position, Vector sizeofField);
    float GetXmin() const;
    float GetYmin() const;
    float GetZmin() const;
    float GetXmax() const;
    float GetYmax() const;
    float GetZmax() const;
    Vector GetMiddle();

    void SetField(Vector position, Vector diagonal);

private:

    Vector pos;
    Vector size;
};


#endif
