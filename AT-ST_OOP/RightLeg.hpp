//
//  RightLeg.hpp
//  AT-ST_OOP
//
//  Created by Armando Hernandez on 2/14/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//
#pragma once
#ifdef __APPLE__
// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
// Import this whole code into a new C++ file (main.cpp, for example). Then run.
// Reference: https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Mac
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif
#ifdef _WIN32
// For VS on Windows only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
// Run
#include "freeglut.h"
#endif
#ifdef __unix__
// For Linux users only: g++ CG_Demo.cpp -lglut -lGL -o CG_Demo
// ./CG_Demo
// Reference: https://www.linuxjournal.com/content/introduction-opengl-programming
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"


class RightLeg
{
public:
    RightLeg();    // constructor
    RightLeg(float _upperLegRadius, float _mediumLegRadius, float _loweLegRadius, float _upperLegHeight, float _mediumLegHeight, float _loweLegHeight, float _feetWidth, float _feetLenght, float _bodyRadius, float _feetHeight);
    ~RightLeg();    // destructor
    
    float upperLegRadius, mediumLegRadius, loweLegRadius;
    float upperLegHeight, mediumLegHeight, loweLegHeight;
    float feetWidth, feetLenght, feetHeight;
    float bodyRadius;
    
    GLUquadricObj *rll;
    GLUquadricObj *rul;
    GLUquadricObj *rf;
    GLUquadricObj *lwrl;
    
    void draw();
    void update();
};
