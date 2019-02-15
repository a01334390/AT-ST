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
#include "limb.hpp"

extern GLUquadricObj *lua;  

Limb::Limb() {
    lua = gluNewQuadric();
	gluQuadricDrawStyle(lua, GLU_FILL);
}

Limb::~Limb(){

}

void Limb::draw(float length,float width,float height){
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-(3.0 + 0.5), 0.2 * 5.0, 0);
    gluCylinder(lua,length, width, height, 10, 10);
}

void Limb::update(GLfloat angle){
    glRotatef(angle, 1, 0, 0);
}