#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include <algorithm>

ObjectManager::ObjectManager() : player2D(nullptr)
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update()
{
	for (auto itr = object2DList.begin(); itr != object2DList.end(); itr++)
	{
		(*itr)->Update();
	}
	DeleteAll2DIfNeeded();
}

void ObjectManager::Draw()
{
	for (auto itr = object2DList.begin(); itr != object2DList.end(); itr++)
	{
		bool isDraw = (*itr)->IsDrawFlag();
		if (isDraw)
		{
			(*itr)->Draw();
		}
	}
}

void ObjectManager::AddObject(Object2D* object2D)
{
	object2DList.push_back(object2D);
	if (object2D->GetTag() == Object2D::Tag2D_Player) {
		player2D = object2D;
	}
}

void ObjectManager::DeleteAll2D()
{
	player2D = nullptr;
	for (auto itr = object2DList.begin(); itr != object2DList.end(); )
	{
		Object2D* temp = *itr;
		itr = object2DList.erase(itr);
		delete temp;
	}
}

void ObjectManager::DeleteAll2DIfNeeded()
{
	for (auto itr = object2DList.begin(); itr != object2DList.end(); )
	{
		if ((*itr)->IsDeleteFlag())
		{
			if (*itr == player2D) player2D = nullptr;
			Object2D* temp = *itr;
			itr = object2DList.erase(itr);
			delete temp;
		}
		else
		{
			itr++;
		}
	}
}

Object2D* ObjectManager::GetObject2DByTag(Object2D::Tag2D tag)
{
	if (tag == Object2D::Tag2D_Player && player2D != nullptr && !player2D->IsDeleteFlag()) {
		return player2D;
	}

	auto itr = std::find_if(
		object2DList.begin(),
		object2DList.end(),
		[&](Object2D* obj) { return obj->GetTag() == tag; }
	);

	if (itr != object2DList.end())
	{
		return (*itr);
	}
	return nullptr;
}

std::vector<Object2D*> ObjectManager::GetObject2DListByTag(Object2D::Tag2D tag)
{
	std::vector<Object2D*> ret;
	for (auto itr = object2DList.begin(); itr != object2DList.end(); itr++)
	{
		if ((*itr)->GetTag() == tag)
		{
			ret.push_back(*itr);
		}
	}
	return ret;
}