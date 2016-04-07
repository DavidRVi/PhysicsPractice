#include "CollisionEngine.h"
#include <iostream>
#include "gl/glut.h"
#include "math.h"
#include "Player.h"
#include "Camera.h"

#define PI 3.141592654f

Player::Player(bool AIcontrolled):
	body(Point(0,1.12,1),0.3f),
	angleY(PI*1.7f),
	angleYSpeed(2),
	dir(0,0,1),
	vel(7),
	velY(0),
	gravity(-9.8f),
	aiUpdateTimer(0),
	aiDecision(1),
	aiControlled(AIcontrolled),
	model(0){

	// setup some special parameters for AI controlled characters
	if(AIcontrolled){
		// load the model, only for AI controlled characters
		model = new ModelOBJ();
		model->Load("models/al.obj", false);
		model->Scale(1.0f);

		// move the center to the left so that it is separated from the user controlled one
		body.c.x=-2;
	}

	// add the player sphere to the collision system to enable interaction with others
	CollisionManager::get()->addSphere(body);
}

Player::~Player(void){
	delete model;
}

void Player::logicTick(float tick, bool keys[]){
	updateAI(tick, keys);

	Point prevPos = body.c;

	//add gravity to our current position
	velY += tick*gravity;
	body.c.y += tick*velY;

	//process the user keyboard input for rotation and compute rotation around the Y axis
	if(aiControls[left])
		angleY += angleYSpeed*tick;
	else if(aiControls[right])
		angleY -= angleYSpeed*tick;

	//update rotation variables
	dir.x = cos(angleY);
	dir.z = -sin(angleY);

	//process movement
	if(aiControls[up])
		body.c = body.c + tick*dir*vel;
	if(aiControls[down])
		body.c = body.c - tick*dir*vel;


	////////////////////////////////
	// AREA DE TRABAJO
	////////////////////////////////

	//do the sphere vs sphere sliding
	CollisionManager::get()->addSphere(body);
	Sphere res(Point(0.0f, 0.0f, 0.0f), 0.0f);
	if (CollisionManager::get()->testSphereSphereSoup(body, res))
	{
		Vector d = res.c - body.c;
		Vector dist(d);
		d.normalilze();

		float delta = -(Dot(d, dist) - body.r - res.r);
		body.c = body.c + delta*d;
	}
	//do the environment slide
	
	for (int i = 0; i < 3; ++i)
	{
		if (vel != 0.0f)
		{
			Triangle t;
			Point intersection;
			if (CollisionManager::get()->testSphereTriangleSoup(body, intersection, t))
			{
				//body.c = prevPos;
				Vector res = body.c - intersection;
				float delta = body.r - Dot(res, t.normal);
				body.c = body.c + delta * t.normal;
			}


		}
	}
	
	
	//check for ceiling
	if (velY > 0.0f)
	{
		Point intersection;
		Point prevPosBase = prevPos;
		Point posBase = body.c + Point(0.0f, 1.0f, 0.0f);
		if (CollisionManager::get()->testSegmentTriangleSoup(prevPosBase, posBase, intersection))
		{
			body.c.y = prevPos.y;
			velY = 0.0f;
		}
	}
	//check for ground and update position if needed
	else if (velY < 0.0f)
	{
		Point intersection;
		Point prevPosBase = prevPos;
		Point posBase = body.c - Point(0.0f, 1.0f, 0.0f);
		if (CollisionManager::get()->testSegmentTriangleSoup(prevPosBase, posBase, intersection))
		{
			body.c.y = intersection.y + 1.0f;
			velY = 0.0f;
		}
	}

	if (aiControls[jump] && velY == 0.0f)
		velY = 5.0f;


		
	////////////////////////////////
	// FIN AREA DE TRABAJO
	////////////////////////////////

	// now update the camera if not an AI player
	if (!aiControlled){
		if (!Camera::get()->IsFreeCam()){
			Camera::get()->SetPosition(Vector3D(body.c.x,body.c.y+0.25,body.c.z));
			Vector3D rot;
			Camera::get()->GetRotated(&rot);
			Camera::get()->Rotate(Vector3D(rot.x,-dir.getAngleY()-90,0));
		}
	}
}


void Player::renderTick(float tick){
	
	// only render those characters AI contolled
	if(aiControlled){
		if(aiControls[down])
			model->SetOrientation(0,-dir.getAngleY()+270,0);
		else
			model->SetOrientation(0,-dir.getAngleY()+90,0);
		model->SetPosition(body.c.x, body.c.y, body.c.z);
		model->Render();
	}
}


void Player::updateAI(float tick, bool keys[]){

	// first reset the controls
	for(int i=0;i<maxDirs; ++i){
		aiControls[i]=false;
	}

	if(aiControlled){
		aiUpdateTimer-=tick;
		if(aiUpdateTimer<0){
			aiUpdateTimer=1+rand()%5;
			aiDecision = rand()%100;
		}
		else if(aiDecision<20){
			aiControls[up]=true;
			aiControls[jump]=true;
		}
		else if(aiDecision<40){
			aiControls[up]=true;
		}
		else if(aiDecision<60){
			aiControls[right]=true;
			aiControls[up]=true;
		}
		else if(aiDecision<80){
			aiControls[left]=true;
			aiControls[up]=true;
		}
		else{
			aiControls[down]=true;
		}
	}
	else{
		if(keys[GLUT_KEY_LEFT])
			aiControls[left]=true;
		if(keys[GLUT_KEY_RIGHT])
			aiControls[right]=true;
		if(keys[GLUT_KEY_UP])
			aiControls[up]=true;
		if(keys[GLUT_KEY_DOWN])
			aiControls[down]=true;
		if(keys[GLUT_KEY_END])
			aiControls[jump]=true;
	}
}