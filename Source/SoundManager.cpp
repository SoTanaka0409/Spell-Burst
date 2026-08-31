#include "SoundManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

/// @brief SoundManager を生成する
SoundManager::SoundManager() : current_bgm_handle_(-1)
{
}

/// @brief 破棄処理を行う
SoundManager::~SoundManager()
{
	ClearAll();
}

/// @brief シングルトンインスタンスを取得する
/// @return SoundManager* 戻り値
SoundManager* SoundManager::GetInstance()
{
	static SoundManager instance;
	return &instance;
}

/// @brief GetSound を実行する
/// @param id id の値
/// @return int 戻り値
int SoundManager::GetSound(const std::string& id)
{
    std::string path = ResourceManager::GetInstance()->GetAssetPath(id);

    auto it = sound_map_.find(path);
    if (it != sound_map_.end())
    {
        return it->second;
    }

    int handle = LoadSoundMem(path.c_str());
    if (handle != -1)
    {
        sound_map_[path] = handle;
    }
    return handle;
}

/// @brief BGMを再生する
/// @param id id の値
void SoundManager::PlayBGM(const std::string& id)
{
    int handle = GetSound(id);
    if (handle == -1) return;

    if (current_bgm_handle_ != handle)
    {
        StopBGM();
        PlaySoundMem(handle, DX_PLAYTYPE_LOOP);
        current_bgm_handle_ = handle;
    }
}

/// @brief 効果音を再生する
/// @param id id の値
void SoundManager::PlaySE(const std::string& id)
{
    int handle = GetSound(id);
    if (handle != -1)
    {
        PlaySoundMem(handle, DX_PLAYTYPE_BACK);
    }
}

/// @brief BGMを停止する
void SoundManager::StopBGM()
{
	if (current_bgm_handle_ != -1)
	{
		StopSoundMem(current_bgm_handle_);
		current_bgm_handle_ = -1;
	}
}

/// @brief すべての音声を停止する
void SoundManager::StopAll()
{
	for (auto& pair : sound_map_)
	{
		if (pair.second != -1)
		{
			StopSoundMem(pair.second);
		}
	}
	current_bgm_handle_ = -1;
}

/// @brief 読み込み済みリソースを解放する
void SoundManager::ClearAll()
{
	StopAll();

	for (auto& pair : sound_map_)
	{
		if (pair.second != -1)
		{
			DeleteSoundMem(pair.second);
		}
	}
	sound_map_.clear();
}
