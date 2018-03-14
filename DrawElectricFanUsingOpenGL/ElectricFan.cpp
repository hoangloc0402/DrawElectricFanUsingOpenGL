#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#define DEG2RAD (3.14159f/180.0f)
using namespace std;

GLfloat angle;
int		screenWidth = 800;
int		screenHeight = 800;
const int circleCount = 100; //Số lượng vòng tròn trong lưới quạt
int fanSpeed = 0; //Tốc độ quạt, ấn "+" "-" để thay đổi
float orthorScaler = 3; //Tham số để scale to nhỏ, tuỳ chỉnh bằng pageup và pagedown
bool swing = false; //Thay đổi chế độ swing của quạt, ấn "s" để thay đổi
bool displayBody = false; //Biến xác định có hiển thị thân quạt hay không, ấn "b" để thay đổi
bool displayEngine = false; //Biến xác định có hiển thị động cơ hay không, ấn "e" để thay đổi
bool displayDome = false; //Biến xác định có hiển thị lưới quạt hay không, ấn "d" để thay đổi
bool displayFanBlade = false; //Biến xác định có hiển thị cánh quạt hay không, ấn "f" để thay đổi
bool draw4Fan = false; //Biến xác định sẽ vẽ 4 quạt cùng lúc hoặc 1 quạt

//Các tham số điều chỉnh góc nhìn khi click kéo chuột
int o_x, o_y;
float eyeX, eyeY, eyeZ;
float centerX, centerY, centerZ;
float upX, upY, upZ;
float alpha = 45;
float beta = 45;
float deltaAngle = 5;
float dR = 0.2;
float Radius = 4;

//Vẽ trục toạ độ
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

#pragma region FanBladeAndEngine
//Chọn hình thức tô màu
void fillColorAndFrame(Mesh &m) {
	m.DrawColor();
	//m.DrawWireframe();
}

//Vẽ một cánh quạt
void drawOneBlade() {
	Mesh blade;
	blade.CreateFanBlade(2, 0.3);
	fillColorAndFrame(blade);
}

//Vẽ hộp động cơ
void drawEngineCover() {
	Mesh engineCoverPart1, engineCoverPart2, engineCoverPart3, engineCoverPart4, engineCoverPart5;

	engineCoverPart1.CreateConical(0.4, 0.35, 0.1, -0.1, 2);
	engineCoverPart2.CreateConical(0.45, 0.4, 0.2, -0.3, 2);
	engineCoverPart3.CreateConical(0.45, 0.45, 0.4, -0.7, 2);
	engineCoverPart4.CreateConical(0.4, 0.45, 0.2, -0.9, 2);
	engineCoverPart5.CreateConical(0.35, 0.4, 0.1, -1, 2);

	fillColorAndFrame(engineCoverPart1);
	fillColorAndFrame(engineCoverPart2);
	fillColorAndFrame(engineCoverPart3);
	fillColorAndFrame(engineCoverPart4);
	fillColorAndFrame(engineCoverPart5);
}

//Vẽ toàn bộ cánh quạt
void drawWholeFanBlade() {

	glPushMatrix();
	glRotatef(-angle * fanSpeed, 0, 1, 0);
	drawOneBlade();
	glRotatef(60, 0, 1, 0); drawOneBlade();
	glRotatef(60, 0, 1, 0); drawOneBlade();
	glRotatef(60, 0, 1, 0); drawOneBlade();
	glRotatef(60, 0, 1, 0); drawOneBlade();
	glRotatef(60, 0, 1, 0); drawOneBlade();
	glPopMatrix();

	Mesh pivotCover, smallPivotCover, steelPivot;
	pivotCover.CreateConical(0.3, 0.3, 0.3, 0, 0);
	fillColorAndFrame(pivotCover);

	smallPivotCover.CreateConical(0.25, 0.2, 0.15, 0.3, 0);
	fillColorAndFrame(smallPivotCover);

	steelPivot.CreateConical(0.1, 0.1, 0.3, -0.3, 1);
	fillColorAndFrame(steelPivot);
}
#pragma endregion

