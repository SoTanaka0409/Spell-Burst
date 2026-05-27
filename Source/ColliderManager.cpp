#include "ColliderManager.h"
#include "Collider.h"
#include"Master.h"
#include <vector>

// 静的メンバ変数定義
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

        // 削除予定ならスキップ
        if ((*itr)->IsDeleteFlag())
        {
            continue;
        }

        for (auto itr_check = mColliderList.begin(); itr_check != mColliderList.end(); ++itr_check)
        {
            if (itr == itr_check)//自分自身のコライダーなら戻る
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

// 描画wwwww
void ColliderManager::Draw()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); itr++)
    {
         //if (Master::mpDebug->Getdebug())
        {
            (*itr)->Draw();
        }
    }
}

// Colliderオブジェクトの追加
void ColliderManager::AddCollider(Collider* Collider)
{
    mColliderList.push_back(Collider);
}

// Colliderオブジェクトの全削除
void ColliderManager::DeleteAllCollider()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); /*ここは空っぽなので注意*/)
    {

        (*itr)->SetDeleteFlag(true);
        // リストから削除
        itr = mColliderList.erase(itr);
        itr++;

    }
    DeleteAllColliderIfNeeded();
}

// 削除する必要のあるオブジェクトがあれば削除する
void ColliderManager::DeleteAllColliderIfNeeded()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); /*ここは空っぽなので注意*/)
    {
        // 破棄フラグが立っていれば削除する
        if ((*itr)->IsDeleteFlag())
        {
            
            // リストから削除
            // erase() は、削除した itr の次の要素を返却してくれる
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