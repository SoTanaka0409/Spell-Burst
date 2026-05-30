#pragma once
#include <string>
#include "vector"
#include "Dxlib.h"
#include "Collider.h"

class Object2D
{
public:
	enum Tag2D
	{
		None2D = 0,
		Tag2D_Player = 1,
		Tag2D_Enemy = 2,
		Tag2D_PlayerBullet=3,
		Tag2D_EnemyBullet=4,
	};

public:
	Object2D(VECTOR initPos);

	virtual ~Object2D();

	virtual void Update();

	virtual void Draw();

public:// getter, setter //
	void SetPosition(VECTOR pos) { mvPosition = pos; };
	VECTOR GetPosition() { return mvPosition; }

	void SetRotation(VECTOR rot) { mvRotation = rot; }
	VECTOR GETRotation() { return mvRotation; }

	void SetDeleteFlag(bool flag) { mbDeleteFlag = flag; }
	bool IsDeleteFlag() { return mbDeleteFlag; }

	void SetDrawFlag(bool flag) { mbDrawFlag = flag; } // Enemy deletion flag setting
	bool IsDrawFlag() { return mbDrawFlag; }          // Creating enemy deletion flags

	// tag
	void SetTag(Tag2D tag) { mnTag = tag; }
	Tag2D GetTag() { return mnTag; }

	virtual void OnEnter(Collider* collider, Collider* check);
	virtual void OnTrigger(Collider* collider, Collider* check);
	virtual void OnExit(Collider* collider, Collider* check);

protected:
	VECTOR mvPosition;  // coordinate
	VECTOR mvRotation;   // rotate

private:
	bool mbDeleteFlag;  // Deletion flag
	Tag2D mnTag;   // tag
	bool mbDrawFlag;// drawing flag


};
