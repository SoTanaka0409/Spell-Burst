#pragma once
#include <string>
#include <unordered_map>

class SoundManager
{
private:
    SoundManager();
    ~SoundManager();

public:
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    static SoundManager* GetInstance();

    /*
     * サウンドハンドルを取得する（キャッシュになければロードする）。
     * [入力] path: 音声ファイルのパス
     * [出力] サウンドハンドル
     * [副作用] メモリに音声データがロードされ、マップに登録される
     */
    int GetSound(const std::string& path);

    /*
     * BGMをループ再生する。
     * [入力] path: 音声ファイルのパス
     * [出力] なし
     * [副作用] 現在のBGMが停止し、新しいBGMが再生される
     */
    void PlayBGM(const std::string& path);
    
    /*
     * SEを単発再生する。
     * [入力] path: 音声ファイルのパス
     * [出力] なし
     * [副作用] SEが再生される
     */
    void PlaySE(const std::string& path);

    /*
     * 再生中のBGMを停止する。
     * [入力] なし
     * [出力] なし
     * [副作用] BGMの再生が止まる
     */
    void StopBGM();

    /*
     * 再生中のすべての音を停止する。
     * [入力] なし
     * [出力] なし
     * [副作用] すべての音声が停止する
     */
    void StopAll();

    /*
     * ロード済みのすべての音声のメモリを解放する。
     * [入力] なし
     * [出力] なし
     * [副作用] すべてのサウンドハンドルが削除され、マップがクリアされる
     */
    void ClearAll();

private:
    std::unordered_map<std::string, int> sound_map_;
    int current_bgm_handle_;
};
