//
//  Torso.cpp
//  AT-ST_OOP
//
//  Created by Armando Hernandez on 2/14/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//

#include "Torso.hpp"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

extern GLfloat theta[];

Torso::Torso()
{
    bodyRadius = 3.0;
    bodyHeight = 5.0;
    
    t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
}

Torso::Torso(float _bodyRadius, float _bodyHeight){
    bodyRadius = _bodyRadius;
    bodyHeight = _bodyHeight;
}


Torso::~Torso()
{
}

void Torso::draw()
{
    glColor3f(0, 0, 0);
    glRotatef(theta[0], 0, 1, 0);
    glPushMatrix();
    {
        glRotatef(-90, 1, 0, 0);
        gluCylinder(t, bodyRadius, bodyRadius, bodyHeight, 10, 10);
    }
    glPopMatrix();}
