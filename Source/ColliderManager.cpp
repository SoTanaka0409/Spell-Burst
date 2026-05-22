#include "ColliderManager.h"
#include "Collider.h"
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
    // Make a copy of the list to prevent iterator invalidation if colliders are deleted during updates
    std::vector<Collider*> activeColliders(mColliderList.begin(), mColliderList.end());

    for (size_t i = 0; i < activeColliders.size(); ++i)
    {
        Collider* c1 = activeColliders[i];
        if (c1 == nullptr || c1->IsDeleteFlag()) continue;

        for (size_t j = i + 1; j < activeColliders.size(); ++j)
        {
            Collider* c2 = activeColliders[j];
            if (c2 == nullptr || c2->IsDeleteFlag() || c1 == c2) continue;

            // Perform bidirectional collision checks
            c1->Update(c2);
            c2->Update(c1);
        }
    }

    DeleteAllColliderIfNeeded();
}

void ColliderManager::Draw()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); itr++)
    {
        if (*itr != nullptr && !(*itr)->IsDeleteFlag())
        {
            (*itr)->Draw();
        }
    }
}

void ColliderManager::AddCollider(Collider* collider)
{
    mColliderList.push_back(collider);
}

void ColliderManager::DeleteAllCollider()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); )
    {
        (*itr)->SetDeleteFlag(true);
        itr = mColliderList.erase(itr);
    }
}

void ColliderManager::DeleteAllColliderIfNeeded()
{
    for (auto itr = mColliderList.begin(); itr != mColliderList.end(); )
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

std::list<Collider*>& ColliderManager::GetColliderList()
{
    return mColliderList;
}
