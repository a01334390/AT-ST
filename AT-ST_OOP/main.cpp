/*
 * Fernando Martin Garcia Del Angel
 * A01334390
 * Armando Hernandez Vargas
 * A01334836
 * 
 */

// Please don't change lines 9-31 (It helps me to grade)
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

#include <stdio.h>
#include <stdlib.h>
// #include <iostream>
#include <string.h>
#include <math.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

//our clases
#include "LeftLeg.hpp"
LeftLeg* leftLeg;
#include "RightLeg.hpp"
RightLeg* rightLeg;
#include "Torso.hpp"
Torso* torso;
#include "Guns.hpp"
Guns* guns;

GLUquadricObj *h, *rla;

/* Initial joint angles */
typedef float point[3];

static GLfloat keyframes[10][15] = {
    //Ida D1 regreso I1
    {-60, 0, 0, 90, -90, 0, 180, 231, -88, 280, -93, 225, 209, -8, -48},
    //Ida D2 regreso I2
    {-60, 0, 0, 90, -90, 0, 180, 241, -88, 284, -113, 233, 216, -26, -33}, 
    //Ida D3 regreso I3
    {-60, 0, 0, 90, -90, 0, 180, 255, -96, 268, -124, 221, 216, -20, -33},
    //Ida D4 Regreso I4
    {-60, 0, 0, 90, -90, 0, 179, 267, -94, 235, -98, 207, 219, -20, -22},
    //Ida D5 Regreso I5
    {-60, 0, 0, 90, -90, 0, 180, 259, -57, 226, -86, 202, 226, -44, -6},
    //Regreso D1 ida I1
    {-60, 0, 0, 90, -90, 0, 180, 280, -93, 231, -88, 209, 225, -48, -8},
    //Regreso D2 ida I2
    {-60, 0, 0, 90, -90, 0, 180, 284, -113, 241, -88, 216, 233, -33, -26},
    //Regreso D3 ida I3
    {-60, 0, 0, 90, -90, 0, 180, 268, -98, 255, -96, 216, 221, -22, -20},
    //Regreso D4 ida I4
    {-60, 0, 0, 90, -90, 0, 180, 235, -98, 267, -94, 219, 207, -22, -20},
    //Regreso D5 ida I5
    {-60, 0, 0, 90, -90, 0, 180, 226, -98, 259, -57, 226, 202, -6, -44}
};

int currentFrame;
GLfloat theta[15] = {-60, 0 ,0 ,90 ,-90, 0, 180 ,259 ,-57 ,259 ,-57 ,202 ,202 ,-44 ,-44};

/* Chosen part for debug */
int bpart;

/* debug mode flag */
int debug = 1;

double size = 1.0;

