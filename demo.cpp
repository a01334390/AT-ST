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
#include <stdlib.h>
// #include <iostream>
#include <string.h>
#include <math.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

/* Declare body parts height */
#define BODY_HEIGHT 5.0
#define BODY_RADIUS 3.0
#define UPPER_GUN_HEIGHT 5.0
#define UPPER_GUN_RADIUS 0.5
#define MIDDLE_GUN_RADIUS 1.0
#define MIDDLE_GUN_HEIGHT 4.0

#define UPPER_LEG_RADIUS 0.5
#define LOWER_LEG_RADIUS 0.5
#define LOWER_LEG_HEIGHT 7.0
#define UPPER_LEG_HEIGHT 3.0
#define LEFT_FEET_HEIGHT 1.0
#define FEET_WIDTH 2.0
#define FEET_LENGTH 3.0

#define LOWEST_LEG_RADIUS 0.5
#define LOWEST_LEG_HEIGHT 3.0


/* Initial joint angles */
typedef float point[3];

static GLfloat keyframes[5][15] = {
	{-30.0,0.0,0.0,95,-88.0,0.0,180,193,-43,263,-121,267,267,-57,-50},
	{-30.0,0.0,0.0,80,-88.0,0.0,180,263,-121,193,-43,267,266,-50,-57},
	{-30.0,0.0,0.0,95,-88.0,0.0,180,284,-141,263,-121,267,267,-57,-50},
	{-30.0,0.0,0.0,80,-88.0,0.0,180,263,-121,284,-141,267,266,-50,-57},
	{-30.0,0.0,0.0,95,-88.0,0.0,180,263,-121,263,-121,267,267,-50,-50}
};

int currentFrame;
GLfloat theta[15] ={-0,0.0,0.0,89,-88.0,0.0,180,263,-121,263,-121,267,267,-50,-50};
/* Chosen part for debug */
int bpart;
/* debug mode flag */
int debug = 1;

GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul, *lf, *rf,*lwll, *lwrl;

double size = 1.0;

