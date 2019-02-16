//
//  Guns.cpp
//  AT-ST_OOP
//
//  Created by Armando Hernandez on 2/14/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//
#include "Guns.hpp"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

GLUquadricObj *lua, *lla, *rua;

extern GLfloat theta[];

Guns::Guns()
{
    bodyRadius = 3.0;
    bodyHeight = 5.0;
    upperGunHeight = 5.0;
    upperGunRadius = 0.5;
    middleGunHeight = 4.0;
    middleGunRadius = 1.0;
    
    lua = gluNewQuadric();
    gluQuadricDrawStyle(lua, GLU_FILL);
    
    rua = gluNewQuadric();
    gluQuadricDrawStyle(rua, GLU_FILL);
    
    lla = gluNewQuadric();
    gluQuadricDrawStyle(lla, GLU_FILL);
}

Guns::Guns(float _bodyRadius, float _bodyHeight, float _upperGunHeight, float _upperGunRadius, float _middleGunHeight, float _middleGunRadius){
    
    bodyRadius = _bodyRadius;
    bodyHeight = _bodyHeight;
    upperGunHeight = _upperGunHeight;
    upperGunRadius = _upperGunRadius;
    middleGunHeight = _middleGunHeight;
    middleGunRadius = _middleGunRadius;
    
}

Guns::~Guns()
{
}

void Guns::draw()
{
    /* Connect left gun to the body */
    glPushMatrix();
    {
        glTranslatef(-(bodyRadius + upperGunRadius), 0.2 * bodyHeight, 0);
        glRotatef(theta[3], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(lua, upperGunRadius, upperGunRadius, upperGunHeight, 10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
    
    /* Connect middle gun to the body */
    glPushMatrix();
    {
        glTranslatef((bodyRadius / 2 - 1.5 * middleGunRadius), 0.2 * bodyHeight, 0);
        glRotatef(theta[3], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(lla, middleGunRadius, middleGunRadius, middleGunRadius, 10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
    
    /* Connect right gun to the body */
    glPushMatrix();
    {
        glTranslatef(bodyRadius + upperGunRadius, 0.2 * bodyHeight, 0);
        glRotatef(theta[3], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(rua, upperGunRadius, upperGunRadius, upperGunHeight, 10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
