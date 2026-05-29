#include "Object2D.h"
#include "Master.h"
#include "ObjectManager.h"
#include "Collider.h"
#include "Scene.h"

Object2D::Object2D(VECTOR initPos)
	: mvPosition(initPos)
	, mvRotation(VGet(0.0f, 0.0f, 0.0f))
	, mbDeleteFlag(false)
	, mnTag(Tag2D::None2D)
	, mbDrawFlag(true)
{
	Master::sceneManager->GetCurrentScene()->GetObjectManager()->AddObject(this);
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