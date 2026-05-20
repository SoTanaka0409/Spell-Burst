#pragma once

#include<list>
#include<vector>

#include"Object2D.h"


class ObjectManager
{
public:
	ObjectManager();

	~ObjectManager();

	void Draw();

	void Update();

public:

	 //2Dオブジェクト追加
	void AddObject(Object2D* object2D);

	//2dオブジェクトの全削除
	void DeleteAll2D();

	//削除する必要のあるオブジェクトがあれば削除する
	//note:全てのオブジェクトの更新が終わった後に呼び出す
	void DeleteAll2DIfNeeded();

	//指定したタグの2Dオブジェクト取得
	//note:該当するオブジェクトが複数ある場合、最初に見つかったオブジェクトを返す
	Object2D* GetObject2DByTag(Object2D::Tag2D tag);

	//指定したタグの2Dオブジェクトのリストを取得
	//note:該当するオブジェクトが複数ある場合、リストに入って全てのオブジェクトを返す
	std::vector<Object2D*>GetObject2DListByTag(Object2D::Tag2D tag);

private:
		
	std::list<Object2D*>mObject2DList;

};
