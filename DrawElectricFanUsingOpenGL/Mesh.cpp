#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		33
#define DEG2RAD (3.14159f/180.0f)

float	ColorArr[COLORNUM][3] = { { 0.6f, 0.0f, 0.0f },{ 0.7f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },
{ 0.96f, 0.0f, 0.0f },{ 0.93f, 0.0f, 0.0f },{ 0.9f, 0.0f, 0.0f },
{ 0.87f, 0.0f, 0.0f },{ 0.83f, 0.0f, 0.0f },{ 0.8f, 0.0f, 0.0f },
{ 0.6f, 0.6f,  0.0f },{ 0.7f, 0.7f,  0.0f },{ 1.0f, 1.0f,  0.0f },
{ 0.97f, 0.97f,  0.0f },{ 0.93f, 0.93f,  0.0f },{ 0.9f, 0.9f,  0.0f },
{ 0.87f, 0.87f,  0.0f },{ 0.83f, 0.83f,  0.0f },{ 0.8f, 0.8f,  0.0f } ,
{ 1.0f, 0.3f, 0.0f },{ 0.06f, 0.6f, 0.75f },{ 0.04f, 0.45f, 0.6f },
{ 0.78f, 0.78f, 0.78f },
{ 0.2f, 0.0f, 0.4f },{ 0.24f, 0.0f, 0.46f },{ 0.28f, 0.0f, 0.52f },{ 0.32f, 0.0f, 0.58f },{ 0.36f, 0.0f, 0.64f },
{ 0.4f, 0.0f, 0.7f },{ 0.44f, 0.0f, 0.76f },{ 0.48f, 0.0f, 0.82f },{ 0.52f, 0.0f, 0.88f },{ 0.56f, 0.0f, 0.94f },
{ 0.6f, 0.0f, 1.0f } };


void Mesh::DrawWireframe() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int		iv = face[f].vert[v].vertIndex;
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::CreateConical(float radius1, float radius2, float height, float y, int color) {
	int i;
	numVerts = 42;
	pt = new Point3[numVerts];
	for (i = 0; i < 20; i++) {
		pt[i].set(radius1 * cos(i * 18 * DEG2RAD), y, radius1*sin(i * 18 * DEG2RAD)); //Hình tròn dưới
		pt[i + 20].set(radius2 * cos(i * 18 * DEG2RAD), y + height, radius2*sin(i * 18 * DEG2RAD)); //Hình tròn trên
	}

	numFaces = 22;
	face = new Face[numFaces];
	if (color == 0) {
		face[20].nVerts = 20;
		face[20].vert = new VertexID[face[20].nVerts];
		face[21].nVerts = 20;
		face[21].vert = new VertexID[face[21].nVerts];
		for (i = 0; i < 20; i++) {
			face[20].vert[i].vertIndex = i;
			face[20].vert[i].colorIndex = 19;
			face[21].vert[i].vertIndex = i + 20;
			face[21].vert[i].colorIndex = 20;
		}
		for (i = 0; i < 20; i++) {
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = (i + 1) % 20;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = i + 20;
			face[i].vert[3].vertIndex = (i + 1) % 20 + 20;
			face[i].vert[0].colorIndex = 19;
			face[i].vert[1].colorIndex = 19;
			face[i].vert[2].colorIndex = 20;
			face[i].vert[3].colorIndex = 20;
		}
	}
	else if (color == 1) {
		face[20].nVerts = 20;
		face[20].vert = new VertexID[face[20].nVerts];
		face[21].nVerts = 20;
		face[21].vert = new VertexID[face[21].nVerts];
		for (i = 0; i < 20; i++) {
			face[20].vert[i].vertIndex = i;
			face[20].vert[i].colorIndex = 19;
			face[21].vert[i].vertIndex = i + 20;
			face[21].vert[i].colorIndex = 20;
		}
		for (i = 0; i < 20; i++) {
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = (i + 1) % 20;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = i + 20;
			face[i].vert[3].vertIndex = (i + 1) % 20 + 20;
			face[i].vert[0].colorIndex = 21;
			face[i].vert[1].colorIndex = 21;
			face[i].vert[2].colorIndex = 21;
			face[i].vert[3].colorIndex = 21;
		}
	}
	else if (color == 2) {
		face[20].nVerts = 20;
		face[20].vert = new VertexID[face[20].nVerts];
		face[21].nVerts = 20;
		face[21].vert = new VertexID[face[21].nVerts];
		for (i = 0; i < 20; i++) {
			face[20].vert[i].vertIndex = i;
			face[20].vert[i].colorIndex = 19;
			face[21].vert[i].vertIndex = i + 20;
			face[21].vert[i].colorIndex = 20;
		}
		for (i = 0; i < 20; i++) {
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = (i + 1) % 20;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = i + 20;
			face[i].vert[3].vertIndex = (i + 1) % 20 + 20;
			face[i].vert[0].colorIndex = 19;
			face[i].vert[1].colorIndex = 19;
			face[i].vert[2].colorIndex = 20;
			face[i].vert[3].colorIndex = 20;
		}
		for (i = 5; i < 15; i++) {
			face[i].vert[0].colorIndex = (i - 5) + 23;
			face[i].vert[1].colorIndex = (i - 5) + 22;
			face[i].vert[2].colorIndex = (i - 5) + 22;
			face[i].vert[3].colorIndex = (i - 5) + 23;
		}
		for (i = 0; i < 5; i++) {
			face[i].vert[0].colorIndex = 27 - i - 1;
			face[i].vert[1].colorIndex = 27 - i;
			face[i].vert[2].colorIndex = 27 - i;
			face[i].vert[3].colorIndex = 27 - i - 1;
		}
		for (i = 15; i < 20; i++) {
			face[i].vert[0].colorIndex = 47 - i - 1;
			face[i].vert[1].colorIndex = 47 - i;
			face[i].vert[2].colorIndex = 47 - i;
			face[i].vert[3].colorIndex = 47 - i - 1;
		}
	}

}

