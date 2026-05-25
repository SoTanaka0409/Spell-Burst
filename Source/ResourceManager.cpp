#include "ResourceManager.h"
#include <DxLib.h>

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
    ClearAll();
}

ResourceManager* ResourceManager::GetInstance() {
    static ResourceManager instance;
    return &instance;
}

int ResourceManager::GetGraph(const std::string& path) {
    auto it = m_graphMap.find(path);
    if (it != m_graphMap.end()) {
        return it->second;
    }

    int handle = LoadGraph(path.c_str());
    if (handle != -1) {
        m_graphMap[path] = handle;
    }
    return handle;
}

<<<<<<< HEAD
=======
int ResourceManager::GetFont(int size, int thickness) {
    int key = size * 1000 + (thickness > 0 ? thickness : 0);
    auto it = m_fontMap.find(key);
    if (it != m_fontMap.end()) {
        return it->second;
    }

    int handle = CreateFontToHandle(NULL, size, thickness);
    if (handle != -1) {
        m_fontMap[key] = handle;
    }
    return handle;
}

>>>>>>> main
void ResourceManager::ClearAll() {
    for (auto& pair : m_graphMap) {
        DeleteGraph(pair.second);
    }
    m_graphMap.clear();
<<<<<<< HEAD
=======

    for (auto& pair : m_fontMap) {
        DeleteFontToHandle(pair.second);
    }
    m_fontMap.clear();
>>>>>>> main
}
