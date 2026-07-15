#include "ColliderManager.h"
#include <unordered_set>
#include <vector>
#include <cmath>
#include "ObjectManager.h"
#include "Collider.h"
#include "DebugLog.h"
#include "Master.h"
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
    const int CELL_SIZE = 100;
    const int GRID_COLS = 20; // 2000 width
    const int GRID_ROWS = 12; // 1200 height
    std::vector<Collider*> grid[GRID_ROWS][GRID_COLS];

    // Build grid
    for (auto* col : collider_list_)
    {
        if (col == nullptr || col->IsDeleteFlag()) continue;

        int min_col = std::max(0, static_cast<int>((std::min(col->position_.x, col->position2.x) - col->radius_) / CELL_SIZE));
        int max_col = std::min(GRID_COLS - 1, static_cast<int>((std::max(col->position_.x, col->position2.x) + col->radius_) / CELL_SIZE));
        int min_row = std::max(0, static_cast<int>((std::min(col->position_.y, col->position2.y) - col->radius_) / CELL_SIZE));
        int max_row = std::min(GRID_ROWS - 1, static_cast<int>((std::max(col->position_.y, col->position2.y) + col->radius_) / CELL_SIZE));

        for (int r = min_row; r <= max_row; ++r)
        {
            for (int c = min_col; c <= max_col; ++c)
            {
                grid[r][c].push_back(col);
            }
        }
    }

    // Check collisions
    for (auto* col1 : collider_list_)
    {
        if (col1 == nullptr || col1->IsDeleteFlag()) continue;
        
        std::unordered_set<Collider*> checked;

        // Check previously colliding objects first to trigger OnExit if they are no longer colliding
        for (auto* col2 : col1->GetCollisionList())
        {
            if (col2 == nullptr || col2->IsDeleteFlag()) continue;
            col1->Update(col2);
            checked.insert(col2);
        }

        int min_col = std::max(0, static_cast<int>((std::min(col1->position_.x, col1->position2.x) - col1->radius_) / CELL_SIZE));
        int max_col = std::min(GRID_COLS - 1, static_cast<int>((std::max(col1->position_.x, col1->position2.x) + col1->radius_) / CELL_SIZE));
        int min_row = std::max(0, static_cast<int>((std::min(col1->position_.y, col1->position2.y) - col1->radius_) / CELL_SIZE));
        int max_row = std::min(GRID_ROWS - 1, static_cast<int>((std::max(col1->position_.y, col1->position2.y) + col1->radius_) / CELL_SIZE));

        for (int r = min_row; r <= max_row; ++r)
        {
            for (int c = min_col; c <= max_col; ++c)
            {
                for (auto* col2 : grid[r][c])
                {
                    if (col1 == col2) continue;
                    if (col2 == nullptr || col2->IsDeleteFlag()) continue;
                    if (checked.count(col2)) continue;

                    col1->Update(col2);
                    checked.insert(col2);
                }
            }
        }
    }

    DeleteAllColliderIfNeeded();
}

void ColliderManager::Draw()
{
    // 範囲ベースforループで簡潔に描画
    for (auto* col : collider_list_)
    {
         if (DebugOn)
        {
            col->Draw();
        }
    }
}

void ColliderManager::AddCollider(Collider* collider_)
{
    collider_list_.push_back(collider_);
}

void ColliderManager::DeleteAllCollider()
{
    // 範囲ベースforループで削除フラグを立てて一括消去
    for (auto* col : collider_list_)
    {
        if (col != nullptr) col->SetDeleteFlag(true);
    }
    collider_list_.clear(); // すべての要素をクリア
}

void ColliderManager::DeleteAllColliderIfNeeded()
{
    // std::list の remove_if を使用して、安全かつ高速に削除フラグ付き要素を除去
    collider_list_.remove_if([](Collider* col)
    {
        return col == nullptr || col->IsDeleteFlag();
    });
}

void ColliderManager::RemoveCollider(Collider* collider_)
{
    collider_list_.remove(collider_);
}


std::list<Collider*>& ColliderManager::GetColliderList()
{
    return collider_list_;
}
