/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#ifndef CURVEBALLDRAWING_H_INCLUDED
#define CURVEBALLDRAWING_H_INCLUDED

#include "Field.h"
#include "Ball.h"
#include "Bat.h"

void drawField(Field& b);
void drawBall(const Ball& b);
void drawSphere(float radius);
void drawBat(const Bat& b, float r, float g, float bl);
void drawBallShadow(const Ball& ball, const Field& cField , int mode);
void drawBatShadow(const Bat& b, const Field& cField, int mode);
void drawDepthLine(const Field& cField, float y, int mode, float r, float g , float b);

#endif // CURVEBALLDRAWING_H_INCLUDED
