#include "Camera.h"
#include <math.h>

Camera Camera;

Camera::Camera():freeCam(false)
{
}
void Camera::Init(int w,int h,float s)
{
	//Init with standard OGL values:
	Position = Vector3D(0.0,0.0,0.0);
	ViewDir  = Vector3D(0.0,0.0,-1.0);
	ViewDirChanged = false;
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
	//Screen
	width = w;
	height = h;
	//Step length
	speed = s;
}
void Camera::Look()
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.x, -Position.y, -Position.z );
}

void Camera::GetPosition(Vector3D *pos)
{
	*pos = Position;
}

void Camera::SetPosition(Vector3D pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = pos.z;
}

void Camera::GetRotated(Vector3D *rot)
{
	*rot = Vector3D(RotatedX,RotatedY,RotatedZ);
}

void Camera::Rotate(Vector3D v)
{
	RotatedX = v.x;
	RotatedY = v.y;
	RotatedZ = v.z;
	ViewDirChanged = true;
}

void Camera::Update(bool keys[],int mouseX,int mouseY, float tick)
{
	int middleX,middleY;
	float angle;

	// Move the camera's view by the mouse
	middleX = width  >> 1;
	middleY = height >> 1;

	if(keys[GLUT_KEY_F10])
		freeCam=!freeCam;

	if (freeCam){

		if(mouseY!=middleY)
		{
			angle = (middleY - mouseY);
			RotateX(angle*tick*3);
		}

		if(mouseX!=middleX)
		{
			angle = (middleX - mouseX);
			RotateY(angle*tick*3);
		}

		if(keys[GLUT_KEY_UP])		MoveForwards(-speed*tick);				
		if(keys[GLUT_KEY_DOWN])		MoveForwards( speed*tick);
		if(keys[GLUT_KEY_LEFT])		StrafeRight(-speed*tick);
		if(keys[GLUT_KEY_RIGHT])	StrafeRight( speed*tick);
	}
	else{
		if(mouseY!=middleY)
		{
			angle = (middleY - mouseY);
			RotateX(angle*tick*3);
		}
	}
}

void Camera::GetViewDir(void)
{
	Vector3D Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (RotatedY + 90.0) * PIdiv180);
	Step1.z = -sin( (RotatedY + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (RotatedX * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(RotatedX * PIdiv180);
	//Rotation around Z-axis not implemented, so:
	ViewDir = Step2;
}

void Camera::RotateX (GLfloat angle)
{
	RotatedX += angle;
	ViewDirChanged = true;
}

void Camera::RotateY (GLfloat angle)
{
	RotatedY += angle;
	ViewDirChanged = true;
}

void Camera::RotateZ (GLfloat angle)
{
	RotatedZ += angle;
	ViewDirChanged = true;
}

void Camera::MoveForwards( GLfloat distance )
{
	if (ViewDirChanged) GetViewDir();
	Vector3D MoveVector;
	MoveVector.x = ViewDir.x * -distance;
	MoveVector.y = ViewDir.y * -distance;
	MoveVector.z = ViewDir.z * -distance;
	Position.Add(MoveVector);
}

void Camera::StrafeRight ( GLfloat distance )
{
	if (ViewDirChanged) GetViewDir();
	Vector3D MoveVector;
	MoveVector.z = -ViewDir.x * -distance;
	MoveVector.y = 0.0;
	MoveVector.x = ViewDir.z * -distance;
	Position.Add(MoveVector);
}
