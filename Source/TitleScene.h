#pragma once
#include "Scene.h"
#include <vector>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

// �^�C�g����ʂ�`��E�Ǘ�����V�[���N���X
class TitleScene : public Scene {
public:
    TitleScene();
    ~TitleScene();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �^�C�g���w�i�摜��UI�{�^���摜��������ɓǂݍ���
    void Initialize() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �L�[���͂�Ď����AZ�L�[��StageSelectScene�֑J�ڂ�����B�w�i�X�N���[���X�V��s��
    void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �^�C�g�����S�A�w�i�AUI�{�^�������ʂɕ`�悷��
    void Draw() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �ǂݍ��񂾉摜���\�[�X��j������
    void Finalize() override;

private:
    int bgGraph; // �^�C�g���w�i�摜�̃n���h��
    float bgScrollX; // �w�i�X�N���[�����o�̂��߂�X���W�I�t�Z�b�g
    int uiButtonGraph; // �I��{�^��UI�̉摜�n���h��
    std::vector<int> rankings; // �N���A�^�C���Ȃǂ̃����L���O�f�[�^�ێ�
};