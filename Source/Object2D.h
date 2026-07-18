#include "Vector2.h"
#pragma once
#include <string>
#include "vector"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Collider.h"

class Object2D
{
public:
	enum Tag2D
	{
		kNone2d = 0,
		kTag2dPlayer = 1,
		kTag2dEnemy = 2,
		kTag2dPlayerBullet = 3,
		kTag2dEnemyBullet = 4,
		kTag2dBarrierEnemy = 5,
		kTag2dBarrierPlayer = 6,
	};

public:
    Object2D(Vector2 initPos);
	virtual ~Object2D();

    /*
     */
    virtual void Update();

    /*
     */
    virtual void Draw();

	void SetPosition(Vector2 pos) { position_ = pos; };
	Vector2 GetPosition() { return position_; }

	void SetRotation(Vector2 rot) { rotation_ = rot; }
	Vector2 GetRotation() { return rotation_; }

	void SetDeleteFlag(bool flag) { delete_flag_ = flag; }
	bool IsDeleteFlag() { return delete_flag_; }

	void SetDrawFlag(bool flag) { draw_flag_ = flag; }
	bool IsDrawFlag() { return draw_flag_; }
	void SetTag(Tag2D tag) { tag_ = tag; }
	Tag2D GetTag() { return tag_; }

    /*
     */
    virtual void OnEnter(Collider* collider, Collider* check);

    /*
     */
    virtual void OnTrigger(Collider* collider, Collider* check);

    /*
     */
    virtual void OnExit(Collider* collider, Collider* check);

protected:
	Vector2 position_;
	Vector2 rotation_;

private:
	bool delete_flag_;
	Tag2D tag_;
	bool draw_flag_;
};
