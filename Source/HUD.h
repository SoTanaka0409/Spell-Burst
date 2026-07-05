#pragma once

class Player;
class Boss;
class EnemyManager;

// UI���̕`��Ǘ��N���X
// HUD�v�f�̃A�j���[�V�������(�C�[�W���O)��s�����߁A�ÓI�ϐ���ێ�����
class HUD {
public:
    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �C�[�W���O�p�ϐ��Ȃǂ̐ÓI��Ԃ���Z�b�g����
    static void Initialize();

    // [����] player: ���@, enemy_manager_: �G�Ǘ�, boss: �{�X
    // [�o��] �Ȃ�
    // [����p] ���݂�HP���Ɋ�Â��A�\���p�̕�Ԕ䗦�i�C�[�W���O�j��v�Z�E�X�V����
    static void Update(Player* player, EnemyManager* enemy_manager_, Boss* boss);

    // [����] player, enemy_manager_, boss, cutin_timer_: ���o����, cutin_image_handle_: ���o�摜
    // [�o��] �Ȃ�
    // [����p] ��ʏ�̍őO�ʂɊeUI�R���|�[�l���g�i�Q�[�W�A�J�b�g�C�����j��`�悷��
    static void Draw(Player* player, EnemyManager* enemy_manager_, Boss* boss, int cutin_timer_, int cutin_image_handle_);

private:
    static float displayHpRatio; // �A�j���[�V������ԗp��HP�\���䗦
    static float displayXpRatio; // �A�j���[�V������ԗp�̌o���l�\���䗦
    static float displaySpellRatio; // �A�j���[�V������ԗp�̃X�y���Q�[�W�\���䗦
    static float displayBarrierRatio; // �A�j���[�V������ԗp�̃o���A�Q�[�W�\���䗦
    static float bossHpRatio; // �A�j���[�V������ԗp�̃{�XHP�\���䗦
};