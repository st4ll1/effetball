#include "curveballDrawing.h"

void Drawing::box(Box b)
{
    glBegin(GL_QUADS);

    //right wall box(inside)
    glColor3f(0.8, 0.6, 0.4);
    glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmax());
    glColor3f(0.5, 0.9, 0.5);
    glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmax());
    glColor3f(0.95, 0.95, 0.95);
    glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmin());
    glColor3f(.85, 0.85, 0.85);
    glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmin());
    //left wall box(inside)
    glColor3f(0.5, 0.9, 0.4);
    glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmax());
    glColor3f(0.5, 0.9, 0.4);
    glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmax());
    glColor3f(0.95, 0.95, 0.95);
    glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmin());
    glColor3f(.85, 0.85, 0.85);
    glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmin());
    //floor box(inside)
    glColor3f(.9, 0.9, 0.9);
    glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmin());
    glColor3f(0.5, 0.9, 0.5);
    glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmax());
    glColor3f(0.5, 0.9, 0.4);
    glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmax());
    glColor3f(.85, 0.85, 0.85);
    glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmin());
    //roof box(inside)
    glColor3f(.9, 0.9, 0.9);
    glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmin());
    glColor3f(0.5, 0.9, 0.4);
    glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmax());
    glColor3f(0.8, 0.6, 0.4);
    glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmax());
    glColor3f(.85, 0.85, 0.85);
    glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmin());
    /*
    //back wall box(inside)
    glColor3f(0.5, 0.3, 0.5);       glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmax());
    glColor3f(0.5, 0.3, 0.4);       glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmax());
    glColor3f(0.5, 0.3, 0.4);       glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmax());
    glColor3f(0.5, 0.3, 0.4);       glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmax());
    */

    glEnd();
}

void Drawing::bat(Bat b){
    glPushMatrix();
    glTranslatef(b.GetX(), b.GetY(), b.GetZ());
    glScalef(1.0,1.0,0.05);
    glColor4f(0.85,0.30,0.30,0.6);
    glutSolidCube(b.GetSize());
    glPopMatrix();
}

void Drawing::batShadow(Bat b,Box cbox)
{
    //oben
    float alpha = ofMap(b.GetY(), cbox.GetYmax(), cbox.GetYmin(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(b.GetX(), cbox.GetYmin(), b.GetZ());
        glRotatef(90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha);
        ofRect(-b.GetSize()/2,2.5,b.GetSize(),5);
        glPopMatrix();
    }
    //unten
    alpha = ofMap(b.GetY(), cbox.GetYmin(), cbox.GetYmax(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(b.GetX(), cbox.GetYmax()-1, b.GetZ());
        glRotatef(-90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha);
        ofRect(-b.GetSize()/2,2.5,b.GetSize(),5);
        glPopMatrix();
    }
    //rechts
    alpha = ofMap(b.GetX(), cbox.GetXmin(), cbox.GetXmax(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(cbox.GetXmax(), b.GetY(), b.GetZ());
        glRotatef(-90,0,0,1);
        glRotatef(-90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha);
        ofRect(-b.GetSize()/2,2.5,b.GetSize(),5);
        glPopMatrix();
    }
    //links
    alpha = ofMap(b.GetX(), cbox.GetXmax(), cbox.GetXmin(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(cbox.GetXmin()+1, b.GetY(), b.GetZ());
        glRotatef(-90,0,0,1);
        glRotatef(90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha);
        ofRect(-b.GetSize()/2,2.5,b.GetSize(),5);
        glPopMatrix();
    }
}

void Drawing::ball(Ball b){
    glPushMatrix();
    glTranslatef(b.GetX(), b.GetY(), b.GetZ());
    glutSolidSphere(b.GetRadius(), 15, 15);
    glPopMatrix();
}

void Drawing::ballShadow(Ball b, Box cbox)
{
    //oben
    float alpha = ofMap(b.GetY(), cbox.GetYmax(), cbox.GetYmin(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(b.GetX(), cbox.GetYmin()+1, b.GetZ());
        glRotatef(90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha);
        ofCircle(0,0, b.GetRadius());
        glPopMatrix();
    }
    //unten
    alpha = ofMap(b.GetY(), cbox.GetYmin(), cbox.GetYmax(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(b.GetX(), cbox.GetYmax()-1, b.GetZ());
        glRotatef(-90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha);
        ofCircle(0,0, b.GetRadius());
        glPopMatrix();
    }
    //rechts
    alpha = ofMap(b.GetX(), cbox.GetXmin(), cbox.GetXmax(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(cbox.GetXmax()-1, b.GetY(), b.GetZ());
        glRotatef(-90,0,0,1);
        glRotatef(-90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha);
        ofCircle(0,0, b.GetRadius());
        glPopMatrix();
    }
    //links
    alpha = ofMap(b.GetX(), cbox.GetXmax(), cbox.GetXmin(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(cbox.GetXmin()+1, b.GetY(), b.GetZ());
        glRotatef(-90,0,0,1);
        glRotatef(90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha);
        ofCircle(0,0, b.GetRadius());
        glPopMatrix();
    }
}
