#pragma once

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

#include "CollisionEngine.h" 
#include "Player.h" 
#include "gl/glut.h"
#include "Vector3D.h" 
#include "Utilities.h"

#define PIdiv180	0.0174529252

class Camera : public SingletonBase<Camera> 
{
private:
	Vector3D Position;
	Vector3D ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;

	int width,height;
	float speed;
	bool freeCam;

	void GetViewDir (void);

public:
	Camera();						
	void Init(int w,int h,float s);	//necessary for input updates
	void Look();					//glRotates and a glTranslate command
	
	void Rotate	(Vector3D Angles);
	void Update (bool keys[255], int mouseX, int mouseY, float tick);

	void GetPosition(Vector3D *pos);
	void GetRotated(Vector3D *rot);
	void SetPosition(Vector3D pos);
	void MoveForwards(GLfloat distance);
	bool IsFreeCam(){return freeCam;}

private:
	void RotateX(GLfloat angle);
	void RotateY(GLfloat angle);
	void RotateZ(GLfloat angle);

	void StrafeRight(GLfloat distance);
};

