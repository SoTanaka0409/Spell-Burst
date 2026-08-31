#include "ResourceManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

#include <fstream>
#include <sstream>

/// @brief ResourceManager を生成する
ResourceManager::ResourceManager()
{
}

/// @brief 破棄処理を行う
ResourceManager::~ResourceManager()
{
	ClearAll();
}

/// @brief シングルトンインスタンスを取得する
/// @return ResourceManager* 戻り値
ResourceManager* ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return &instance;
}

/// @brief CSVファイルを読み込む
/// @param csv_path csv_path の値
/// @return bool 戻り値
bool ResourceManager::LoadCSV(const std::string& csv_path)
{
	std::ifstream file(csv_path);
	if (!file.is_open()) return false;

	std::string line;
	// ヘッダー行を読み飛ばす
	std::getline(file, line); 

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string id, path;
		if (std::getline(ss, id, ',') && std::getline(ss, path, ','))
		{
			// Windows環境で行末の\rが混入した場合に取り除く
			if (!path.empty() && path.back() == '\r') path.pop_back();
			asset_paths_[id] = path;
		}
	}
	return true;
}

/// @brief アセットIDに対応するパスを取得する
/// @param id id の値
/// @return std::string 戻り値
std::string ResourceManager::GetAssetPath(const std::string& id)
{
	auto it = asset_paths_.find(id);
	if (it != asset_paths_.end())
	{
		return it->second;
	}
	// IDが見つからない場合は、後方互換のためID自体をパスとして返す
	return id;
}

/// @brief 画像ハンドルを取得する
/// @param id id の値
/// @return int 戻り値
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

/// @brief フォントハンドルを取得する
/// @param size size の値
/// @param thickness thickness の値
/// @return int 戻り値
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

/// @brief 読み込み済みリソースを解放する
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
