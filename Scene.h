
#pragma once

#include "ModelOBJ.h"

#define SIZE		50.0f
#define AI_PLAYERS		2

class Camera;
class Player;

class Scene  
{
public:
	Scene();
	virtual ~Scene();

	void Logic(float tick, bool keys[]);
	void Render(float tick);
	bool Init();

private:
	ModelOBJ *House;
	Player* player;
	Player* aiPlayers[AI_PLAYERS];
};

