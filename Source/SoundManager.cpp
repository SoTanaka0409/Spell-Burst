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
    if (soundMap.find(path) == soundMap.end())
    {
        int handle = LoadSoundMem(path.c_str());
        soundMap[path] = handle;
    }
    return soundMap[path];
}

void SoundManager::PlayBGM(const std::string& path)
{
    int handle = GetSound(path);
    if (handle != -1)
    {
        // Œ»İ‚ÌBGM‚ªˆá‚¤ê‡‚Í~‚ß‚é
        if (current_bgm_handle_ != -1 && current_bgm_handle_ != handle)
        {
            StopSoundMem(current_bgm_handle_);
        }
        
        // Ä¶‚³‚ê‚Ä‚¢‚È‚¢ê‡‚Ì‚İÄ¶ŠJn
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
{//‚a‚f‚l‚Ì’â~
    if (current_bgm_handle_ != -1)
    {
        StopSoundMem(current_bgm_handle_);
        current_bgm_handle_ = -1;
    }
}

void SoundManager::StopAll()
{
    // ‘S‚Ä‚ÌƒTƒEƒ“ƒh‚ÌÄ¶‚ğ’â~
    for (auto& pair : soundMap)
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
    for (auto& pair : soundMap)
    {
        if (pair.second != -1)
        {
            DeleteSoundMem(pair.second);
        }
    }
    soundMap.clear();
}

