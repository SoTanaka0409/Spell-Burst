#include "ResourceManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

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

int ResourceManager::GetFont(int size, int thickness) {
    auto key = std::make_pair(size, thickness);
    auto it = m_fontMap.find(key);
    if (it != m_fontMap.end()) {
        return it->second;
    }

    int handle = CreateFontToHandle(NULL, size, thickness, DX_FONTTYPE_ANTIALIASING);
    m_fontMap[key] = handle;
    return handle;
}

void ResourceManager::ClearAll() {
    for (auto& pair : m_graphMap) {
        DeleteGraph(pair.second);
    }
    m_graphMap.clear();
    for (auto& pair : m_fontMap) {
        DeleteFontToHandle(pair.second);
    }
    m_fontMap.clear();
}