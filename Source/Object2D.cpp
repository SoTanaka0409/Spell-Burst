#include "Object2D.h"
#include "ObjectManager.h"
#include "Master.h"
#include "Collider.h"
#include "Scene.h"

Object2D::Object2D(Vector2 initPos)
	: position_(initPos)
	, rotation_(Vector2(0.0f, 0.0f))
	, delete_flag_(false)
	, tag_(Tag2D::kNone2d)
	, draw_flag_(true)
{
}

Object2D::~Object2D()
{
}

void Object2D::Draw()
{
}

void Object2D::Update()
{
}

void Object2D::OnEnter(Collider* collider, Collider* check)
{
}

void Object2D::OnExit(Collider* collider, Collider* check)
{
}

void Object2D::OnTrigger(Collider* collider, Collider* check)
{
}
