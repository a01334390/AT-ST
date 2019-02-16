//
//  RightLeg.cpp
//  AT-ST_OOP
//
//  Created by Armando Hernandez on 2/14/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//

#include "RightLeg.hpp"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"


extern GLfloat theta[];

RightLeg::RightLeg()
{
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
    
    rll = gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_FILL);
    
    rul = gluNewQuadric();
    gluQuadricDrawStyle(rul, GLU_FILL);
    
    lwrl = gluNewQuadric();
    gluQuadricDrawStyle(lwrl, GLU_FILL);
    
    rf = gluNewQuadric();
    gluQuadricDrawStyle(rf, GLU_FILL);
}

RightLeg::RightLeg(float _upperLegRadius, float _mediumLegRadius, float _loweLegRadius, float _upperLegHeight, float _mediumLegHeight, float _loweLegHeight, float _feetWidth, float _feetLenght, float _bodyRadius, float _feetHeight){
    
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

RightLeg::~RightLeg()
{
}
void RightLeg::draw()
{
    glPushMatrix();
    {
        //right upper leg
        glTranslatef(bodyRadius + upperLegRadius, 0.1 * upperLegHeight, 0);
        glRotatef(theta[9], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(rul, upperLegRadius, upperLegRadius, upperLegHeight, 10, 10);
        }
        glPopMatrix();
        
        //right medium leg
        glTranslatef(0, upperLegHeight, 0);
        glRotatef(theta[10], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(rll, mediumLegRadius, mediumLegRadius, mediumLegHeight, 10, 10);
        }
        glPopMatrix();
        
        //right lower leg
        glTranslatef(0, upperLegHeight + 4*feetHeight, 0);
        glRotatef(theta[14], 1, 0, 0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(lwrl, loweLegRadius, loweLegRadius, loweLegHeight, 10, 10);
        }
        glPopMatrix();
        
        //roght foot
        glTranslatef(0,3*feetHeight,1);
        glRotatef(theta[12],1,0,0);
        glPushMatrix();
        {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(rf, feetLenght, feetWidth, feetHeight, 10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
