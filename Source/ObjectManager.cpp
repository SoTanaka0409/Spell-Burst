#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include <algorithm>

ObjectManager::ObjectManager() : player_2d_(nullptr)
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update()
{
	// 範囲ベースforループで簡潔に全オブジェクトを更新
	for (auto* obj : object_2d_list_)
	{
		obj->Update();
	}
	DeleteAll2DIfNeeded();
}

void ObjectManager::Draw()
{
	// 範囲ベースforループで描画フラグが立っているものを描画
	for (auto* obj : object_2d_list_)
	{
		if (obj->IsDrawFlag())
		{
			obj->Draw();
		}
	}
}

void ObjectManager::AddObject(Object2D* object2D)
{
	object_2d_list_.push_back(object2D);
	if (object2D->GetTag() == Object2D::kTag2dPlayer) {
		player_2d_ = object2D;
	}
}

void ObjectManager::DeleteAll2D()
{
	player_2d_ = nullptr;
	// 範囲ベースforループでメモリを解放後、一括でクリア
	for (auto* obj : object_2d_list_) {
		delete obj;
	}
	object_2d_list_.clear();
}

void ObjectManager::DeleteAll2DIfNeeded()
{
	// std::list の remove_if を使用して、削除フラグを満たすオブジェクトを安全に削除
	object_2d_list_.remove_if([this](Object2D* obj) {
		if (obj != nullptr && obj->IsDeleteFlag()) {
			if (obj == player_2d_) player_2d_ = nullptr;
			delete obj;
			return true;
		}
		return false;
	});
}

Object2D* ObjectManager::GetObject2DByTag(Object2D::Tag2D tag_)
{
	if (tag_ == Object2D::kTag2dPlayer && player_2d_ != nullptr && !player_2d_->IsDeleteFlag()) {
		return player_2d_;
	}

	auto itr = std::find_if(
		object_2d_list_.begin(),
		object_2d_list_.end(),
		[&](Object2D* obj) { return obj->GetTag() == tag_; }
	);

	if (itr != object_2d_list_.end())
	{
		return (*itr);
	}
	return nullptr;
}

std::vector<Object2D*> ObjectManager::GetObject2DListByTag(Object2D::Tag2D tag_)
{
	std::vector<Object2D*> ret;
	// 範囲ベースforループで簡潔に検索
	for (auto* obj : object_2d_list_)
	{
		if (obj->GetTag() == tag_)
		{
			ret.push_back(obj);
		}
	}
	return ret;
}