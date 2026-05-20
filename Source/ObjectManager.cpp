#include"ObjectManager.h"
#include"Master.h"
#include"ColliderManager.h"
#include<algorithm>

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

//更新
void ObjectManager::Update()
{
	for (std::list<Object2D*>::iterator itr = mObject2DList.begin(); itr != mObject2DList.end(); itr++)
	{
		(*itr)->Update();
	}

	//更新が終わったら不要なオブジェクトを削除
	DeleteAll2DIfNeeded();
}

//描画
void ObjectManager::Draw()
{
	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end(); itr++)
	{
		if ((*itr)->IsDrawFlag() == true)
		{
			(*itr)->Draw();
		}
	}
}

//2Dオブジェクトの追加
void ObjectManager::AddObject(Object2D* object2D)
{
	mObject2DList.push_back(object2D);
}

//2Dオブジェクトの全削除
void ObjectManager::DeleteAll2D()
{
	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end();)
	{
		Object2D* temp = *itr;

		//リストから削除
		itr = mObject2DList.erase(itr);

		//オブジェクトそのものを削除
		delete temp;
		temp = nullptr;
	}
}

//削除する必要のあるオブジェクトがあれば削除する
void ObjectManager::DeleteAll2DIfNeeded()
{
	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end();)
	{
		if ((*itr)->IsDeleteFlag() == true)
		{
			Object2D* temp = *itr;

			//リストから削除
			itr = mObject2DList.erase(itr);

			//オブジェクトそのものを削除
			delete temp;
			temp = nullptr;
		}
		else
		{
			//次の要素へ進める
			itr++;
		}
	}
}

//指定したタグの2Dオブジェクト取得
Object2D* ObjectManager::GetObject2DByTag(Object2D::Tag2D tag)
{
	auto itr = std::find_if(
		mObject2DList.begin(),
		mObject2DList.end(),
		[&](Object2D* obj) {return obj->GetTag() == tag; }
	);

	if (itr != mObject2DList.end())
	{
		return (*itr);
	}
	return nullptr;
}

//指定したタグの2Dオブジェクトのリストを取得
std::vector<Object2D*>ObjectManager::GetObject2DListByTag(Object2D::Tag2D tag)
{
	std::vector<Object2D*>ret;

	for (auto itr = mObject2DList.begin(); itr != mObject2DList.end(); itr++)
	{
		if ((*itr)->GetTag() == tag)
		{
			ret.push_back(*itr);
		}
	}

	return ret;
}
