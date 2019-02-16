//
//  LeftLeg.cpp
//  AT-ST_OOP
//
//  Created by Armando Hernandez on 2/14/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//

#include "LeftLeg.hpp"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

extern GLfloat theta[];

LeftLeg::LeftLeg(){
    upperLegRadius = 0.5;
    mediumLegRadius = 0.5;
    loweLegRadius = 0.5;
    
    upperLegHeight = 3.0;
    mediumLegHeight = 7.0;
    loweLegHeight = 3.0;
    
    feetWidth = 2.0;
    feetLenght = 3.0;
    feetHeight = 1.0;

    bodyRadius = 3.0;
    
    lll = gluNewQuadric();
    gluQuadricDrawStyle(lll, GLU_FILL);
    lul = gluNewQuadric();
    gluQuadricDrawStyle(lul, GLU_FILL);
    lf = gluNewQuadric();
    gluQuadricDrawStyle(lf, GLU_FILL);
    lwll = gluNewQuadric();
    gluQuadricDrawStyle(lwll, GLU_FILL);
}

LeftLeg::LeftLeg(float _upperLegRadius, float _mediumLegRadius, float _loweLegRadius, float _upperLegHeight, float _mediumLegHeight, float _loweLegHeight, float _feetWidth, float _feetLenght, float _bodyRadius, float _feetHeight){
    
    upperLegRadius = _upperLegRadius;
    mediumLegRadius = _mediumLegRadius;
    loweLegRadius = _loweLegRadius;
    
    upperLegHeight = _upperLegHeight;
    mediumLegHeight = _mediumLegHeight;
    loweLegHeight = _loweLegHeight;
    
    feetWidth = _feetWidth;
    feetLenght = _feetLenght;
    feetHeight = _feetHeight;
    
    bodyRadius = _bodyRadius;
}

LeftLeg::~LeftLeg()
{
}

void LeftLeg::draw()
{
    glPushMatrix();
    {
        //left upper leg
        glTranslatef(-(bodyRadius + upperLegRadius), 0.1 * upperLegHeight, 0);
        glRotatef(theta[7], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(lul, upperLegRadius, upperLegRadius, upperLegHeight, 10, 10);
        }
        glPopMatrix();
        
        //left medium leg
        glTranslatef(0, upperLegHeight, 0);
        glRotatef(theta[8], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(lll, mediumLegRadius, mediumLegRadius, mediumLegHeight, 10, 10);
        }
        glPopMatrix();
        
        //left lower leg
        glTranslatef(0, upperLegHeight + 4 * feetHeight, 0);
        glRotatef(theta[13], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(lwll, loweLegRadius, loweLegRadius, loweLegHeight, 10, 10);
        }
        glPopMatrix();
        
        //left foot
        glTranslatef(0,3*feetHeight,1);
        glRotatef(theta[11],1,0,0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(lf, feetLenght, feetWidth, feetHeight, 10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
