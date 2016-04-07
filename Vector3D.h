
#pragma once

//3D Point/vector class

class Vector3D  
{
public:
	Vector3D();
	Vector3D(float X, float Y, float Z);
	virtual ~Vector3D();

	void Add(Vector3D v);

	float x, y, z;
};

