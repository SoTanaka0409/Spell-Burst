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
<<<<<<< HEAD
	for (auto itr = object2DList.begin(); itr != object2DList.end(); itr++)
=======
	// 範囲ベースforループで簡潔に全オブジェクトを更新
	for (auto* obj : mObject2DList)
>>>>>>> main
	{
		obj->Update();
	}
	DeleteAll2DIfNeeded();
}

void ObjectManager::Draw()
{
<<<<<<< HEAD
	for (auto itr = object2DList.begin(); itr != object2DList.end(); itr++)
=======
	// 範囲ベースforループで描画フラグが立っているものを描画
	for (auto* obj : mObject2DList)
>>>>>>> main
	{
		if (obj->IsDrawFlag())
		{
			obj->Draw();
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
<<<<<<< HEAD
	player2D = nullptr;
	for (auto itr = object2DList.begin(); itr != object2DList.end(); )
	{
		Object2D* temp = *itr;
		itr = object2DList.erase(itr);
		delete temp;
=======
	m_player2D = nullptr;
	// 範囲ベースforループでメモリを解放後、一括でクリア
	for (auto* obj : mObject2DList) {
		delete obj;
>>>>>>> main
	}
	mObject2DList.clear();
}

void ObjectManager::DeleteAll2DIfNeeded()
{
<<<<<<< HEAD
	for (auto itr = object2DList.begin(); itr != object2DList.end(); )
	{
		if ((*itr)->IsDeleteFlag())
		{
			if (*itr == player2D) player2D = nullptr;
			Object2D* temp = *itr;
			itr = object2DList.erase(itr);
			delete temp;
=======
	// std::list の remove_if を使用して、削除フラグを満たすオブジェクトを安全に削除
	mObject2DList.remove_if([this](Object2D* obj) {
		if (obj != nullptr && obj->IsDeleteFlag()) {
			if (obj == m_player2D) m_player2D = nullptr;
			delete obj;
			return true;
>>>>>>> main
		}
		return false;
	});
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
<<<<<<< HEAD
	for (auto itr = object2DList.begin(); itr != object2DList.end(); itr++)
=======
	// 範囲ベースforループで簡潔に検索
	for (auto* obj : mObject2DList)
>>>>>>> main
	{
		if (obj->GetTag() == tag)
		{
			ret.push_back(obj);
		}
	}
	return ret;
}