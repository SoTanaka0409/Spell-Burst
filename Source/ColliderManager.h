#pragma once
#include <list>

class Collider;

class ColliderManager
{
public:
    ColliderManager();
    ~ColliderManager();

    void Update();
    void Draw();

    static ColliderManager* GetInstance()
    {
        if (Instance == nullptr)
        {
            Instance = new ColliderManager();
        }
        return Instance;
    }

    static void Finalize()
    {
        if (Instance != nullptr)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

public:
    void AddCollider(Collider* collider);
    void DeleteAllCollider();
    void DeleteAllColliderIfNeeded();
    void RemoveCollider(Collider* collider);
    
    std::list<Collider*>& GetColliderList();

private:
    std::list<Collider*> mColliderList;

    static ColliderManager* Instance;
};
