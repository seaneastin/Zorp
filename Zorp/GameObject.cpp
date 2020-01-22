#include "pch.h"
#include "GameObject.h"
#include "GameDefines.h"


GameObject::GameObject()
{
}

GameObject::GameObject(Point2D position)
{
}


GameObject::~GameObject()
{
}

bool GameObject::compare(const GameObject* p1, const GameObject* p2)
{
	return p1->m_priority < p2->m_priority;
}
