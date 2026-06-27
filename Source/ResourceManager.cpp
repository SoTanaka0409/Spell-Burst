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
    auto it = graphMap.find(path);
    if (it != graphMap.end()) {
        return it->second;
    }

    int handle = LoadGraph(path.c_str());
    graphMap[path] = handle;
    return handle;
}

int ResourceManager::GetFont(int size, int thickness) {
    auto key = std::make_pair(size, thickness);
    auto it = fontMap.find(key);
    if (it != fontMap.end()) {
        return it->second;
    }

    int handle = CreateFontToHandle(NULL, size, thickness, DX_FONTTYPE_ANTIALIASING);
    fontMap[key] = handle;
    return handle;
}

void ResourceManager::ClearAll() {
    for (auto& pair : graphMap) {
        DeleteGraph(pair.second);
    }
    graphMap.clear();
    for (auto& pair : fontMap) {
        DeleteFontToHandle(pair.second);
    }
    fontMap.clear();
}