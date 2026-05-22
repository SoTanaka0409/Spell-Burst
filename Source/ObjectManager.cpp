#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include <algorithm>

ObjectManager::ObjectManager() : m_player2D(nullptr)
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update()
{
	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end(); itr++)
	{
		(*itr)->Update();
	}
	DeleteAll2DIfNeeded();
}

void ObjectManager::Draw()
{
	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end(); itr++)
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
	mObject2DList.push_back(object2D);
	if (object2D->GetTag() == Object2D::Tag2D_Player) {
		m_player2D = object2D;
	}
}

void ObjectManager::DeleteAll2D()
{
	m_player2D = nullptr;
	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end(); )
	{
		Object2D* temp = *itr;
		itr = mObject2DList.erase(itr);
		delete temp;
	}
}

void ObjectManager::DeleteAll2DIfNeeded()
{
	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end(); )
	{
		if ((*itr)->IsDeleteFlag())
		{
			if (*itr == m_player2D) m_player2D = nullptr;
			Object2D* temp = *itr;
			itr = mObject2DList.erase(itr);
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
	if (tag == Object2D::Tag2D_Player && m_player2D != nullptr && !m_player2D->IsDeleteFlag()) {
		return m_player2D;
	}

	auto itr = std::find_if(
		mObject2DList.begin(),
		mObject2DList.end(),
		[&](Object2D* obj) { return obj->GetTag() == tag; }
	);

	if (itr != mObject2DList.end())
	{
		return (*itr);
	}
	return nullptr;
}

std::vector<Object2D*> ObjectManager::GetObject2DListByTag(Object2D::Tag2D tag)
{
	std::vector<Object2D*> ret;
	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end(); itr++)
	{
		if ((*itr)->GetTag() == tag)
		{
			ret.push_back(*itr);
		}
	}
	return ret;
}