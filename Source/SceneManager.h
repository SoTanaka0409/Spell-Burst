#include <memory>
#pragma once
#include "Scene.h"

// ゲーム全体のシーン遷移を管理するクラス
class SceneManager
{
public:
	enum SceneType
	{
		kSceneNone = 0,
		kSceneReset,
		kSceneName,
		kSceneTitle,
		kSceneOperation,
		kSceneRule,
		kSceneTutorial,
		kSceneLevel,
		kSceneGame,
		kScene3dHard,
		kSceneResult,
		kSceneResultWin,
		kSceneNormalResultScene,
		kScene3d
	};

public:
	SceneManager();
	~SceneManager();

    /*
     * 最初のシーン（通常はTITLE等）のInitializeを呼び出し初期化する。
     * [入力] なし
     * [出力] なし
     * [副作用] シーンが初期化される
     */
	void Initialize();

    /*
     * 現在のシーンのDraw関数を呼び出し、描画処理を委譲する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面にシーンの要素が描画される
     */
	void Draw();

    /*
     * 現在のシーンのUpdate関数を呼び出す。また、次シーンが予約されていれば遷移処理を行う。
     * [入力] なし
     * [出力] なし
     * [副作用] シーンの更新や切り替えが発生する
     */
	void Update();

    /*
     * 現在のシーンのFinalizeを呼び出し、メモリを解放する。
     * [入力] なし
     * [出力] なし
     * [副作用] シーンのリソースが解放される
     */
	void Finalize();

    /*
     * next_scene_type_が設定されている場合、旧シーンを破棄して新シーンを生成・初期化する。
     * [入力] なし
     * [出力] なし
     * [副作用] シーンの切り替えが完了する
     */
	void ChangeSceneIfNeeded();

    /*
     * 次のシーンを予約する。
     * [入力] next: 次に遷移したいシーンの種別
     * [出力] なし
     * [副作用] 次回Update時にシーン遷移が行われる
     */
	void SetNextScene(SceneType next) { next_scene_type_ = next; }

	void SetSceneHard(bool isHard) { is_scene_hard_ = isHard; }
	bool GetSceneHard() { return is_scene_hard_; }

	void SetSceneNormal(bool isNormal) {is_scene_normal_ = isNormal; }
	bool GetSceneNormal() { return is_scene_normal_; }

	Scene* GetCurrentScene() { return current_scene_.get(); }

private:
	SceneType scene_type_;     
	SceneType next_scene_type_;
	std::unique_ptr<Scene> current_scene_;    
	

	bool is_scene_hard_;
	bool is_scene_normal_;
};