void body()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(t, BODY_RADIUS, BODY_RADIUS, BODY_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_gun()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(lua, UPPER_GUN_RADIUS, UPPER_GUN_RADIUS, UPPER_GUN_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_gun()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(rua, UPPER_GUN_RADIUS, UPPER_GUN_RADIUS, UPPER_GUN_HEIGHT, 10, 10);
	glPopMatrix();
}

void middle_gun()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(lla, MIDDLE_GUN_RADIUS, MIDDLE_GUN_RADIUS, MIDDLE_GUN_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_upper_leg()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_lower_leg()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_upper_leg()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_lower_leg()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_lowest_leg(){
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(lwrl, LOWEST_LEG_RADIUS, LOWEST_LEG_RADIUS, LOWEST_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_lowest_leg(){
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(lwll, LOWEST_LEG_RADIUS, LOWEST_LEG_RADIUS, LOWEST_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_feet()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(lf, FEET_LENGTH, FEET_WIDTH, LEFT_FEET_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_feet()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(lf, FEET_LENGTH, FEET_WIDTH, LEFT_FEET_HEIGHT, 10, 10);
	glPopMatrix();
}

void init()
{
	glEnable(GL_DEPTH_TEST);		  // Enable check for close and far objects.
	glClearColor(0.0, 0.0, 0.0, 0.0); // Clear the color state.
	glMatrixMode(GL_MODELVIEW);		  // Go to 3D mode.
	glLoadIdentity();				  // Reset 3D view matrix.
}

void drawAxis()
{
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 1);
		glVertex3f(0, 0, 1);
	}
	glEnd();
	glFlush();
}

void display() // Called for each frame (about 60 times per second).
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers.
	glLoadIdentity();									// Reset 3D view matrix.
	gluLookAt(0.0, 0.0, 10.0,							// Where the camera is.
			  0.0, 0.0, 0.0,							// To where the camera points at.
			  0.0, 1.0, 0.0);
	drawAxis();
	/* Draw Torso */
	glColor3f(0, 0, 0);
	glRotatef(theta[0], 0, 1, 0);
	body();
	/* Connect left gun to the body */
	glPushMatrix();
	glTranslatef(-(BODY_RADIUS + UPPER_GUN_RADIUS), 0.2 * BODY_HEIGHT, 0);
	glRotatef(theta[3], 1, 0, 0);
	left_gun();
	glPopMatrix();

	/* Connect middle gun to the body */
	glPushMatrix();
	glTranslatef((BODY_RADIUS / 2 - 1.5 * MIDDLE_GUN_RADIUS), 0.2 * BODY_HEIGHT, 0);
	glRotatef(theta[3], 1, 0, 0);
	left_gun();
	glPopMatrix();

	/* Connect right gun to the body */
	glPushMatrix();
	glTranslatef(BODY_RADIUS + UPPER_GUN_RADIUS, 0.2 * BODY_HEIGHT, 0);
	glRotatef(theta[3], 1, 0, 0);
	right_gun();
	glPopMatrix();

	/* Connect the left leg */
	glPushMatrix();
	glTranslatef(-(BODY_RADIUS + UPPER_LEG_RADIUS), 0.1 * UPPER_LEG_HEIGHT, 0);
	glRotatef(theta[7], 1, 0, 0);
	left_upper_leg();

	glTranslatef(0, UPPER_LEG_HEIGHT, 0);
	glRotatef(theta[8], 1, 0, 0);
	left_lower_leg();

	glTranslatef(0, UPPER_LEG_HEIGHT + 4 * LEFT_FEET_HEIGHT, 0);
	glRotatef(theta[13], 1, 0, 0);
	left_lowest_leg();

	glTranslatef(0,3*LEFT_FEET_HEIGHT,1);
	glRotatef(theta[11],1,0,0);
	left_feet();
	
	glPopMatrix();

	/* Connect the right leg */
	glPushMatrix();
	glTranslatef(BODY_RADIUS + UPPER_LEG_RADIUS, 0.1 * UPPER_LEG_HEIGHT, 0);
	glRotatef(theta[9], 1, 0, 0);
	right_upper_leg();

	glTranslatef(0, UPPER_LEG_HEIGHT, 0);
	glRotatef(theta[10], 1, 0, 0);
	right_lower_leg();

	glTranslatef(0, UPPER_LEG_HEIGHT + 4*LEFT_FEET_HEIGHT, 0);
	glRotatef(theta[14], 1, 0, 0);
	right_lowest_leg();

	glTranslatef(0,3*LEFT_FEET_HEIGHT,1);
	glRotatef(theta[12],1,0,0);
	right_feet();

	glPopMatrix();

	glFlush();
	glutSwapBuffers(); // Swap the hidden and visible buffers.
}

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

void idle() {
	if(!debug){
		if(currentFrame == (sizeof(keyframes)/sizeof(keyframes[0]))){
		currentFrame = 0;
	}

	int equal = 1;

	for(int x = 0; x < (sizeof(theta)/sizeof(theta[0])); x++){
		if(!compare_float(keyframes[currentFrame][x],theta[x])){
			if(keyframes[currentFrame][x] >= theta[x]){
				theta[x] += 0.07f;
			} else{
				theta[x] -= 0.07f;
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
				10.0 * (GLfloat)y / (GLfloat)x, -10.0, 10.0);
	else
		glOrtho(-10.0 * (GLfloat)x / (GLfloat)y,
				10.0 * (GLfloat)x / (GLfloat)y, 0.0, 10.0, -10.0, 10.0);
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
		case 'a':
		case '1':
		case 1:
			bpart = 0;
			break;
		case 'B':
		case 'b':
		case '2':
		case 2:
			bpart = 1;
			break;
		case 'C':
		case 'c':
		case '3':
		case 3:
			bpart = 2;
			break;
		case 'D':
		case 'd':
		case '4':
		case 4:
			bpart = 3;
			break;
		case 'E':
		case 'e':
		case '5':
		case 5:
			bpart = 4;
			break;
		case 'F':
		case 'f':
		case '6':
		case 6:
			bpart = 5;
			break;
		case 'G':
		case 'g':
		case '7':
		case 7:
			bpart = 6;
			break;
		case 'H':
		case 'h':
		case '8':
		case 8:
			bpart = 7;
			break;
		case 'I':
		case 'i':
		case '9':
		case 9:
			bpart = 8;
			break;
		case 'J':
		case 'j':
		case 10:
			bpart = 9;
			break;
		case 'K':
		case 'k':
		case 11:
			bpart = 10;
			break;
		case 'M':
		case 'm':
		case 12:
			bpart = 11;
			break;
		case 'N':
		case 'n':
		case 13:
			bpart = 12;
			break;
		
		case 'O':
		case 'o':
		case 14:
			bpart = 13;
			break;
		
		case 'P':
		case 'p':
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

	// glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// glEnable(GL_DEPTH_TEST);
	// 	glDepthFunc(GL_ALWAYS);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.1, 0.1, 0.1);

	/* allocate quadrics with filled drawing style */

	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);
	lua = gluNewQuadric();
	gluQuadricDrawStyle(lua, GLU_FILL);
	lla = gluNewQuadric();
	gluQuadricDrawStyle(lla, GLU_FILL);
	rua = gluNewQuadric();
	gluQuadricDrawStyle(rua, GLU_FILL);
	rla = gluNewQuadric();
	gluQuadricDrawStyle(rla, GLU_FILL);
	lul = gluNewQuadric();
	gluQuadricDrawStyle(lul, GLU_FILL);
	lll = gluNewQuadric();
	gluQuadricDrawStyle(lll, GLU_FILL);
	rul = gluNewQuadric();
	gluQuadricDrawStyle(rul, GLU_FILL);
	rll = gluNewQuadric();
	gluQuadricDrawStyle(rll, GLU_FILL);
	lf = gluNewQuadric();
	gluQuadricDrawStyle(lf, GLU_FILL);
	rf = gluNewQuadric();
	gluQuadricDrawStyle(rf, GLU_FILL);
	lwll = gluNewQuadric();
	gluQuadricDrawStyle(lwll, GLU_FILL);
	lwrl = gluNewQuadric();
	gluQuadricDrawStyle(lwrl, GLU_FILL);
}

void menu(int id){
   debug = id;
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);									  // Init GLUT with command line parameters.
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
	glutIdleFunc(idle);		  // Idle CALLBACK function.
	glutMainLoop();			  // Begin graphics program.
	return 0;				  // ANSI C requires a return value.
}