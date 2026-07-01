#include "ColliderManager.h"
#include "Collider.h"
#include "DebugLog.h"
#include"Master.h"
#include <vector>
ColliderManager* ColliderManager::Instance = nullptr;


ColliderManager::ColliderManager()
{

}

ColliderManager::~ColliderManager()
{

}
void ColliderManager::Update()
{
<<<<<<< HEAD
    for (auto itr = colliderList.begin(); itr != colliderList.end(); ++itr)
=======
    // 範囲ベースforループで簡潔な当たり判定チェックの二重ループ
    for (auto* col1 : mColliderList)
>>>>>>> main
    {
        if (col1 == nullptr || col1->IsDeleteFlag())
        {
            continue;
        }

<<<<<<< HEAD
        for (auto itr_check = colliderList.begin(); itr_check != colliderList.end(); ++itr_check)
        {
            if (itr == itr_check)//�������g�̃R���C�_�[�Ȃ�߂�
=======
        for (auto* col2 : mColliderList)
        {
            if (col1 == col2) // 自分自身のコライダーは弾く
>>>>>>> main
            {
                continue;
            }

            if (col2 == nullptr || col2->IsDeleteFlag())
            {
                continue;
            }

            col1->Update(col2);
        }
    }

    DeleteAllColliderIfNeeded();
}
void ColliderManager::Draw()
{
<<<<<<< HEAD
    for (auto itr = colliderList.begin(); itr != colliderList.end(); itr++)
=======
    // 範囲ベースforループで簡潔に描画
    for (auto* col : mColliderList)
>>>>>>> main
    {
         if (DebugOn)
        {
            col->Draw();
        }
    }
}
void ColliderManager::AddCollider(Collider* Collider)
{
    colliderList.push_back(Collider);
}
void ColliderManager::DeleteAllCollider()
{
<<<<<<< HEAD
    for (auto itr = colliderList.begin(); itr != colliderList.end(); /*�����͋���ۂȂ̂Œ���*/)
    {

        (*itr)->SetDeleteFlag(true);
        itr = colliderList.erase(itr);
        itr++;

=======
    // 範囲ベースforループで削除フラグを立てて一括消去
    for (auto* col : mColliderList)
    {
        if (col != nullptr) col->SetDeleteFlag(true);
>>>>>>> main
    }
    mColliderList.clear(); // すべての要素をクリア
}
void ColliderManager::DeleteAllColliderIfNeeded()
{
<<<<<<< HEAD
    for (auto itr = colliderList.begin(); itr != colliderList.end(); /*�����͋���ۂȂ̂Œ���*/)
    {
        if ((*itr)->IsDeleteFlag())
        {
            itr = colliderList.erase(itr);

           
        }
        else
        {
            itr++;
        }
    }
=======
    // std::list の remove_if を使用して、安全かつ高速に削除フラグ付き要素を除去
    mColliderList.remove_if([](Collider* col) {
        return col == nullptr || col->IsDeleteFlag();
    });
>>>>>>> main
}

void ColliderManager::RemoveCollider(Collider* collider)
{
    colliderList.remove(collider);
}