void Mesh::CreateFanBlade(float length, float height) {

	int i;

	numVerts = 16;
	pt = new Point3[numVerts];
	float low1 = 0.05;
	float thickness = 0.2;
	float delta1 = (height - low1) / 6;
	float delta2 = (height - thickness) / 6;

	for (i = 0; i < 7; i++) {
		pt[i].set(length * cos(i * 4 * DEG2RAD), height - delta1 * i, length*sin(i * 4 * DEG2RAD));
		pt[i + 7].set(length * cos(i * 4 * DEG2RAD), height - thickness - delta2 * i, length*sin(i * 4 * DEG2RAD));
	}
	pt[14].set(0, 0, 0);
	pt[15].set(0, height, 0);


	numFaces = 10;
	face = new Face[numFaces];

	face[0].nVerts = 9;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[8].vertIndex = 14;
	face[0].vert[7].vertIndex = 15;
	face[0].vert[6].vertIndex = 0;
	face[0].vert[5].vertIndex = 1;
	face[0].vert[4].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	face[0].vert[2].vertIndex = 4;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[0].vertIndex = 6;
	for (int j = 0; j < face[0].nVerts; j++)
		face[0].vert[j].colorIndex = 1;


	face[1].nVerts = 9;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 14;
	face[1].vert[1].vertIndex = 15;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 8;
	face[1].vert[4].vertIndex = 9;
	face[1].vert[5].vertIndex = 10;
	face[1].vert[6].vertIndex = 11;
	face[1].vert[7].vertIndex = 12;
	face[1].vert[8].vertIndex = 13;
	for (int j = 0; j < face[1].nVerts; j++)
		face[1].vert[j].colorIndex = 1;

	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 15;
	face[2].vert[1].vertIndex = 0;
	face[2].vert[2].vertIndex = 7;
	for (int j = 0; j < face[2].nVerts; j++)
		face[2].vert[j].colorIndex = 1;

	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 14;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 13;
	for (int j = 0; j < face[3].nVerts; j++)
		face[3].vert[j].colorIndex = 1;

	for (i = 4; i < numFaces; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = (i - 4);
		face[i].vert[1].vertIndex = (i - 4) + 1;
		face[i].vert[2].vertIndex = (i - 4) + 8;
		face[i].vert[3].vertIndex = (i - 4) + 7;
		for (int j = 0; j < face[i].nVerts; j++)
			face[i].vert[j].colorIndex = 1;
	}
}

