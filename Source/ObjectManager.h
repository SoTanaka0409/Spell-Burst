#pragma once
#include <list>
#include <vector>
#include "Object2D.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Draw();
	void Update();

	void AddObject(Object2D* object2D);
	void DeleteAll2D();
	void DeleteAll2DIfNeeded();

	Object2D* GetObject2DByTag(Object2D::Tag2D tag);
	std::vector<Object2D*> GetObject2DListByTag(Object2D::Tag2D tag);

	size_t GetObjectCount() const { return mObject2DList.size(); }
	const std::list<Object2D*>& GetObjectList() const { return mObject2DList; }

private:
	std::list<Object2D*> mObject2DList;
};
