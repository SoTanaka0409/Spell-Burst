#pragma once
#include "Scene.h"

// �L�����N�^�[�I�����ѓ�Փx�i�X�e�[�W�j�I���Ǘ�����V�[���N���X
class StageSelectScene : public Scene {
public:
    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �I��UI�摜�Ȃǂ�ǂݍ���
    void Initialize() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���L�[���͂őI����ڂ�X�V���A����(Z)�Ńt�F�[�Y�i�s��Q�[���J�n(GameScene�J��)��s��
    void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���݂̃t�F�[�Y(�L�����I��/��Փx�I��)�ɉ��������j���[��ʂ�`�悷��
    void Draw() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �ǂݍ��񂾉摜���\�[�X��j������
    void Finalize() override;
private:
    int phase_; // 0: Character, 1: Stage
    int ui_button_graph_;
    int wait_count_;
};