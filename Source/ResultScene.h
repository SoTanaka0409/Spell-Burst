#pragma once
#include "Scene.h"
#include <vector>

// ���U���g��ʂ̉��o�i������Ȃǁj�Ɏg�p�����p�[�e�B�N���̍\����
struct ResultParticle {
    float x, y;         // �p�[�e�B�N���̌��ݍ��W
    float vx, vy;       // X�����EY�����̈ړ����x�x�N�g��
    float size;         // �p�[�e�B�N���̕`��T�C�Y
    float angle;        // ���݂̕`��p�x�i��]��ԁj
    float rotSpeed;     // ��]���x�i���t���[�����Z�����p�x�j
    int color;          // �p�[�e�B�N���̐F�iDxLib�̃J���[�R�[�h�Ȃǁj
    int life;           // �p�[�e�B�N���̎c������i�t���[�����j
};

// ���U���g�i�Q�[���N���A/�Q�[���I�[�o�[�j��ʂ�`��E�Ǘ�����V�[���N���X
class ResultScene : public Scene {
public:
    // �Q�[���̏��s���ʂ�ێ�����ÓI�t���O�itrue: �N���A/����, false: �Q�[���I�[�o�[/�s�k�j
    // Scene�ڍs�O��GameScene�����珑�������Č��ʂ�n�����߂Ɏg�p����
    static bool isVictory;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �������͎�����p�[�e�B�N���̏������A�w�i�⎩�@�摜�̓ǂݍ��݂�s��
    void Initialize() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �p�[�e�B�N���̍X�V����сA�L�[���́iZ�L�[�j�ɂ��^�C�g���ւ̑J�ڏ�����s��
    void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���s�ɉ������w�i�F�A�e�L�X�g�A���@�摜�i�s�k���͈Ó]���j�A�p�[�e�B�N����`�悷��
    void Draw() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �ǂݍ��񂾉摜���\�[�X��j������
    void Finalize() override;

private:
    std::vector<ResultParticle> particles; // ������Ȃǂ̉��o�p�p�[�e�B�N����Ǘ�����z��
    int stateTimer;                        // �V�[���J�n����̌o�ߎ��Ԃ�v��^�C�}�[�i�����̃t�F�[�h�C������͎�t�̒x���Ɏg�p�j
    int bgGraph;                           // �w�i�摜�̃O���t�B�b�N�n���h���iDxLib�p�j
    int playerGraph;                       // ���@�i�v���C���[�j�摜�̃O���t�B�b�N�n���h��

    // [����] x, y: �`����W, str: ������, color: �����F, outlineColor: ���F, fontHandle: �t�H���g
    // [�o��] �Ȃ�
    // [����p] �w�肳�ꂽ���W�ɉ����t���̕������`�悷��i���F������̂��߂̃w���p�[�֐��j
    void DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle);
};