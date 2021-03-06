//
//  Guns.hpp
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


class Guns
{
public:
    Guns();    // constructor
    Guns(float _bodyRadius, float _bodyHeight, float _upperGunHeight, float _upperGunRadius, float _middleGunHeight, float _middleGunRadius);
    ~Guns();    // destructor
    
    float bodyRadius, bodyHeight;
    float upperGunHeight, upperGunRadius;
    float middleGunHeight, middleGunRadius;
    GLUquadricObj *lua;
    GLUquadricObj *lla;
    GLUquadricObj *rua;
    
    void draw();
    void update();
};
