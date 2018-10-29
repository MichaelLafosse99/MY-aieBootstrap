#pragma once
#include "Condition.h"
#include "Vector2D.h"
#include "GameObject.h"

class WithinRangeCondition : public Condition
{
public:
	WithinRangeCondition(GameObject* target, float distance) : m_target(target), m_distance(distance) {}
	~WithinRangeCondition() {}
	bool test(GameObject* go) const
	{
		Vector2D target = m_target->getPosition();
		Vector2D pos = go->getPosition();
		Vector2D dist = { target.x - pos.x, target.y - pos.y };
		float length = sqrt(dist.x * dist.x + dist.y * dist.y);
		if (length < m_distance)
			return true;
		return false;
	}
protected:
	GameObject * m_target;
	float m_distance;
};