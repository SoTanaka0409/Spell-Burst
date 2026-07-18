#include "SoundManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

SoundManager::SoundManager() : current_bgm_handle_(-1)
{
}

SoundManager::~SoundManager()
{
	ClearAll();
}

SoundManager* SoundManager::GetInstance()
{
	static SoundManager instance;
	return &instance;
}

int SoundManager::GetSound(const std::string& path)
{
	if (sound_map_.find(path) == sound_map_.end())
	{
		int handle = LoadSoundMem(path.c_str());
		sound_map_[path] = handle;
	}
	return sound_map_[path];
}

void SoundManager::PlayBGM(const std::string& path)
{
	int handle = GetSound(path);
	if (handle != -1)
	{
		if (current_bgm_handle_ != -1 && current_bgm_handle_ != handle)
		{
			StopSoundMem(current_bgm_handle_);
		}

		if (CheckSoundMem(handle) == 0)
		{
			PlaySoundMem(handle, DX_PLAYTYPE_LOOP);
			current_bgm_handle_ = handle;
		}
	}
}

void SoundManager::PlaySE(const std::string& path)
{
	int handle = GetSound(path);
	if (handle != -1)
	{
		PlaySoundMem(handle, DX_PLAYTYPE_BACK, TRUE);
	}
}

void SoundManager::StopBGM()
{
	if (current_bgm_handle_ != -1)
	{
		StopSoundMem(current_bgm_handle_);
		current_bgm_handle_ = -1;
	}
}

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
