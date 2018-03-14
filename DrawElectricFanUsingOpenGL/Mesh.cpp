#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		48
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
{ 0.6f, 0.0f, 1.0f },{ 0.5f, 1.0f, 0.0f }, {0.65f, 1.0f, 0.28f}, { 0.0f, 0.48f, 0.8f} ,{0.0f, 0.3f, 0.5f},
{ 0.0f, 0.44f, 0.74f},{ 0.0f, 0.41f, 0.68f },{ 0.0f, 0.37f, 0.62f },{ 0.0f, 0.34f, 0.56f },
{ 0.61f, 0.79f, 0.09f},{ 0.58f, 0.76f, 0.09f },{ 0.56f, 0.72f, 0.08f },{ 0.53f, 0.69f, 0.08f },
{ 0.51f, 0.65f, 0.07f },{ 0.48f, 0.62f, 0.07f }, {0.12f, 0.6f, 0.26f}
};


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

			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

//Vẽ hình chóp cụ với 2 bán kính đáy, chiều cao, tooạ độ tâm đường tròn đáy và màu
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

//Hàm vẽ cánh quạt
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
		face[0].vert[j].colorIndex = 9 - j - 1;


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
		face[1].vert[j].colorIndex = j + 9;

	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 15;
	face[2].vert[1].vertIndex = 0;
	face[2].vert[2].vertIndex = 7;
	for (int j = 0; j < face[2].nVerts; j++)
		face[2].vert[j].colorIndex = 18;

	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 14;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 13;
	for (int j = 0; j < face[3].nVerts; j++)
		face[3].vert[j].colorIndex = 18;

	for (i = 4; i < numFaces; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = (i - 4);
		face[i].vert[1].vertIndex = (i - 4) + 1;
		face[i].vert[2].vertIndex = (i - 4) + 8;
		face[i].vert[3].vertIndex = (i - 4) + 7;
		for (int j = 0; j < face[i].nVerts; j++)
			face[i].vert[j].colorIndex = 18;
	}
}

/*
	Hàm CreateOval để vẽ một hình oval với bán kính 2 đầu là radius1, radius2.
	radius3 dùng đẻ để thay đổi bán kính cho một đường tròn trên.
	heightBot, heightUp là chiều cao bắt đầu của hình và chiều cao kết thúc của hình
	length là độ dài của phần giữa hình oval cần vẽ
	delta là khoảng lệch độ cao giữa 2 bên đầu oval
	color là tham số để tạo màu
*/

void Mesh::CreateOval(float radius1, float radius2, float radius3, float heightBot, float heightUp, float length, float delta, int color) {
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
		face[21].vert[i].vertIndex = i + 20;
	}
	for (i = 0; i < 20; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = (i + 1) % 20;
		face[i].vert[1].vertIndex = i;
		face[i].vert[2].vertIndex = i + 20;
		face[i].vert[3].vertIndex = (i + 1) % 20 + 20;
	}
	switch (color) {
	case 0: 
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 33;
			face[21].vert[i].colorIndex = 34;
			face[i].vert[0].colorIndex = 33;
			face[i].vert[1].colorIndex = 33;
			face[i].vert[2].colorIndex = 34;
			face[i].vert[3].colorIndex = 34;
		}
		break;
	case 1:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 46;
			face[21].vert[i].colorIndex = 45;
			face[i].vert[0].colorIndex = 46;
			face[i].vert[1].colorIndex = 46;
			face[i].vert[2].colorIndex = 45;
			face[i].vert[3].colorIndex = 45;
		}
		break;
	case 2:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 45;
			face[21].vert[i].colorIndex = 44;
			face[i].vert[0].colorIndex = 45;
			face[i].vert[1].colorIndex = 45;
			face[i].vert[2].colorIndex = 44;
			face[i].vert[3].colorIndex = 44;
		}
		break;
	case 3:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 44;
			face[21].vert[i].colorIndex = 43;
			face[i].vert[0].colorIndex = 44;
			face[i].vert[1].colorIndex = 44;
			face[i].vert[2].colorIndex = 43;
			face[i].vert[3].colorIndex = 43;
		}
		break;
	case 4:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 43;
			face[21].vert[i].colorIndex = 42;
			face[i].vert[0].colorIndex = 43;
			face[i].vert[1].colorIndex = 43;
			face[i].vert[2].colorIndex = 42;
			face[i].vert[3].colorIndex = 42;
		}
		break;
	case 5:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 42;
			face[21].vert[i].colorIndex = 41;
			face[i].vert[0].colorIndex = 42;
			face[i].vert[1].colorIndex = 42;
			face[i].vert[2].colorIndex = 41;
			face[i].vert[3].colorIndex = 41;
		}
		break;
	case 6:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 47;
			face[21].vert[i].colorIndex = 47;
			face[i].vert[0].colorIndex = 47;
			face[i].vert[1].colorIndex = 47;
			face[i].vert[2].colorIndex = 47;
			face[i].vert[3].colorIndex = 47;
		}
		break;
	}
}

/*
	Hàm CreateFanNeck để vẽ cổ quạt
	radius1, radius2 là bán kính hình tròn trên và dưới
	heightBot, heightUp là chiều cao bắt đầu và kết thúc của hình
	oldDelta, newDelta là 2 tham số về độ lệch của tâm hình tròn khỏi trục y
	color là tham số để tạo màu
*/

void Mesh::CreateFanNeck(float radius1, float radius2, float heightBot, float heightUp, float oldDelta, float newDelta, int color) {
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
		face[21].vert[i].vertIndex = i + 20;
	}
	for (i = 0; i < 20; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = (i + 1) % 20;
		face[i].vert[1].vertIndex = i;
		face[i].vert[2].vertIndex = i + 20;
		face[i].vert[3].vertIndex = (i + 1) % 20 + 20;
		
	}
	switch (color) {
	case 0:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 35;
			face[21].vert[i].colorIndex = 37;
			face[i].vert[0].colorIndex = 35;
			face[i].vert[1].colorIndex = 35;
			face[i].vert[2].colorIndex = 37;
			face[i].vert[3].colorIndex = 37;
		}
		break;
	case 1:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 37;
			face[21].vert[i].colorIndex = 38;
			face[i].vert[0].colorIndex = 37;
			face[i].vert[1].colorIndex = 37;
			face[i].vert[2].colorIndex = 38;
			face[i].vert[3].colorIndex = 38;
		}
		break;
	case 2:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 38;
			face[21].vert[i].colorIndex = 39;
			face[i].vert[0].colorIndex = 38;
			face[i].vert[1].colorIndex = 38;
			face[i].vert[2].colorIndex = 39;
			face[i].vert[3].colorIndex = 39;
		}
		break;
	case 3:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 39;
			face[21].vert[i].colorIndex = 40;
			face[i].vert[0].colorIndex = 39;
			face[i].vert[1].colorIndex = 39;
			face[i].vert[2].colorIndex = 40;
			face[i].vert[3].colorIndex = 40;
		}
		break;
	case 4:
		for (i = 0; i < 20; i++) {
			face[20].vert[i].colorIndex = 40;
			face[21].vert[i].colorIndex = 36;
			face[i].vert[0].colorIndex = 40;
			face[i].vert[1].colorIndex = 40;
			face[i].vert[2].colorIndex = 36;
			face[i].vert[3].colorIndex = 36;
		}
		break;
	}

}