#pragma region FanBody
//Vẽ núm vận cho quạt
void drawSwitch(float heightBot) {
	Mesh fanSwitchP1;
	Mesh fanSwitchP2;
	Mesh fanSwitchP3;
	Mesh fanSwitchP4;
	Mesh fanSwitchP5;

	glPushMatrix();

	glTranslatef(0, 0, 1.5);

	fanSwitchP1.CreateConical(0.4, 0.4, 0.1, heightBot, 1);
	fanSwitchP2.CreateOval(0.1, 0.1, 0.1, heightBot + 0.1, heightBot + 0.11, 0.25, 0, 6);
	fanSwitchP3.CreateOval(0.09, 0.09, 0.09, heightBot + 0.11, heightBot + 0.12, 0.25, 0, 6);
	fanSwitchP4.CreateOval(0.08, 0.08, 0.08, heightBot + 0.12, heightBot + 0.13, 0.25, 0, 6);
	fanSwitchP5.CreateOval(0.07, 0.07, 0.07, heightBot + 0.13, heightBot + 0.15, 0.25, 0, 6);


	/*fanSwitchP1.DrawWireframe();
	fanSwitchP2.DrawWireframe();
	fanSwitchP3.DrawWireframe();
	fanSwitchP4.DrawWireframe();
	fanSwitchP5.DrawWireframe();*/

	fanSwitchP1.DrawColor();
	fanSwitchP2.DrawColor();
	fanSwitchP3.DrawColor();
	fanSwitchP4.DrawColor();
	fanSwitchP5.DrawColor();

	glPopMatrix();
}

//Vẽ trục tiếp xúc giữa động cơ và cổ quạt
void drawContractor() {
	Mesh fanContractor;

	glPushMatrix();

	glTranslatef(0.1, 1.6, -0.75);
	glRotatef(30, 1, 0, 0);
	glRotatef(90, 0, 0, 1);

	fanContractor.CreateOval(0.2, 0.2, 0.2, 0, 0.2, 0.15, 0, 0);

	//fanContractor.DrawWireframe();
	fanContractor.DrawColor();

	glPopMatrix();
}

//Vẽ dây
void drawRopes(float length, float posX, float posZ) {
	Mesh fanRopesP1;
	Mesh fanRopesP2;
	Mesh fanRopesP3;
	Mesh fanRopesP4;
	Mesh fanRopesP5;

	glPushMatrix();

	glTranslatef(-posX, -0.15, posZ);

	glRotatef(-90, 1, 0, 0);

	fanRopesP1.CreateConical(0.08, 0.06, 0.1, 0, 1);
	fanRopesP2.CreateConical(0.06, 0.04, 0.2, 0.1, 1);
	fanRopesP3.CreateConical(0.04, 0.02, 0.3, 0.2, 1);
	fanRopesP4.CreateConical(0.02, 0.01, 0.4, 0.3, 1);
	fanRopesP5.CreateConical(0.01, 0.01, length, 0.4, 1);

	/*fanRopesP1.DrawWireframe();
	fanRopesP2.DrawWireframe();
	fanRopesP3.DrawWireframe();
	fanRopesP4.DrawWireframe();
	fanRopesP5.DrawWireframe();*/

	fanRopesP1.DrawColor();
	fanRopesP2.DrawColor();
	fanRopesP3.DrawColor();
	fanRopesP4.DrawColor();
	fanRopesP5.DrawColor();



	glPopMatrix();
}

//Vẽ đế quạt
void drawFanBase(float oriHeight) {
	Mesh	fanBaseP1;
	Mesh	fanBaseP2;
	Mesh	fanBaseP3;
	Mesh	fanBaseP4;
	Mesh	fanBaseP5;

	fanBaseP1.CreateOval(0.8, 0.6, 0.8, 0, oriHeight, 1.5, 0.2, 1);
	fanBaseP2.CreateOval(0.78, 0.58, 0.78, oriHeight, oriHeight + 0.02, 1.5, 0.2, 2);
	fanBaseP3.CreateOval(0.76, 0.56, 0.76, oriHeight + 0.02, oriHeight + 0.04, 1.5, 0.2, 3);
	fanBaseP4.CreateOval(0.74, 0.54, 0.74, oriHeight + 0.04, oriHeight + 0.06, 1.5, 0.2, 4);
	fanBaseP5.CreateOval(0.72, 0.52, 0.72, oriHeight + 0.06, oriHeight + 0.08, 1.5, 0.2, 5);


	/*fanBaseP1.DrawWireframe();
	fanBaseP2.DrawWireframe();
	fanBaseP3.DrawWireframe();
	fanBaseP4.DrawWireframe();
	fanBaseP5.DrawWireframe();*/

	fanBaseP1.DrawColor();
	fanBaseP2.DrawColor();
	fanBaseP3.DrawColor();
	fanBaseP4.DrawColor();
	fanBaseP5.DrawColor();

}