void Mesh::CreateOval(float radius1, float radius2, float radius3, float heightBot, float heightUp, float length, float delta) {
		int i;
		numVerts = 42;
		pt = new Point3[numVerts];
		float halfLength = length / 2;
		for (i = 0; i < 10; i++) {
			pt[i].set(radius1 * cos(i * 20 * DEG2RAD), heightBot, radius1*sin(i * 20 * DEG2RAD) + length); //Hình tròn dưới
			pt[i + 20].set(radius1 * cos(i * 20 * DEG2RAD), heightUp, radius3*sin(i * 20 * DEG2RAD) + length); //Hình tròn trên

			pt[i + 10].set(radius2 * cos((i * 20 + 180)* DEG2RAD), heightBot, radius2*sin((i * 20 + 180) * DEG2RAD) - 0.1); //Hình tròn dưới
			pt[i + 30].set(radius2 * cos((i * 20 + 180) * DEG2RAD), heightUp + delta, radius2*sin((i * 20 + 180) * DEG2RAD) - 0.1); //Hình tròn trên
		}

		numFaces = 22;
		face = new Face[numFaces];

		face[20].nVerts = 20;
		face[20].vert = new VertexID[face[20].nVerts];
		face[21].nVerts = 20;
		face[21].vert = new VertexID[face[21].nVerts];
		for (i = 0; i < 20; i++) {
			face[20].vert[i].vertIndex = i;
			face[20].vert[i].colorIndex = 1;
			face[21].vert[i].vertIndex = i + 20;
			face[21].vert[i].colorIndex = 1;
		}
		for (i = 0; i < 20; i++) {
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = (i + 1) % 20;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = i + 20;
			face[i].vert[3].vertIndex = (i + 1) % 20 + 20;
			for (int j = 0; j<face[i].nVerts; j++)
				face[i].vert[j].colorIndex = 1;
		}

	}

void Mesh::CreateFanNeck(float radius1, float radius2, float heightBot, float heightUp, float oldDelta, float newDelta) {
		int i;
		numVerts = 42;
		pt = new Point3[numVerts];
		for (i = 0; i < 20; i++) {
			pt[i].set(radius1 * cos(i * 18 * DEG2RAD), heightBot, radius1*sin(i * 18 * DEG2RAD) - oldDelta); //Hình tròn dưới
			pt[i + 20].set(radius2 * cos(i * 18 * DEG2RAD), heightUp, radius2*sin(i * 18 * DEG2RAD) - newDelta); //Hình tròn trên
		}

		numFaces = 22;
		face = new Face[numFaces];

		face[20].nVerts = 20;
		face[20].vert = new VertexID[face[20].nVerts];
		face[21].nVerts = 20;
		face[21].vert = new VertexID[face[21].nVerts];
		for (i = 0; i < 20; i++) {
			face[20].vert[i].vertIndex = i;
			face[20].vert[i].colorIndex = 1;
			face[21].vert[i].vertIndex = i + 20;
			face[21].vert[i].colorIndex = 1;
		}
		for (i = 0; i < 20; i++) {
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = (i + 1) % 20;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = i + 20;
			face[i].vert[3].vertIndex = (i + 1) % 20 + 20;
			for (int j = 0; j<face[i].nVerts; j++)
				face[i].vert[j].colorIndex = 1;
		}

}