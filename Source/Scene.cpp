#include "Scene.h"
#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include "DebugLog.h"

Scene::Scene()
{
	// Create object manager
	mpObjectManager = new ObjectManager();
	mpColliderManager = new ColliderManager();
}

Scene::~Scene()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->DeleteAll2D();
		delete mpObjectManager;
	}
	if (mpColliderManager != nullptr)
	{
		mpColliderManager->DeleteAllCollider();
		delete mpColliderManager;
	}
}

// Draw
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

// Update
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