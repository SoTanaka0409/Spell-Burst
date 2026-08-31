#include "ColliderManager.h"
#include <unordered_set>
#include <vector>
#include <cmath>
#include "ObjectManager.h"
#include "Collider.h"
#include "DebugLog.h"
#include "Master.h"

ColliderManager* ColliderManager::instance_ = nullptr;

/// @brief ColliderManager を生成する
ColliderManager::ColliderManager()
{
}

/// @brief 破棄処理を行う
ColliderManager::~ColliderManager()
{
}

/// @brief 毎フレームの更新処理を行う
void ColliderManager::Update()
{
	const int CELL_SIZE = 100;
	const int GRID_COLS = 20;
	const int GRID_ROWS = 12;

	std::vector<Collider*> grid[GRID_ROWS][GRID_COLS];

	for (auto* col : collider_list_)
	{
		if (col == nullptr || col->IsDeleteFlag()) continue;

		int min_col = std::max(0, std::min(GRID_COLS - 1, static_cast<int>((std::min(col->position_.x, col->position2_.x) - col->radius_) / CELL_SIZE)));
		int max_col = std::max(0, std::min(GRID_COLS - 1, static_cast<int>((std::max(col->position_.x, col->position2_.x) + col->radius_) / CELL_SIZE)));
		int min_row = std::max(0, std::min(GRID_ROWS - 1, static_cast<int>((std::min(col->position_.y, col->position2_.y) - col->radius_) / CELL_SIZE)));
		int max_row = std::max(0, std::min(GRID_ROWS - 1, static_cast<int>((std::max(col->position_.y, col->position2_.y) + col->radius_) / CELL_SIZE)));

		for (int r = min_row; r <= max_row; ++r)
		{
			for (int c = min_col; c <= max_col; ++c)
			{
				grid[r][c].push_back(col);
			}
		}
	}

	std::unordered_set<Collider*> current_intersecting_pairs;

	for (int r = 0; r < GRID_ROWS; ++r)
	{
		for (int c = 0; c < GRID_COLS; ++c)
		{
			const auto& cell_colliders = grid[r][c];
			size_t col_count = cell_colliders.size();
			if (col_count < 2) continue;

			for (size_t i = 0; i < col_count; ++i)
			{
				Collider* col1 = cell_colliders[i];
				if (col1 == nullptr || col1->IsDeleteFlag()) continue;

				for (size_t j = i + 1; j < col_count; ++j)
				{
					Collider* col2 = cell_colliders[j];
					if (col2 == nullptr || col2->IsDeleteFlag()) continue;

					if (col1 == col2 || col1->GetParentObject() == col2->GetParentObject()) continue;

					col1->Update(col2);
					col2->Update(col1);
				}
			}
		}
	}

	DeleteAllColliderIfNeeded();
}

/// @brief 描画処理を行う
void ColliderManager::Draw()
{
	for (auto* col : collider_list_)
	{
		if (DebugOn)
		{
			col->Draw();
		}
	}
}

/// @brief AddCollider を実行する
/// @param collider collider の値
void ColliderManager::AddCollider(Collider* collider)
{
	collider_list_.push_back(collider);
}

/// @brief DeleteAllCollider を実行する
void ColliderManager::DeleteAllCollider()
{
	for (auto* col : collider_list_)
	{
		if (col != nullptr) col->SetDeleteFlag(true);
	}
	collider_list_.clear();
}

/// @brief DeleteAllColliderIfNeeded を実行する
void ColliderManager::DeleteAllColliderIfNeeded()
{
	collider_list_.remove_if([](Collider* col)
		{
			return col == nullptr || col->IsDeleteFlag();
		});
}

/// @brief RemoveCollider を実行する
/// @param collider collider の値
void ColliderManager::RemoveCollider(Collider* collider)
{
	collider_list_.remove(collider);
}

/// @brief GetColliderList を実行する
/// @return std::list<Collider*>& 戻り値
std::list<Collider*>& ColliderManager::GetColliderList()
{
	return collider_list_;
}
