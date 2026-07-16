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
     * オブジェクトの位置や状態をフレームごとに更新する（派生クラスで実装）。
     * [入力] なし
     * [出力] なし
     * [副作用] オブジェクトの状態が更新される
     */
    virtual void Update();

    /*
     * オブジェクトのグラフィックを画面に描画する（派生クラスで実装）。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
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
     * コライダー同士が接触を開始した瞬間に呼び出されるイベントハンドラ。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] 派生クラスによって接触時の処理が実行される
     */
    virtual void OnEnter(Collider* collider, Collider* check);

    /*
     * コライダー同士が接触している間に毎フレーム呼び出されるイベントハンドラ。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] 派生クラスによって継続的な接触処理が実行される
     */
    virtual void OnTrigger(Collider* collider, Collider* check);

    /*
     * コライダー同士が離脱した瞬間に呼び出されるイベントハンドラ。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] 派生クラスによって離脱時の処理が実行される
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