//Vẽ cổ quạt
void drawFanNeck(float oriHeight) {
	Mesh	fanNeckP1;
	Mesh	fanNeckP2;
	Mesh	fanNeckP3;
	Mesh	fanNeckP4;
	Mesh	fanNeckP5;

	fanNeckP1.CreateFanNeck(0.36, 0.34, oriHeight, oriHeight + 0.1, 0, 0.1, 0);
	fanNeckP2.CreateFanNeck(0.34, 0.32, oriHeight + 0.1, oriHeight + 0.2, 0.1, 0.15, 1);
	fanNeckP3.CreateFanNeck(0.32, 0.30, oriHeight + 0.2, oriHeight + 0.3, 0.15, 0.2, 2);
	fanNeckP4.CreateFanNeck(0.30, 0.28, oriHeight + 0.3, oriHeight + 0.5, 0.2, 0.3, 3);
	fanNeckP5.CreateFanNeck(0.28, 0.25, oriHeight + 0.5, oriHeight + 1, 0.3, 0.6, 4);

	/*fanNeckP1.DrawWireframe();
	fanNeckP2.DrawWireframe();
	fanNeckP3.DrawWireframe();
	fanNeckP4.DrawWireframe();
	fanNeckP5.DrawWireframe();*/

	fanNeckP1.DrawColor();
	fanNeckP2.DrawColor();
	fanNeckP3.DrawColor();
	fanNeckP4.DrawColor();
	fanNeckP5.DrawColor();
}

//Vẽ toàn thân quạt
void drawFanBody() {
	float oriHeight = 0.22;
	drawFanBase(oriHeight);
	drawFanNeck(oriHeight + 0.2);
	drawSwitch(0.3);
	drawContractor();
	drawRopes(2.5, 0.15, 4.2);
	drawRopes(3, -0.15, 4.7);
}
#pragma endregion

#pragma region FanDome
void drawDomeLine(float arr[circleCount][2], float low, float high, int section, float innerRadius, float outterRadius) {
	glBegin(GL_LINES);
	for (int i = 0; i <= circleCount; i++) {
		float x = arr[i%circleCount][0];
		float y = low;
		float z = arr[i%circleCount][1];
		for (int j = 1; j <= section; j++) {
			glVertex3f(x, y, z);
			x = cos(i*(360.0f / circleCount)*DEG2RAD)*(innerRadius + (outterRadius - innerRadius) / section * j);
			z = sin(i*(360.0f / circleCount)*DEG2RAD)*(innerRadius + (outterRadius - innerRadius) / section * j);
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
		SubCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)* subRadius;
		SubCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)* subRadius;

		InnerCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)* innerRadius;
		InnerCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)* innerRadius;

		InCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)*    inRadius;
		InCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)*    inRadius;

		MiddleCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)*middleRadius;
		MiddleCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)*middleRadius;

		OutterCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)*outterRadius;
		OutterCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)*outterRadius;
	}

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, subHeight, 0.0f);
	for (int i = 0; i < circleCount + 1; i++) {
		glVertex3f(SubCircle[i%circleCount][0], subHeight, SubCircle[i%circleCount][1]);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i <= circleCount; i++) {
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
		SubCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)* subRadius;
		SubCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)* subRadius;

		InnerCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)* innerRadius;
		InnerCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)* innerRadius;

		InCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)*    inRadius;
		InCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)*    inRadius;

		MiddleCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)*middleRadius;
		MiddleCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)*middleRadius;

		OutterCircle[i][0] = cos(i*(360.0f / circleCount)*DEG2RAD)*outterRadius;
		OutterCircle[i][1] = sin(i*(360.0f / circleCount)*DEG2RAD)*outterRadius;
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
#pragma endregion

