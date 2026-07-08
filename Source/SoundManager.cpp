#include "SoundManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

SoundManager::SoundManager() : current_bgm_handle_(-1) {
}

SoundManager::~SoundManager() {
    ClearAll();
}

SoundManager* SoundManager::GetInstance() {
    static SoundManager instance;
    return &instance;
}

int SoundManager::GetSound(const std::string& path) {
    if (soundMap.find(path) == soundMap.end()) {
        int handle = LoadSoundMem(path.c_str());
        soundMap[path] = handle;
    }
    return soundMap[path];
}

void SoundManager::PlayBGM(const std::string& path) {
    int handle = GetSound(path);
    if (handle != -1) {
        // 現在のBGMが違う場合は止める
        if (current_bgm_handle_ != -1 && current_bgm_handle_ != handle) {
            StopSoundMem(current_bgm_handle_);
        }
        
        // 再生されていない場合のみ再生開始
        if (CheckSoundMem(handle) == 0) {
            PlaySoundMem(handle, DX_PLAYTYPE_LOOP);
            current_bgm_handle_ = handle;
        }
    }
}

void SoundManager::PlaySE(const std::string& path) {
    int handle = GetSound(path);
    if (handle != -1) {
        PlaySoundMem(handle, DX_PLAYTYPE_BACK, TRUE);
    }
}

void SoundManager::StopBGM() 
{//ＢＧＭの停止
    if (current_bgm_handle_ != -1)
    {
        StopSoundMem(current_bgm_handle_);
        current_bgm_handle_ = -1;
    }
}

void SoundManager::StopAll() {
    // 全てのサウンドの再生を停止
    for (auto& pair : soundMap) {
        if (pair.second != -1) {
            StopSoundMem(pair.second);
        }
    }
    current_bgm_handle_ = -1;
}

void SoundManager::ClearAll() 
{
    StopAll();
    for (auto& pair : soundMap) {
        if (pair.second != -1) {
            DeleteSoundMem(pair.second);
        }
    }
    soundMap.clear();
}

