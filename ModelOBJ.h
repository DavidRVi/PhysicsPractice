#pragma once

#include "CollisionEngine.h"
#include "glm.h"
#include "Vector3D.h"

class ModelOBJ
{
public:
	ModelOBJ();
	~ModelOBJ();

	bool Load(char *filename, bool addForCollision=false);
	void AddToCollisionEngine();
	void UpdateTriangleBuffer();
	void Scale(float factor);
	void Render();
	void SetPosition(float x, float y, float z);
	void SetOrientation(float angX, float angY, float angZ);

private:
	GLMmodel *model;
	std::vector<mvc::Triangle> triangles;
	Vector3D position;
	Vector3D orientation;
};
