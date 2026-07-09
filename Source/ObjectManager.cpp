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
	// 驕ｽ繝ｻ蟲・ｹ晏生繝ｻ郢ｧ・ｹfor郢晢ｽｫ郢晢ｽｼ郢晏干縲帝ａ・｡雋取鱒竊楢怦・ｨ郢ｧ・ｪ郢晄じ縺夂ｹｧ・ｧ郢ｧ・ｯ郢晏現・定ｭ厄ｽｴ隴・ｽｰ
	for (auto& obj : object_2d_list_)
	{
		obj->Update();
	}
	DeleteAll2DIfNeeded();
}

void ObjectManager::Draw()
{
	// 驕ｽ繝ｻ蟲・ｹ晏生繝ｻ郢ｧ・ｹfor郢晢ｽｫ郢晢ｽｼ郢晏干縲定ｬ蜀怜愛郢晁ｼ釆帷ｹｧ・ｰ邵ｺ讙趣ｽｫ荵昶夢邵ｺ・ｦ邵ｺ繝ｻ・狗ｹｧ繧・・郢ｧ蜻育ｷ帝包ｽｻ
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
	object_2d_list_.push_back(object2D);
	if (object2D->GetTag() == Object2D::kTag2dPlayer) {
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
	object_2d_list_.remove_if([this](std::shared_ptr<Object2D>& obj) {
		if (obj && obj->IsDeleteFlag()) {
			if (player_2d_.lock() == obj) player_2d_.reset();
			return true;
		}
		return false;
	});
}

std::shared_ptr<Object2D> ObjectManager::GetObject2DByTag(Object2D::Tag2D tag_)
{
	if (tag_ == Object2D::kTag2dPlayer) {
		if (auto p = player_2d_.lock()) {
			if (!p->IsDeleteFlag()) return p;
		}
	}

	auto itr = std::find_if(
		object_2d_list_.begin(),
		object_2d_list_.end(),
		[&](const std::shared_ptr<Object2D>& obj) { return obj->GetTag() == tag_; }
	);

	if (itr != object_2d_list_.end())
	{
		return (*itr);
	}
	return nullptr;
}

std::vector<std::shared_ptr<Object2D>> ObjectManager::GetObject2DListByTag(Object2D::Tag2D tag_)
{
	std::vector<std::shared_ptr<Object2D>> ret;
	for (auto& obj : object_2d_list_)
	{
		if (obj->GetTag() == tag_)
		{
			ret.push_back(obj);
		}
	}
	return ret;
}

