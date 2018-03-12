#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID {
public:
	int		vertIndex;
	int		colorIndex;
};

class Face {
public:
	int		nVerts;
	VertexID*	vert;

	Face() {
		nVerts = 0;
		vert = NULL;
	}
	~Face() {
		if (vert != NULL) {
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh {
public:
	int		numVerts;
	Point3*		pt;

	int		numFaces;
	Face*		face;
public:
	Mesh() {
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh() {
		if (pt != NULL) delete[] pt;
		if (face != NULL) delete[] face;
		numVerts = 0;
		numFaces = 0;
	}

	void DrawWireframe();
	void DrawColor();
	void CreateFanBlade(float length, float height);
	void CreateConical(float radius1, float radius2, float height, float y, int color);
	void CreateOval(float radius1, float radius2, float radius3, float heightBot, float heightUp, float length, float delta);
	void CreateFanNeck(float radius1, float radius2, float heightBot, float heightUp, float oldDelta, float newDelta);
};

#endif
