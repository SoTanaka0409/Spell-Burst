#include"Scene.h"
#include"ObjectManager.h"
#include"Master.h"
#include"ColliderManager.h"

Scene::Scene()
{
	//オブジェクトマネージャーの生成
	mpObjectManager = new ObjectManager();
	mpColliderManager = new ColliderManager();
	
}

Scene::~Scene()
{
	
	
	
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->DeleteAll3D();
		delete mpObjectManager;
	}
	if (mpColliderManager != nullptr)
	{
		mpColliderManager->DeleteAllCollider();
		delete mpColliderManager;
		
	}

	
}
//描画wwwwwwwwwwwwww
void Scene::Draw()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Draw();
	}
	if (mpColliderManager != nullptr)
	{
		mpColliderManager->Draw();
	}
	
	
}
//更新
void Scene::Update()
{
	if (mpObjectManager != nullptr)
	{
		
		mpObjectManager->Update();
	}
	if (mpColliderManager != nullptr)
	{
		mpColliderManager->Update();
	}

}