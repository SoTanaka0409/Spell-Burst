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
		kNone2d = 0,
		kTag2dPlayer = 1,
		kTag2dEnemy = 2,
		kTag2dPlayerBullet = 3,
		kTag2dEnemyBullet = 4,
		kTag2dBarrierEnemy = 5,
		kTag2dBarrierPlayer = 6,
	};

public:
	Object2D(Vector2 init_pos);
	virtual ~Object2D();

	// [入力] なし
	// [出力] なし
	// [副作用] オブジェクトの位置や状態をフレームごとに更新する（派生先で実装）
	virtual void Update();

	// [入力] なし
	// [出力] なし
	// [副作用] オブジェクトのグラフィックを画面に描画する（派生先で実装）
	virtual void Draw();

	void SetPosition(Vector2 pos) { position_ = pos; };
	Vector2 GetPosition() { return position_; }

	void SetRotation(Vector2 rot) { rotation_ = rot; }
	Vector2 GetRotation() { return rotation_; }

	void SetDeleteFlag(bool flag) { delete_flag_ = flag; }
	bool IsDeleteFlag() { return delete_flag_; }

	void SetDrawFlag(bool flag) { draw_flag_ = flag; }
	bool IsDrawFlag() { return draw_flag_; }
	void SetTag(Tag2D tag_) { tag_ = tag_; }
	Tag2D GetTag() { return tag_; }

	// [入力] collider_: 自身のコライダー, check: 相手のコライダー
	// [出力] なし
	// [副作用] コライダー同士が接触を開始した瞬間に呼び出されるイベントハンドラ
	virtual void OnEnter(Collider* collider_, Collider* check);

	// [入力] collider_: 自身のコライダー, check: 相手のコライダー
	// [出力] なし
	// [副作用] コライダー同士が接触している間に毎フレーム呼び出されるイベントハンドラ
	virtual void OnTrigger(Collider* collider_, Collider* check);

	// [入力] collider_: 自身のコライダー, check: 相手のコライダー
	// [出力] なし
	// [副作用] コライダー同士が離脱した瞬間に呼び出されるイベントハンドラ
	virtual void OnExit(Collider* collider_, Collider* check);

protected:
	Vector2 position_;
	Vector2 rotation_;

private:
	bool delete_flag_;
	Tag2D tag_;
	bool draw_flag_;
};