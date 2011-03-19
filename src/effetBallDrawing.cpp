/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#include "effetBallDrawing.h"

void drawField(Field& b)
{
    glBegin(GL_QUADS);
    //right wall(inside)
    glColor3f(0.8, 0.6, 0.4);
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmax());
    glColor3f(0.5, 0.9, 0.5);
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmax());
    glColor3f(0.95, 0.95, 0.95);
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmin());
    glColor3f(.85, 0.85, 0.85);
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmin());
    //left wall(inside)
    glColor3f(0.5, 0.9, 0.4);
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmax());
    glColor3f(0.5, 0.9, 0.4);
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmax());
    glColor3f(0.95, 0.95, 0.95);
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmin());
    glColor3f(.85, 0.85, 0.85);
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmin());
    //top wall(inside)
    glColor3f(.9, 0.9, 0.9);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmax());
    glColor3f(0.5, 0.9, 0.5);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmax());
    glColor3f(0.5, 0.9, 0.4);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmax());
    glColor3f(.85, 0.85, 0.85);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmax());
    //bottom wall(inside)
    glColor3f(.9, 0.9, 0.9);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(b.GetXmin(), b.GetYmax(), b.GetZmin());
    glColor3f(0.5, 0.9, 0.4);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(b.GetXmin(), b.GetYmin(), b.GetZmin());
    glColor3f(0.8, 0.6, 0.4);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(b.GetXmax(), b.GetYmin(), b.GetZmin());
    glColor3f(.85, 0.85, 0.85);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(b.GetXmax(), b.GetYmax(), b.GetZmin());

    glEnd();
}

void drawBat(const Bat& b,float r, float g, float bl)
{
    int borderPercentage = 10;
    Vector size = b.GetSize();
    glPushMatrix();
        glTranslatef(b.pos.x+size.x/2, b.pos.y+size.y/2, b.pos.z+size.z/2);
        glPushMatrix();
            glColor3f(r,g,bl);
            glTranslatef(0,0,size.z/2*(1-1/borderPercentage));
            glScalef(size.x,size.y,size.z/borderPercentage);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glColor3f(r,g,bl);
            glTranslatef(0,0,-size.z/2*(1-1/borderPercentage));
            glScalef(size.x,size.y,size.z/borderPercentage);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glColor3f(r,g,bl);
            glTranslatef(size.z/2*(1-1/borderPercentage),0,0);
            glScalef(size.x/borderPercentage,size.y,size.z);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glColor3f(r,g,bl);
            glTranslatef(-size.z/2*(1-1/borderPercentage),0,0);
            glScalef(size.x/borderPercentage,size.y,size.z);
            glutSolidCube(1);
        glPopMatrix();
        glColor4f(r,g,bl,0.3f);
        glScalef(size.x,size.y,size.z);
        glutSolidCube(1);
    glPopMatrix();
}

void drawBatShadow(const Bat& bat, const Field& cField, int mode)
{
    //bottom
    if(mode>0){
        float alpha = ofMap(bat.GetZ(), cField.GetZmax(), cField.GetZmin(), 0, 1);
        Vector size = bat.GetSize();
        if (alpha>0)
        {
            glPushMatrix();
            glTranslatef(bat.GetX()+size.x/2, bat.GetY(), cField.GetZmin()+10);
            glColor4f(0, 0, 0, alpha);
            glScalef(size.x,size.y,10);
            glutSolidCube(1);
            glPopMatrix();
        }
        if(mode>1){
            alpha = ofMap(bat.GetZ(), cField.GetZmax(), cField.GetZmin(), 1, 0);
            if (alpha>0)
            {
                glPushMatrix();
                glTranslatef(bat.GetX()+size.x/2, bat.GetY(), cField.GetZmax()-10);
                glColor4f(0, 0, 0, alpha);
                glScalef(size.x,size.y,10);
                glutSolidCube(1);
                glPopMatrix();
            }
            alpha = ofMap(bat.GetX(), cField.GetXmax(), cField.GetXmin(), 1, 0);
            if (alpha>0)
            {
                glPushMatrix();
                glTranslatef(cField.GetXmax()-10, bat.GetY(), bat.GetZ()+size.z/2);
                glColor4f(0, 0, 0, alpha);
                glScalef(10,size.y,size.z);
                glutSolidCube(1);
                glPopMatrix();
            }
            alpha = ofMap(bat.GetX(), cField.GetXmax(), cField.GetXmin(), 0, 1);
            if (alpha>0)
            {
                glPushMatrix();
                glTranslatef(cField.GetXmin()+10, bat.GetY(), bat.GetZ()+size.z/2);
                glColor4f(0, 0, 0, alpha);
                glScalef(10,size.y,size.z);
                glutSolidCube(1);
                glPopMatrix();
            }
        }
    }
}

