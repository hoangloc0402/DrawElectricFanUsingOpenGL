#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		21
#define DEG2RAD (3.14159f/180.0f)

float	ColorArr[COLORNUM][3] = { { 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0,  0.0, 1.0 },
{ 1.0, 1.0,  0.0 },{ 1.0, 0.0, 1.0 },{ 0.0, 1.0, 1.0 },
{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },{ 0.9,  0.9, 0.9 },
{ 1.0, 0.5,  0.5 },{ 0.5, 1.0, 0.5 },{ 0.5, 0.5, 1.0 },
{ 0.0, 0.0, 0.0 },{ 0.7, 0.2, 0.6 },{ 0.4, 1.0, 0.1 },
{ 1.0, 0.5, 0.5 },{ 0.2, 0.2, 0.9 },{ 0.2, 1.0, 1.0 } ,
{ 1.0, 0.5, 0.3 },{ 0.9, 1.0, 0.3 },{ 0.8, 0.5, 0.7 } };


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

void Mesh::CreateConical(float radius1, float radius2  , float height, float y) {
	int i;
	numVerts = 42;
	pt = new Point3[numVerts];
	for (i = 0; i < 20; i++) {
		pt[i].set(radius1 * cos(i * 18 * DEG2RAD), y, radius1*sin(i * 18 * DEG2RAD)); //Hình tròn dưới
		pt[i + 20].set(radius2 * cos(i * 18 * DEG2RAD), y + height, radius2*sin(i * 18 * DEG2RAD)); //Hình tròn trên
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
	for (int j = 0; j<face[0].nVerts; j++)
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
	for (int j = 0; j<face[1].nVerts; j++)
		face[1].vert[j].colorIndex = 1;

	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 15;
	face[2].vert[1].vertIndex = 0;
	face[2].vert[2].vertIndex = 7;
	for (int j = 0; j<face[2].nVerts; j++)
		face[2].vert[j].colorIndex = 1;

	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 14;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 13;
	for (int j = 0; j<face[3].nVerts; j++)
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