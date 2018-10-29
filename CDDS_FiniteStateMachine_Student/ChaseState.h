#pragma once
#include "State.h"
#include "Vector2D.h"
#include <vector>
#include "GameObject.h"
class GameObject;

class ChaseState : public State
{
public:
	ChaseState();
	~ChaseState();

	void onUpdate(GameObject* object, float dt);

	void setTarget(GameObject* target) { m_target = target; }

private:
	GameObject * m_target;
};