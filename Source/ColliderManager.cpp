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
    // 範囲ベースforループで簡潔な当たり判定チェックの二重ループ
    for (auto* col1 : mColliderList)
    {
        if (col1 == nullptr || col1->IsDeleteFlag())
        {
            continue;
        }

        for (auto* col2 : mColliderList)
        {
            if (col1 == col2) // 自分自身のコライダーは弾く
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
    // 範囲ベースforループで簡潔に描画
    for (auto* col : mColliderList)
    {
         if (DebugOn)
        {
            col->Draw();
        }
    }
}
void ColliderManager::AddCollider(Collider* Collider)
{
    mColliderList.push_back(Collider);
}
void ColliderManager::DeleteAllCollider()
{
    // 範囲ベースforループで削除フラグを立てて一括消去
    for (auto* col : mColliderList)
    {
        if (col != nullptr) col->SetDeleteFlag(true);
    }
    mColliderList.clear(); // すべての要素をクリア
}
void ColliderManager::DeleteAllColliderIfNeeded()
{
    // std::list の remove_if を使用して、安全かつ高速に削除フラグ付き要素を除去
    mColliderList.remove_if([](Collider* col) {
        return col == nullptr || col->IsDeleteFlag();
    });
}

void ColliderManager::RemoveCollider(Collider* collider)
{
    mColliderList.remove(collider);
}