#include "ResourceManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    ClearAll();
}

ResourceManager* ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return &instance;
}

int ResourceManager::GetGraph(const std::string& path)
{
    auto it = graph_map_.find(path);
    if (it != graph_map_.end())
    {
        return it->second;
    }

    int handle = LoadGraph(path.c_str());
    graph_map_[path] = handle;
    return handle;
}

int ResourceManager::GetFont(int size, int thickness)
{
    auto key = std::make_pair(size, thickness);
    auto it = font_map_.find(key);
    if (it != font_map_.end())
    {
        return it->second;
    }

    int handle = CreateFontToHandle(NULL, size, thickness, DX_FONTTYPE_ANTIALIASING);
    font_map_[key] = handle;
    return handle;
}

void ResourceManager::ClearAll()
{
    for (auto& pair : graph_map_)
    {
        DeleteGraph(pair.second);
    }
    graph_map_.clear();
    for (auto& pair : font_map_)
    {
        DeleteFontToHandle(pair.second);
    }
    font_map_.clear();
}