int compare_float(float f1, float f2){
    float precision = 0.1;
    if (((f1 - precision) < f2) &&
        ((f1 + precision) > f2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void drawAxis()
{
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    {
        glColor3f(1, 0, 0);
        glVertex3f(-10, -10, 0);
        glVertex3f(10, -10, 0);
        
        glColor3f(0, 0, 1);
        glVertex3f(0, -10, -10);
        glVertex3f(0, -10, 10);
    }
    glEnd();
    glFlush();
}

float yCam = 0.0;

void display() // Called for each frame (about 60 times per second).
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers.
    glLoadIdentity();                                    // Reset 3D view matrix.
    gluLookAt(0.0, yCam, 10.0,                            // Where the camera is.
              0.0, 0.0, 0.0,                            // To where the camera points at.
              0.0, 1.0, 0.0);
    
    // Draws "floor"
    drawAxis();
    
    /* Draw Torso */
    torso->draw();
    
    /* Draw Guns*/
    guns->draw();
    
    /* Connect the left leg*/
    leftLeg->draw();
    
    /* Connect the right leg */
    rightLeg->draw();
    
    glFlush();
    glutSwapBuffers(); // Swap the hidden and visible buffers.
}

float dir = 1;

void idle() {


    if(!debug){
        
        if (yCam > 0.5 || yCam < -0.5){
            dir = dir*-1;
        }
        yCam += 0.0008*dir;
        
        if(currentFrame == (sizeof(keyframes)/sizeof(keyframes[0]))){
            currentFrame = 0;
        }
        
        int equal = 1;
        
        for(int x = 0; x < (sizeof(theta)/sizeof(theta[0])); x++){
            if(!compare_float(keyframes[currentFrame][x],theta[x])){
                if(keyframes[currentFrame][x] >= theta[x]){
                    theta[x] += 0.1f;
                } else{
                    theta[x] -= 0.1f;
                }
                equal = equal&0;
            }
        }
        
        if(equal){
            currentFrame++;
        }
    }
    glutPostRedisplay(); // Display again.
}

void reshape(int x, int y) // Called when the window geometry changes.
{
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (x <= y)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat)y / (GLfloat)x,
                10.0 * (GLfloat)y / (GLfloat)x, 0.2, 30.0);
    else
        glOrtho(-10.0 * (GLfloat)x / (GLfloat)y,
                10.0 * (GLfloat)x / (GLfloat)y, 0.0, 10.0, 0.2, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 Used primarily to measure the right angles
 */
void littleKey(unsigned char key, int x, int y)
{
    if (debug)
    {
        switch (key)
        {
            case 'A':
            case 'q':
            case '1':
            case 1:
                bpart = 0;
                break;
            case 'B':
            case 'w':
            case '2':
            case 2:
                bpart = 1;
                break;
            case 'C':
            case 'e':
            case '3':
            case 3:
                bpart = 2;
                break;
            case 'D':
            case 'r':
            case '4':
            case 4:
                bpart = 3;
                break;
            case 'E':
            case 't':
            case '5':
            case 5:
                bpart = 4;
                break;
            case 'F':
            case 'y':
            case '6':
            case 6:
                bpart = 5;
                break;
            case 'G':
            case 'u':
            case '7':
            case 7:
                bpart = 6;
                break;
            case 'H':
            case 'i':
            case '8':
            case 8:
                bpart = 7;
                break;
            case 'I':
            case 'o':
            case '9':
            case 9:
                bpart = 8;
                break;
            case 'J':
            case 'p':
            case 10:
                bpart = 9;
                break;
            case 'K':
            case 'z':
            case 11:
                bpart = 10;
                break;
            case 'M':
            case 'x':
            case 12:
                bpart = 11;
                break;
            case 'N':
            case 'c':
            case 13:
                bpart = 12;
                break;
                
            case 'O':
            case 'v':
            case 14:
                bpart = 13;
                break;
                
            case 'P':
            case 'b':
            case 15:
                bpart = 14;
                break;
                
            case 's':
            case 'S':
                for(int i=0;i<(sizeof(theta)/sizeof(theta[0]));i++){
                    printf("theta[%i] = %f\n",i,theta[i]);
                }
                break;
        }
    }
    glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
    if(debug){
        switch (key)
        {
            case GLUT_KEY_UP:
                theta[bpart] += 1;
                printf("Theta[%i]=%f\n", bpart, theta[bpart]);
                break;
            case GLUT_KEY_DOWN:
                theta[bpart] -= 1;
                printf("Theta[%i]=%f\n", bpart, theta[bpart]);
                break;
        }
    }
}

void myinit()
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {0.3, 0.3, 0.3, 0.3};
    GLfloat mat_ambient[] = {0.9, 0.9, 0.9, 0.9};
    GLfloat mat_shininess = {100.0};
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {10.0, 10.0, 10.0, 0.0};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    
    //glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_ALWAYS);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.1, 0.1, 0.1);
    
    /* allocate quadrics with filled drawing style */
    h = gluNewQuadric();
    gluQuadricDrawStyle(h, GLU_FILL);
    rla = gluNewQuadric();
    gluQuadricDrawStyle(rla, GLU_FILL);
    
    /* start parts */
    leftLeg = new LeftLeg();
    rightLeg = new RightLeg();
    torso = new Torso();
    guns = new Guns();
}

void menu(int id){
    debug = id;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                                      // Init GLUT with command line parameters.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB); // Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
    glutInitWindowSize(500, 600);
    glutCreateWindow("AT-ST");
    glutKeyboardFunc(littleKey);
    glutSpecialFunc(specialKey);
    
    
    /* Debug mouse */
    glutCreateMenu(menu);
    glutAddMenuEntry("Stop debug", 0);
    glutAddMenuEntry("Start debug", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    myinit();
    glutReshapeFunc(reshape); // Reshape CALLBACK function.
    glutDisplayFunc(display); // Display CALLBACK function.
    glutIdleFunc(idle);          // Idle CALLBACK function.
    glutMainLoop();              // Begin graphics program.
    return 0;                  // ANSI C requires a return value.
}
