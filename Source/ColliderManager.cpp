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
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); ++itr)
    {
        if ((*itr) == nullptr)
        {
            continue;
        }
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
void ColliderManager::Draw()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); itr++)
    {
         if (DebugOn)
        {
            (*itr)->Draw();
        }
    }
}
void ColliderManager::AddCollider(Collider* Collider)
{
    mColliderList.push_back(Collider);
}
void ColliderManager::DeleteAllCollider()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); /*ここは空っぽなので注意*/)
    {

        (*itr)->SetDeleteFlag(true);
        itr = mColliderList.erase(itr);
        itr++;

    }
    DeleteAllColliderIfNeeded();
}
void ColliderManager::DeleteAllColliderIfNeeded()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); /*ここは空っぽなので注意*/)
    {
        if ((*itr)->IsDeleteFlag())
        {
            itr = mColliderList.erase(itr);

           
        }
        else
        {
            itr++;
        }
    }
}

void ColliderManager::RemoveCollider(Collider* collider)
{
    mColliderList.remove(collider);
}