void drawBall(const Ball& ball)
{
    glPushMatrix();
    glTranslatef(ball.pos.x, ball.pos.y, ball.pos.z);
    //rotation
    Quaternion q = ball.currentRotation;
    glRotatef(q.angle(),q.i,q.j,q.k);
    drawSphere(ball.GetRadius());
    glPopMatrix();
}

void drawSphere(float radius)
{
    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, radius, 100, 100);
    gluDeleteQuadric(sphere);
}

void drawBallShadow(const Ball& ball, const Field& cField, int mode)
{
    //bottom
    float alpha = ofMap(ball.pos.z, cField.GetZmax(), cField.GetZmin(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(ball.pos.x, ball.pos.y, cField.GetZmin()+5);
        glColor4f(0, 0, 0, alpha);
        glScalef(ball.GetRadius(),ball.GetRadius(),10);
        drawSphere(1.0f);
        glPopMatrix();
    }
    //top
    alpha = ofMap(ball.pos.z, cField.GetZmin(), cField.GetZmax(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(ball.pos.x, ball.pos.y, cField.GetZmax()-5);
        glColor4f(0, 0, 0, alpha);
        glScalef(ball.GetRadius(),ball.GetRadius(),10);
        drawSphere(1.0f);
        glPopMatrix();
    }
    //left
    alpha = ofMap(ball.pos.x, cField.GetXmax(), cField.GetXmin(), 0, 1);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(cField.GetXmin()+5, ball.pos.y, ball.pos.z);
        glColor4f(0, 0, 0, alpha);
        glScalef(10,ball.GetRadius(),ball.GetRadius());
        drawSphere(1.0f);
        glPopMatrix();
    }
    //right
    alpha = ofMap(ball.pos.x, cField.GetXmax(), cField.GetXmin(), 1, 0);
    if (alpha>0)
    {
        glPushMatrix();
        glTranslatef(cField.GetXmax()-5, ball.pos.y, ball.pos.z);
        glColor4f(0, 0, 0, alpha);
        glScalef(10,ball.GetRadius(),ball.GetRadius());
        drawSphere(1.0f);
        glPopMatrix();
    }
}

void drawDepthLine(const Field& cField, float y, int mode, float r, float g, float b){
    float width = cField.GetXmax()-cField.GetXmin();
    if(mode){
        //bottom
        glPushMatrix();
        glTranslatef(cField.GetXmin()+width/2, y, cField.GetZmin()+5);
        glColor3f(r, g, b);
        glScalef(width,20,10);
        glutSolidCube(1);
        glPopMatrix();
        //top
        glPushMatrix();
        glTranslatef(cField.GetXmin()+width/2, y, cField.GetZmax()-5);
        glColor3f(r, g, b);
        glScalef(width,20,10);
        glutSolidCube(1);
        glPopMatrix();
        float height = cField.GetZmax()-cField.GetZmin();
        //left
        glPushMatrix();
        glTranslatef(cField.GetXmin()+5, y, cField.GetZmin()+height/2);
        glColor3f(r, g, b);
        glScalef(10,20,height);
        glutSolidCube(1);
        glPopMatrix();
        //right
        glPushMatrix();
        glTranslatef(cField.GetXmax()-5, y, cField.GetZmin()+height/2);
        glColor3f(r, g, b);
        glScalef(10,20,height);
        glutSolidCube(1);
        glPopMatrix();
    }
}