//Hàm vẽ toàn bộ quạt
void drawFan() {
	glPushMatrix();

	glTranslatef(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glPushMatrix();
	if (displayBody)
		drawFanBody();
	glPopMatrix();

	glTranslatef(0, 1.7, -1.1);
	glRotatef(30, 1, 0, 0);

	if (swing) { //Nếu cho quạt quay (swing)
		if (angle <= 180)
			glRotatef(angle * 120 / 180 - 60, 0, 0, 1);
		else
			glRotatef((360 - angle) * 12 / 18 - 60, 0, 0, 1);
	}

	glTranslatef(0, 1, 0);
	if (displayFanBlade)
		drawWholeFanBlade(); //Vẽ toàn bộ 6 cánh quạt và trục

	glTranslatef(0, -0.3, 0);
	if (displayEngine)
		drawEngineCover(); //Vẽ hộp động cơ

	if (displayDome) {
		glColor3f(0.52f, 0.52f, 0.52f);
		drawDomeRear(2.8, 0.4, 0.1); //Vẽ phần lưới quạt phía sau
		glTranslatef(0, 0.5, 0);
		drawDomeFront(2.8, 0.6); //Vẽ phần lưới quạt phía trước
	}
	glPopMatrix();
}

//Các hàm callback
#pragma region Callback Func
void processTimer(int value) {
	angle += (GLfloat)value / 5;
	if (angle > 360.0f) angle -= 360.0f;
	glutTimerFunc(25, processTimer, value);
	glutPostRedisplay();
}

void onKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '+':
		fanSpeed += 4;
		break;
	case '-':
		fanSpeed -= 4;
		break;
	case 's':
		if (swing) swing = false;
		else swing = true;
		break;
	case 'b':
		if (displayBody) displayBody = false;
		else displayBody = true;
		break;
	case 'd':
		if (displayDome) displayDome = false;
		else displayDome = true;
		break;
	case 'f':
		if (displayFanBlade) displayFanBlade = false;
		else displayFanBlade = true;
		break;
	case 'e':
		if (displayEngine) displayEngine = false;
		else displayEngine = true;
		break;
	case 'a':
		displayBody = displayEngine = displayDome = displayFanBlade = true;
		break;
	case '4':
		if (draw4Fan) draw4Fan = false;
		else draw4Fan = true;
		break;
	default: break;
	}
	if (fanSpeed > 20) fanSpeed = 20;
	if (fanSpeed < 0) fanSpeed = 0;
	glutPostRedisplay();
}

void onSpecialKey(int key, int x, int y) {
	switch (key) {

	case GLUT_KEY_PAGE_UP:		// Zoom in
		orthorScaler -= 0.2;
		break;
	case GLUT_KEY_PAGE_DOWN:	// Zoom out
		orthorScaler += 0.2;
	default:
		break;
	}
	if (orthorScaler > 10) orthorScaler = 10;
	if (orthorScaler < 0.5) orthorScaler = 0.5;
	glutPostRedisplay();
}

void onReshape(int w, int h) {
	int size = min(w, h);
	glViewport(0, 0, size, size);
}

void onMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		o_x = x;
		o_y = y;
	}
}

void onMotion(int x, int y) {
	alpha += (x - o_x) / 2;
	beta += (y - o_y) / 2;
	o_x = x;
	o_y = y;
	glutPostRedisplay();
}

#pragma endregion


void view() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	glOrtho(-orthorScaler, orthorScaler, -orthorScaler, orthorScaler, -orthorScaler, orthorScaler);
}
void initOpenGL() {
	//setup projection type
	//glFrustrum: define viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-2.0,	//left
		2.0,	//right
		-2.0,	//bottom
		2.0,	//top
		2.0,	//near
		10.0	//far
	);
	//Default MatrixMode is MODELVIEW 
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);

}
void initialize() {
	eyeX = Radius * cos(DEG2RAD * alpha);
	eyeY = Radius * sin(DEG2RAD * beta);
	eyeZ = Radius * sin(DEG2RAD * alpha);
	centerX = 0;
	centerY = 0;
	centerZ = 0;
	upX = 0;
	upY = 1;
	upZ = 0;
}

void myDisplay() {
	initOpenGL();
	initialize();
	view();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	drawAxis();
	glViewport(0, 0, screenWidth, screenHeight);

	if (draw4Fan) {
		glPushMatrix();
		glTranslatef(5, 0, 0);
		drawFan();
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(5, 0, 0);
		drawFan();
		glPopMatrix();

		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(5, 0, 0);
		drawFan();
		glPopMatrix();

		glPushMatrix();
		glRotatef(270, 0, 1, 0);
		glTranslatef(5, 0, 0);
		drawFan();
		glPopMatrix();

	}
	else drawFan();

	glFlush();
	glutSwapBuffers();
}

int main(int argc, CHAR* argv[]) {

	glutInit(&argc, (char**)argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight); 
	glutInitWindowPosition(50, 50); 
	glutCreateWindow("Draw Electric Fan"); 

	glutDisplayFunc(myDisplay);
	glutTimerFunc(5, processTimer, 5);
	glutKeyboardFunc(onKeyboard);
	glutSpecialFunc(onSpecialKey);
	glutReshapeFunc(onReshape);
	glutMotionFunc(onMotion);
	glutMouseFunc(onMouseDown);

	glutMainLoop();
	return 0;
}

