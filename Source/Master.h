#pragma once
#include "SceneManager.h"
#include <memory>

class Master
{
public:
	static std::unique_ptr<SceneManager> sceneManager;
};