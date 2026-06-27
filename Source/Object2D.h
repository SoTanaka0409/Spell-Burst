#include "Vector2.h"
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
		Tag2D_BarrierEnemy = 5,
		Tag2D_BarrierPlayer = 6,
	};

public:
	Object2D(Vector2 initPos);
	virtual ~Object2D();

	// [入力] なし
	// [出力] なし
	// [副作用] オブジェクトの位置や状態をフレームごとに更新する（派生先で実装）
	virtual void Update();

	// [入力] なし
	// [出力] なし
	// [副作用] オブジェクトのグラフィックを画面に描画する（派生先で実装）
	virtual void Draw();

	void SetPosition(Vector2 pos) { position = pos; };
	Vector2 GetPosition() { return position; }

	void SetRotation(Vector2 rot) { rotation = rot; }
	Vector2 GetRotation() { return rotation; }

	void SetDeleteFlag(bool flag) { deleteFlag = flag; }
	bool IsDeleteFlag() { return deleteFlag; }

	void SetDrawFlag(bool flag) { drawFlag = flag; }
	bool IsDrawFlag() { return drawFlag; }
	void SetTag(Tag2D tag) { tag = tag; }
	Tag2D GetTag() { return tag; }

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
	Vector2 position;
	Vector2 rotation;

private:
	bool deleteFlag;
	Tag2D tag;
	bool drawFlag;
};