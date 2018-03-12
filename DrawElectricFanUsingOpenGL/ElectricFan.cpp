#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#define DEG2RAD (3.14159f/180.0f)
using namespace std;

GLfloat angle;
int		screenWidth = 1200;
int		screenHeight = 600;
const int circleCount = 20;

//void drawAxis() {
//	glColor3f(0, 0, 1);
//	glBegin(GL_LINES);
//	glVertex3f(0, 0, 0);
//	glVertex3f(40, 0, 0);
//
//	glVertex3f(0, 0, 0);
//	glVertex3f(0, 40, 0);
//
//	glVertex3f(0, 0, 0);
//	glVertex3f(0, 0, 40);
//	glEnd();
//}

void fillColorAndFrame(Mesh &m) {
	m.DrawColor();
	//m.DrawWireframe();
}

void drawBlade() {
	Mesh blade;
	blade.CreateFanBlade(2, 0.3);
	fillColorAndFrame(blade);
}

void drawEngineCover() {
	Mesh engineCoverPart1, engineCoverPart2, engineCoverPart3, engineCoverPart4, engineCoverPart5;

	engineCoverPart1.CreateConical(0.4, 0.35, 0.1, -0.1);
	engineCoverPart2.CreateConical(0.45, 0.4, 0.2, -0.3);
	engineCoverPart3.CreateConical(0.45, 0.45, 0.4, -0.7);
	engineCoverPart4.CreateConical(0.4, 0.45, 0.2, -0.9);
	engineCoverPart5.CreateConical(0.35, 0.4, 0.1, -1);

	fillColorAndFrame(engineCoverPart1);
	fillColorAndFrame(engineCoverPart2);
	fillColorAndFrame(engineCoverPart3);
	fillColorAndFrame(engineCoverPart4);
	fillColorAndFrame(engineCoverPart5);

}

void drawWholeFanBlade() {
	glViewport(0, 0, screenWidth/2, screenHeight);
	//drawAxis();
	glColor3f(0, 0, 0);

	glRotatef(-angle*20, 0, 1, 0);
	drawBlade();
	glRotatef(72, 0, 1, 0); drawBlade();
	glRotatef(72, 0, 1, 0); drawBlade();
	glRotatef(72, 0, 1, 0); drawBlade();
	glRotatef(72, 0, 1, 0); drawBlade();
	glRotatef(angle *20, 0, 1, 0);

	Mesh pivot, smallPivot, steelPivot, engineCoverPart1, engineCoverPart2, engineCoverPart3, engineCoverPart4;
	pivot.CreateConical(0.3, 0.3, 0.3,0);
	fillColorAndFrame(pivot);

	smallPivot.CreateConical(0.25, 0.2, 0.15,0.3);
	fillColorAndFrame(smallPivot);

	steelPivot.CreateConical(0.1, 0.1, 0.3, -0.3);
	fillColorAndFrame(steelPivot);

	//glLoadIdentity();

}

void drawDomeLine(float arr[circleCount][2], float low, float high, int section, float innerRadius, float outterRadius) {
	glBegin(GL_LINES);
	for (int i = 0; i < circleCount; i++) {
		float x = arr[i][0];
		float y = low;
		float z = arr[i][1];
		for (int j = 1; j <= section; j++) {
			glVertex3f(x, y, z);
			x = cos(i*(360 / circleCount)*DEG2RAD)*(innerRadius + (outterRadius - innerRadius) / section * j);
			z = sin(i*(360 / circleCount)*DEG2RAD)*(innerRadius + (outterRadius - innerRadius) / section * j);
			y = (high - low) / section * j + low;
			glVertex3f(x, y, z);
		}
	}
	glEnd();
}

void drawDomeFront(float radius, float height) {
	float    SubCircle[circleCount][2];
	float  InnerCircle[circleCount][2];
	float	  InCircle[circleCount][2];
	float MiddleCircle[circleCount][2];
	float OutterCircle[circleCount][2];
	float    subRadius = radius * 0.22f;
	float  innerRadius = radius * 0.24f;
	float     inRadius = radius * 0.52f;
	float middleRadius = radius * 0.80f;
	float outterRadius = radius * 0.9;
	float  innerHeight = height;
	float	 subHeight = height * 0.9f;
	float     inHeight = height * 0.7f;
	float middleHeight = height * 0.4f;
	float outterHeight = 0.0f;
	int		   section = 10;
	for (int i = 0; i < circleCount; i++) {
		SubCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)* subRadius;
		SubCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)* subRadius;

		InnerCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)* innerRadius;
		InnerCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)* innerRadius;

		InCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)*    inRadius;
		InCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)*    inRadius;

		MiddleCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)*middleRadius;
		MiddleCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)*middleRadius;

		OutterCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)*outterRadius;
		OutterCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)*outterRadius;
	}

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, subHeight, 0.0f);
	for (int i = 0; i < circleCount + 1; i++) {
		glVertex3f(SubCircle[i%circleCount][0], subHeight, SubCircle[i%circleCount][1]);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < circleCount; i++) {
		glVertex3f(InnerCircle[i%circleCount][0], innerHeight, InnerCircle[i%circleCount][1]);
		glVertex3f(InnerCircle[(i + 1) % circleCount][0], innerHeight, InnerCircle[(i + 1) % circleCount][1]);

		glVertex3f(InCircle[i%circleCount][0], inHeight, InCircle[i%circleCount][1]);
		glVertex3f(InCircle[(i + 1) % circleCount][0], inHeight, InCircle[(i + 1) % circleCount][1]);

		glVertex3f(MiddleCircle[i%circleCount][0], middleHeight, MiddleCircle[i%circleCount][1]);
		glVertex3f(MiddleCircle[(i + 1) % circleCount][0], middleHeight, MiddleCircle[(i + 1) % circleCount][1]);

		glVertex3f(OutterCircle[i%circleCount][0], outterHeight, OutterCircle[i%circleCount][1]);
		glVertex3f(OutterCircle[(i + 1) % circleCount][0], outterHeight, OutterCircle[(i + 1) % circleCount][1]);
	}
	glEnd();

	drawDomeLine(SubCircle, subHeight, innerHeight, section, subRadius, innerRadius);


	drawDomeLine(InnerCircle, innerHeight, inHeight, section, innerRadius, inRadius);
	drawDomeLine(InCircle, inHeight, middleHeight, section, inRadius, middleRadius);
	drawDomeLine(MiddleCircle, middleHeight, outterHeight, section * 3, middleRadius, outterRadius);;
}

