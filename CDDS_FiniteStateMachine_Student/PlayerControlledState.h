#pragma once
#include "State.h"
#include "GameObject.h"
#include "Input.h"
#include "GameDefs.h"
//TUTORIAL CODE:
class PlayerControlledState : public State
{
public:
	PlayerControlledState();
	~PlayerControlledState();
	
	void onUpdate(GameObject* object, float deltaTime);
};
///////////////////////