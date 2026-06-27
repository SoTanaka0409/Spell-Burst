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
    for (auto itr = colliderList.begin(); itr != colliderList.end(); ++itr)
    {
        if ((*itr) == nullptr)
        {
            continue;
        }
        if ((*itr)->IsDeleteFlag())
        {
            continue;
        }

        for (auto itr_check = colliderList.begin(); itr_check != colliderList.end(); ++itr_check)
        {
            if (itr == itr_check)//�������g�̃R���C�_�[�Ȃ�߂�
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
    for (auto itr = colliderList.begin(); itr != colliderList.end(); itr++)
    {
         if (DebugOn)
        {
            (*itr)->Draw();
        }
    }
}
void ColliderManager::AddCollider(Collider* Collider)
{
    colliderList.push_back(Collider);
}
void ColliderManager::DeleteAllCollider()
{
    for (auto itr = colliderList.begin(); itr != colliderList.end(); /*�����͋���ۂȂ̂Œ���*/)
    {

        (*itr)->SetDeleteFlag(true);
        itr = colliderList.erase(itr);
        itr++;

    }
    DeleteAllColliderIfNeeded();
}
void ColliderManager::DeleteAllColliderIfNeeded()
{
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
}

void ColliderManager::RemoveCollider(Collider* collider)
{
    colliderList.remove(collider);
}