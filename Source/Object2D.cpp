#include "Object2D.h"
#include "ObjectManager.h"
#include "Master.h"
#include "Collider.h"
#include "Scene.h"

/// @brief Object2D を生成する
/// @param initPos initPos の値
Object2D::Object2D(Vector2 initPos)
	: position_(initPos)
	, rotation_(Vector2(0.0f, 0.0f))
	, delete_flag_(false)
	, tag_(Tag2D::kNone2d)
	, draw_flag_(true)
{
}

/// @brief 破棄処理を行う
Object2D::~Object2D()
{
}

/// @brief 描画処理を行う
void Object2D::Draw()
{
}

/// @brief 毎フレームの更新処理を行う
void Object2D::Update()
{
}

/// @brief 接触開始時の処理を行う
/// @param collider collider の値
/// @param check check の値
void Object2D::OnEnter(Collider* collider, Collider* check)
{
}

/// @brief 接触終了時の処理を行う
/// @param collider collider の値
/// @param check check の値
void Object2D::OnExit(Collider* collider, Collider* check)
{
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void Object2D::OnTrigger(Collider* collider, Collider* check)
{
}
