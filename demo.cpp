/*
 * Fernando Martin Garcia Del Angel
 * A01334390
 * TC3022. Computer Graphics Course.
 * Flags of the world
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
#include <string.h>
#include <math.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

void init() {
	glEnable(GL_DEPTH_TEST);			// Enable check for close and far objects.
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Clear the color state.
	glMatrixMode(GL_MODELVIEW);			// Go to 3D mode.
	glLoadIdentity();					// Reset 3D view matrix.
}

void drawRectangle(float x, float y, float w, float h){
    glBegin(GL_POLYGON);
    {
        glVertex3f(x,y,0);
        glVertex3f(x +w,y,0);
        glVertex3f(x+w,y-h,0);
        glVertex3f(x,y-h,0);
        
    }
    glEnd();
	glFlush();
}

void drawAxis (){
	glLineWidth(3.0f);
	glBegin(GL_LINES);{
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(1,0,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,1,0);
		glColor3f(0,0,1);
		glVertex3f(0,0,1);
		glVertex3f(0,0,1);
	}
	glEnd();
	glFlush();
}

void display()							// Called for each frame (about 60 times per second).
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(0.0, 0.0, 10.0,										// Where the camera is.
		      0.0, 0.0, 0.0,										// To where the camera points at.
		      0.0, 1.0, 0.0);
	glLineWidth(5);
	drawAxis();
	glutSwapBuffers();												// Swap the hidden and visible buffers.
}

void idle()															// Called when drawing is finished.
{
	
    glutPostRedisplay();										// Display again.
}

void reshape(int x, int y)											// Called when the window geometry changes.
{
	glMatrixMode(GL_PROJECTION);									// Go to 2D mode.
	glLoadIdentity();												// Reset the 2D matrix.
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);		// Configure the camera lens aperture.
	glMatrixMode(GL_MODELVIEW);										// Go to 3D mode.
	glViewport(0, 0, x, y);											// Configure the camera frame dimensions.
	gluLookAt(0.0, 1.0, 4.0,
		      0.0, 0.0, 0.0,
		      0.0, 1.0, 0.0);
	display();
}


/*
	This can help on having an interactive keyboard
*/
void littleKey(unsigned char key, int x, int y){
	switch(key){
		case 'A': case 'a': case '1': case 1:
			
		break;
		case 'B': case 'b': case '2': case 2:
			
		break;
		case 'C': case 'c': case '3': case 3:
			
		break;
		case 'D': case 'd': case '4': case 4:
			
		break;
		case 'E': case 'e': case '5': case 5:
			
		break;
		case 'F': case 'f': case '6': case 6:
			
		break;
		case 'G': case 'g': case '7': case 7:
			
		break;
	}
	//Goes back to the display function
	glutPostRedisplay();
}

void specialKey(int key, int x,int y){
	switch(key){
		case GLUT_KEY_UP:
			
			break;
		case GLUT_KEY_DOWN:
			
			break;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);											// Init GLUT with command line parameters.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);		// Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
	glutInitWindowSize(800, 600);
	glutCreateWindow("AT-ST");
	
	init();
	glutKeyboardFunc(littleKey);
	glutSpecialFunc(specialKey);
	glutReshapeFunc(reshape);										// Reshape CALLBACK function.
	glutDisplayFunc(display);										// Display CALLBACK function.
	glutIdleFunc(idle);												// Idle CALLBACK function.
	glutMainLoop();													// Begin graphics program.
	return 0;														// ANSI C requires a return value.
}