void drawDomeRear(float radius, float height, float lineWidth) {
	float    SubCircle[circleCount][2];
	float  InnerCircle[circleCount][2];
	float	  InCircle[circleCount][2];
	float MiddleCircle[circleCount][2];
	float OutterCircle[circleCount][2];
	float    subRadius = radius * 0.22f;
	float  innerRadius = radius * 0.24f;
	float     inRadius = radius * 0.52f;
	float middleRadius = radius * 0.80f;
	float outterRadius = radius * 0.9;
	float	 subHeight = height * 0.1f;
	float     inHeight = height * 0.2f;
	float middleHeight = height * 0.4f;
	float outterHeight = height;
	int		   section = 10;
	for (int i = 0; i < circleCount; i++) {
		SubCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)* subRadius;
		SubCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)* subRadius;

		InnerCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)* innerRadius;
		InnerCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)* innerRadius;

		InCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)*    inRadius;
		InCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)*    inRadius;

		MiddleCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)*middleRadius;
		MiddleCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)*middleRadius;

		OutterCircle[i][0] = cos(i*(360 / circleCount)*DEG2RAD)*outterRadius;
		OutterCircle[i][1] = sin(i*(360 / circleCount)*DEG2RAD)*outterRadius;
	}

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, subHeight, 0.0f);
	for (int i = 0; i < circleCount + 1; i++) {
		glVertex3f(SubCircle[i%circleCount][0], subHeight, SubCircle[i%circleCount][1]);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < circleCount; i++) {
		glVertex3f(InnerCircle[i%circleCount][0], 0, InnerCircle[i%circleCount][1]);
		glVertex3f(InnerCircle[(i + 1) % circleCount][0], 0, InnerCircle[(i + 1) % circleCount][1]);

		glVertex3f(InCircle[i%circleCount][0], inHeight, InCircle[i%circleCount][1]);
		glVertex3f(InCircle[(i + 1) % circleCount][0], inHeight, InCircle[(i + 1) % circleCount][1]);

		glVertex3f(MiddleCircle[i%circleCount][0], middleHeight, MiddleCircle[i%circleCount][1]);
		glVertex3f(MiddleCircle[(i + 1) % circleCount][0], middleHeight, MiddleCircle[(i + 1) % circleCount][1]);

		glVertex3f(OutterCircle[i%circleCount][0], outterHeight, OutterCircle[i%circleCount][1]);
		glVertex3f(OutterCircle[(i + 1) % circleCount][0], outterHeight, OutterCircle[(i + 1) % circleCount][1]);
	}
	glEnd();

	drawDomeLine(SubCircle, subHeight, 0.0f, section, subRadius, innerRadius);


	drawDomeLine(InnerCircle, 0.0f, inHeight, section, innerRadius, inRadius);
	drawDomeLine(InCircle, inHeight, middleHeight, section, inRadius, middleRadius);
	drawDomeLine(MiddleCircle, middleHeight, outterHeight, section * 3, middleRadius, outterRadius);

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < circleCount + 1; i++) {
		glVertex3f(OutterCircle[i % circleCount][0], outterHeight, OutterCircle[i % circleCount][1]);
		glVertex3f(OutterCircle[i % circleCount][0], outterHeight + lineWidth, OutterCircle[i % circleCount][1]);
	}
	glEnd();
}


void drawFan() {
	//glTranslatef(0, 1, 0);
	//glRotatef(90, 1, 0, 0);
	//glTranslatef(0, 1, 0);
	drawWholeFanBlade();
	glTranslatef(0, -0.3, 0);
	drawEngineCover();
	
	drawDomeRear(2.8, 0.4, 0.1);
	glTranslatef(0, 0.5, 0);
	drawDomeFront(2.8, 0.6);
}













void myDisplay() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		//1.5*cos(DEG2RAD*angle),	//eyeX
		1.5*sin(DEG2RAD*angle),	//eyeY
		1.5*cos(DEG2RAD*angle),

		1.5,	//eyeZ
		0.0,	//reference point X
		0.0,	//reference point Y
		0.0,	//reference point Z
		0.0,	//up vector X
		1.0,	//up vector Y
		0.0		//up vector Z
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawFan();

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

	myInit();
	glutDisplayFunc(myDisplay);
	glutTimerFunc(5, processTimer, 5);
	glutMainLoop();
	return 0;
}

