#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#define DEG2RAD (3.14159f/180.0f)
using namespace std;

GLfloat angle;
int		screenWidth = 1200;
int		screenHeight = 600;
Mesh	fanBlade;


void drawAxis() {
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(40, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 40, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 40);
	glEnd();
}

void myDisplay() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		//1.5*cos(DEG2RAD*angle),	//eyeX
		1.5*sin(DEG2RAD*angle),	//eyeY
		1.5,

		1.5*cos(DEG2RAD*angle),	//eyeZ
		0.0,	//reference point X
		0.0,	//reference point Y
		0.0,	//reference point Z
		0.0,	//up vector X
		1.0,	//up vector Y
		0.0		//up vector Z
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth / 2, screenHeight);
	drawAxis();
	glColor3f(0, 0, 0);


	fanBlade.DrawWireframe();


	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	drawAxis();

	fanBlade.DrawColor();

	glFlush();
	glutSwapBuffers();
}

void myInit() {
	float	fHalfSize = 4;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}
void processTimer(int value) {
	angle += (GLfloat)value / 5;
	if (angle > 360.0f) angle -= 360.0f;
	glutTimerFunc(100, processTimer, value);
	glutPostRedisplay();
}
int main(int argc, CHAR* argv[]) {


	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(50, 50); // set window position on screen
	glutCreateWindow("Draw Fannnnnnnnnnnnnnnnnnn"); // open the screen window

	fanBlade.CreateFanBlade(2, 0.5);

	myInit();
	glutDisplayFunc(myDisplay);
	glutTimerFunc(100, processTimer, 7);
	glutMainLoop();
	return 0;
}

