#pragma once
#include "SceneManager.h"
#include <memory>

/// @brief ゲーム全体で共有する主要管理オブジェクトを保持するクラス
class Master
{
public:
	static std::unique_ptr<SceneManager> sceneManager; ///< シーン管理クラスの共有インスタンス
};