#include "Vector2.h"
#pragma once
#include <string>
#include "vector"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Collider.h"

/// @brief 2Dゲームオブジェクトの共通基底クラス
class Object2D
{
public:
	/// @brief 2Dオブジェクトの種別タグ
	enum Tag2D
	{
		kNone2d = 0,           ///< タグなし
		kTag2dPlayer = 1,     ///< プレイヤー
		kTag2dEnemy = 2,      ///< 敵
		kTag2dPlayerBullet = 3, ///< プレイヤー弾
		kTag2dEnemyBullet = 4,  ///< 敵弾
		kTag2dBarrierEnemy = 5, ///< 敵バリア
		kTag2dBarrierPlayer = 6 ///< プレイヤーバリア
	};

public:
    /// @brief 2Dオブジェクトを生成する
    /// @param initPos 初期座標
    Object2D(Vector2 initPos);

	/// @brief 2Dオブジェクトを破棄する
	virtual ~Object2D();

    /// @brief オブジェクトの状態を毎フレーム更新する
    virtual void Update();

    /// @brief オブジェクトを描画する
    virtual void Draw();

	/// @brief 座標を設定する
	/// @param pos 設定する座標
	void SetPosition(Vector2 pos) { position_ = pos; }

	/// @brief 座標を取得する
	/// @return Vector2 現在座標
	Vector2 GetPosition() { return position_; }

	/// @brief 回転値を設定する
	/// @param rot 設定する回転値
	void SetRotation(Vector2 rot) { rotation_ = rot; }

	/// @brief 回転値を取得する
	/// @return Vector2 現在の回転値
	Vector2 GetRotation() { return rotation_; }

	/// @brief 削除フラグを設定する
	/// @param flag 削除対象ならtrue
	void SetDeleteFlag(bool flag) { delete_flag_ = flag; }

	/// @brief 削除フラグを取得する
	/// @return bool 削除対象ならtrue
	bool IsDeleteFlag() { return delete_flag_; }

	/// @brief 描画フラグを設定する
	/// @param flag 描画するならtrue
	void SetDrawFlag(bool flag) { draw_flag_ = flag; }

	/// @brief 描画フラグを取得する
	/// @return bool 描画するならtrue
	bool IsDrawFlag() { return draw_flag_; }

	/// @brief オブジェクトタグを設定する
	/// @param tag 設定するタグ
	void SetTag(Tag2D tag) { tag_ = tag; }

	/// @brief オブジェクトタグを取得する
	/// @return Tag2D 現在のタグ
	Tag2D GetTag() { return tag_; }

    /// @brief コライダー接触開始時の処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnEnter(Collider* collider, Collider* check);

    /// @brief コライダー接触中の処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check);

    /// @brief コライダー接触終了時の処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnExit(Collider* collider, Collider* check);

protected:
	Vector2 position_; ///< オブジェクトの座標
	Vector2 rotation_; ///< オブジェクトの回転値

private:
	bool delete_flag_; ///< 削除対象かを示すフラグ
	Tag2D tag_;        ///< オブジェクト種別タグ
	bool draw_flag_;   ///< 描画するかを示すフラグ
};