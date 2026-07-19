#include "ResourceManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

#include <fstream>
#include <sstream>

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

bool ResourceManager::LoadCSV(const std::string& csv_path)
{
	std::ifstream file(csv_path);
	if (!file.is_open()) return false;

	std::string line;
	// ヘッダー行をスキップする場合は以下を有効に
	std::getline(file, line); 

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string id, path;
		if (std::getline(ss, id, ',') && std::getline(ss, path, ','))
		{
			// Windows環境の改行コード(\r)が混入する対策
			if (!path.empty() && path.back() == '\r') path.pop_back();
			asset_paths_[id] = path;
		}
	}
	return true;
}

std::string ResourceManager::GetAssetPath(const std::string& id)
{
	auto it = asset_paths_.find(id);
	if (it != asset_paths_.end())
	{
		return it->second;
	}
	// IDが見つからない場合、後方互換性のためID自体をパスとして返す
	return id;
}

int ResourceManager::GetGraph(const std::string& id)
{
	std::string path = GetAssetPath(id);

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
