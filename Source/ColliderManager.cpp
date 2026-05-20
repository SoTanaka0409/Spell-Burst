#include "ColliderManager.h"
#include "Collider.h"

#include <vector>

// 静的メンバ変数の定義
ColliderManager* ColliderManager::Instance = nullptr;


ColliderManager::ColliderManager()
{

}

ColliderManager::~ColliderManager()
{

}

// 更新
void ColliderManager::Update()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); ++itr)
    {
        // nullptrチェック
        if ((*itr) == nullptr)
        {
            continue;
        }

        // 削除予定なのでスキップ
        if ((*itr)->IsDeleteFlag())
        {
            continue;
        }

        for (auto itr_check = mColliderList.begin(); itr_check != mColliderList.end(); ++itr_check)
        {
            if (itr == itr_check)
            {
                continue;
            }

            if ((*itr_check) == nullptr)
            {
                continue;
            }

            if ((*itr_check)->IsDeleteFlag())
            {
                continue;
            }

            (*itr)->Update((*itr_check));
        }
    }

    DeleteAllColliderIfNeeded();
}

// 描画
void ColliderManager::Draw()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); itr++)
    {
        // デバッグ描画が必要な場合はここで呼ぶ
        // (*itr)->Draw();
    }
}

// Colliderオブジェクトの追加
void ColliderManager::AddCollider(Collider* collider)
{
    mColliderList.push_back(collider);
}

// Colliderオブジェクトの全削除
void ColliderManager::DeleteAllCollider()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end();)
    {
        (*itr)->SetDeleteFlag(true);
        // リストから削除（erase はイテレータを返すので itr に代入してループを継続）
        itr = mColliderList.erase(itr);
        // ※ erase後に itr++ は不要（erase の戻り値が次の要素を指している）
    }
}

// 削除する必要のあるオブジェクトがあれば削除する
void ColliderManager::DeleteAllColliderIfNeeded()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end();)
    {
        // 削除フラグが立っていれば削除する
        if ((*itr)->IsDeleteFlag())
        {
            // リストから削除
            // erase() は、削除した後の itr の次の要素を返す
            itr = mColliderList.erase(itr);
        }
        else
        {
            // 次の要素へ進める
            itr++;
        }
    }
}

void ColliderManager::RemoveCollider(Collider* collider)
{
    mColliderList.remove(collider);
}

std::list<Collider*>& ColliderManager::GetColliderList()
{
    return mColliderList;
}
