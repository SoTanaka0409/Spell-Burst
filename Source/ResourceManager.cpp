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
    m_graphMap[path] = handle;
    return handle;
}

void ResourceManager::ClearAll() {
    for (auto& pair : m_graphMap) {
        DeleteGraph(pair.second);
    }
    m_graphMap.clear();
}
