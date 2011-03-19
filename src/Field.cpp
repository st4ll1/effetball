/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#include "Field.h"

Field::Field(Vector position, Vector sizeofField) : pos(position), size(sizeofField) {}
float Field::GetXmin() const
{
    return pos.x;
}
float Field::GetYmin() const
{
    return pos.y;
}
float Field::GetZmin() const
{
    return pos.z;
}
float Field::GetXmax() const
{
    return pos.x+size.x;
}
float Field::GetYmax() const
{
    return pos.y+size.y;
}
float Field::GetZmax() const
{
    return pos.z+size.z;
}

Vector Field::GetMiddle()
{
    return (pos + size)/2;
}

void Field::SetField(Vector position, Vector size)
{
    pos = position;
    this->size = size;
}
