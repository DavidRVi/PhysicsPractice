
#include "Scene.h"
#include "CollisionEngine.h"
#include "Player.h"
#include "gl/glut.h"
#include <string.h>
#include <math.h>

Scene::Scene() {}

Scene::~Scene(){
	delete House;
	delete player;
	for(int i=0; i< AI_PLAYERS; ++i){
		delete aiPlayers[i];
	}
}

bool Scene::Init()
{
	// create the player and the AI players
	player = new Player(false);
	for(int i=0; i< AI_PLAYERS; ++i){
		aiPlayers[i] = new Player(true);
	}

	House = new ModelOBJ();
	if(!House) return false;
	
	House->Load("models/EdificiColisions.obj",true);
	House->Scale(20.0f);

	return true;
}

void Scene::Logic(float tick, bool keys[])
{
	player->logicTick(tick,keys);
	for(int i=0; i< AI_PLAYERS; ++i){
		aiPlayers[i]->logicTick(tick,keys);
	}
}

void Scene::Render(float tick)
{
	player->renderTick(tick);
	for(int i=0; i< AI_PLAYERS; ++i){
		aiPlayers[i]->renderTick(tick);
	}

	House->Render();
}
