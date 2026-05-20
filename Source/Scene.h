#pragma once
#include "DxLib.h"

// Forward declarations
class ObjectManager;
class ColliderManager;

// Base class for all Scenes
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Initialize() = 0;
	virtual void Update();
	virtual void Draw();
	virtual void Finalize() = 0;

	ObjectManager* GetObjectManager() { return mpObjectManager; }
	ColliderManager* GetCollisionManager() { return mpColliderManager; }
	
private:
	ObjectManager* mpObjectManager;
	ColliderManager* mpColliderManager;
};