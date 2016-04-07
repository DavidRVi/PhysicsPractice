#pragma once

#include "ModelOBJ.h"

using namespace mvc;

// Our character
class Player
{
public:
	enum{
		up=0,
		down,
		left,
		right,
		jump,
		maxDirs
	}pad;

	// Default constructor, initializes all constants
	Player(bool AIcontrolled);

	// Empty default destructor
	~Player(void);

	// Function responsible for updating the character position
	void logicTick(float tick, bool keys[]);

	// Function responsible for rendering our character
	void renderTick(float tick);

	// Function responsible for updating a player AI
	void Player::updateAI(float tick, bool keys[]);

	// Character body as an sphere
	Sphere body;

	// Direction the character is facing
	Vector dir;

	// Rotation in the Y axis, used to compute dir
	float angleY;

	// Constant angular velocity in the Y axis, affects angleY
	const float angleYSpeed;

	// Velocity in the Y axis
	float velY;

	// Velocity
	float vel;

	// Constant acceleration in the Y axis
	const float gravity;

	// Whether this is an AI controlled player
	bool aiControlled;

	// AI controls
	bool aiControls[maxDirs];

	// AI Update timer
	float aiUpdateTimer;

	// AI decision
	int aiDecision;

	// The character model
	ModelOBJ *model;
};
