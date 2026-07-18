#include "Master.h"
#include "ObjectManager.h"
#include "ColliderManager.h"
#include <algorithm>

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update()
{
	for (auto& obj : object_2d_list_)
	{
		obj->Update();
	}
	DeleteAll2DIfNeeded();
}

void ObjectManager::Draw()
{
	for (auto& obj : object_2d_list_)
	{
		if (obj->IsDrawFlag())
		{
			obj->Draw();
		}
	}
}

void ObjectManager::AddObject(std::shared_ptr<Object2D> object2D)
{
	if (!object2D)
	{
		return;
	}

	object_2d_list_.push_back(object2D);

	if (object2D->GetTag() == Object2D::kTag2dPlayer)
	{
		player_2d_ = object2D;
	}
}

void ObjectManager::DeleteAll2D()
{
	player_2d_.reset();
	object_2d_list_.clear();
}

void ObjectManager::DeleteAll2DIfNeeded()
{
	object_2d_list_.remove_if([this](std::shared_ptr<Object2D>& obj)
		{
			if (obj && obj->IsDeleteFlag())
			{
				if (player_2d_.lock() == obj) player_2d_.reset();
				return true;
			}
			return false;
		});
}

std::shared_ptr<Object2D> ObjectManager::GetObject2DByTag(Object2D::Tag2D tag)
{
	if (tag == Object2D::kTag2dPlayer)
	{
		if (auto p = player_2d_.lock())
		{
			if (!p->IsDeleteFlag()) return p;
		}
	}

	auto itr = std::find_if(
		object_2d_list_.begin(),
		object_2d_list_.end(),
		[&](const std::shared_ptr<Object2D>& obj) { return obj->GetTag() == tag; }
	);

	if (itr != object_2d_list_.end())
	{
		return (*itr);
	}
	return nullptr;
}

std::vector<std::shared_ptr<Object2D>> ObjectManager::GetObject2DListByTag(Object2D::Tag2D tag)
{
	std::vector<std::shared_ptr<Object2D>> ret;

	for (auto& obj : object_2d_list_)
	{
		if (obj->GetTag() == tag)
		{
			ret.push_back(obj);
		}
	}
	return ret;
}
