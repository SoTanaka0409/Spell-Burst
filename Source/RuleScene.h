#pragma once
#include "Scene.h"

// �������⃋�[���i�`���[�g���A���j��X���C�h�`���ŕ\������V�[���N���X
class RuleScene : public Scene {
public:
    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �e�X���C�h�i�摜�j��ǂݍ��ݔz��Ɋi�[����
    void Initialize() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���E�L�[�ŃX���C�h��؂�ւ��AZ�L�[�܂��͍ŏI�X���C�h���y�[�W��StageSelectScene�֑J�ڂ���
    void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���ݑI�����Ă��郋�[���̃X���C�h�摜����сA�����̃i�r�Q�[�V�����e�L�X�g��`�悷��
    void Draw() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �ǂݍ��񂾑S�ẴX���C�h�摜��j������
    void Finalize() override;
private:
    int rule_graphs_[6];
    int current_slide_;
};