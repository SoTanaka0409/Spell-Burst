#pragma once
#include "Scene.h"

class SceneManager
{
public:

	enum SCENE_TYPE
	{
		SCENE_NONE = 0,
		SCENE_RESET,
		SCENE_NAME,
		SCENE_TITLE,
		SCENE_OPERATION,
		SCENE_RULE,//�^�C�g��
		SCENE_TUTORIAL,
		SCENE_LEVEL,
		SCENE_GAME,    //�Q�[��
		SCENE_3DHARD,
		SCENE_RESULT,   //���U���g
		SCENE_RESULTWIN,
		SCENE_NORMALRESULTSCENE,//�Q�[���I�[�o�[
		SCENE_3D

	};
public:
	SceneManager();
	
	~SceneManager();


	void Initialize();

	void Draw();

	void Update();

	void Finalize();
	//�V�[���J�ځi�؂�ւ������j���K�v�ȏ�ԂȂ�J�ڏ��������
	void ChangeSceneIfNeeded();
	//���Ɉړ�����J�ڂ���V�[���̐ݒ�
	//note:�V�[���J�ڂ�������ꍇ�́A�K�����̏�����o�R���đJ�ڂ�����
	void SetNextScene(SCENE_TYPE next) { mnNextSceneType = next; }

	void SetSceneHard(bool Hard) { SceneHard = Hard; }
	bool GetSceneHard() { return SceneHard; }

	void SetSceneNormal(bool Normal) {SceneNormal=Normal; }
	bool GetSceneNormal() { return SceneNormal; }


	//���݂̃V�[���̎擾
	Scene* GetCurrentScene() { return mpCurrentScene; }

private:
	SCENE_TYPE mnSceneType;     //���݂̃V�[���̃^�C�v
	SCENE_TYPE mnNextSceneType;//���̃V�[���̃^�C�v
	Scene* mpCurrentScene;    //���݃V�[���̃|�C���^
	Scene* mp;

	bool SceneHard;
	bool SceneNormal;

};