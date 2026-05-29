#pragma once
#include <string>
#include "vector"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Collider.h"

// 画面上に描画・配置されるすべてのゲーム内オブジェクトの基底クラス
class Object2D
{
public:
	enum Tag2D
	{
		None2D = 0,
		Tag2D_Player = 1,
		Tag2D_Enemy = 2,
		Tag2D_PlayerBullet = 3,
		Tag2D_EnemyBullet = 4,
		tag2D_BarierEne = 5,
		tag2D_BarierPla = 6,
	};

public:
	Object2D(VECTOR initPos);
	virtual ~Object2D();

	// [入力] なし
	// [出力] なし
	// [副作用] オブジェクトの位置や状態をフレームごとに更新する（派生先で実装）
	virtual void Update();

	// [入力] なし
	// [出力] なし
	// [副作用] オブジェクトのグラフィックを画面に描画する（派生先で実装）
	virtual void Draw();

	void SetPosition(VECTOR pos) { mvPosition = pos; };
	VECTOR GetPosition() { return mvPosition; }

	void SetRotation(VECTOR rot) { mvRotation = rot; }
	VECTOR GETRotation() { return mvRotation; }

	void SetDeleteFlag(bool flag) { mbDeleteFlag = flag; }
	bool IsDeleteFlag() { return mbDeleteFlag; }

	void SetDrawFlag(bool flag) { mbDrawFlag = flag; }
	bool IsDrawFlag() { return mbDrawFlag; }
	void SetTag(Tag2D tag) { mnTag = tag; }
	Tag2D GetTag() { return mnTag; }

	// [入力] collider: 自身のコライダー, check: 相手のコライダー
	// [出力] なし
	// [副作用] コライダー同士が接触を開始した瞬間に呼び出されるイベントハンドラ
	virtual void OnEnter(Collider* collider, Collider* check);

	// [入力] collider: 自身のコライダー, check: 相手のコライダー
	// [出力] なし
	// [副作用] コライダー同士が接触している間に毎フレーム呼び出されるイベントハンドラ
	virtual void OnTrigger(Collider* collider, Collider* check);

	// [入力] collider: 自身のコライダー, check: 相手のコライダー
	// [出力] なし
	// [副作用] コライダー同士が離脱した瞬間に呼び出されるイベントハンドラ
	virtual void OnExit(Collider* collider, Collider* check);

protected:
	VECTOR mvPosition;
	VECTOR mvRotation;

private:
	bool mbDeleteFlag;
	Tag2D mnTag;
	bool mbDrawFlag;
};