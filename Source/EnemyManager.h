#pragma once
#include <vector>
#include <memory>

class Enemy;
class Boss;

// �G�L�����N�^�[�̐����E�i�s�t�F�[�Y�𓝊�����Ǘ��N���X
// �{�X�o������̊Ď���A���݂̃t�F�[�Y�i�E�F�[�u�j�ɉ������G�̃X�|�[���𐧌䂷��
class EnemyManager {
private:
    int spawn_timer_;              // GoiX|[jԊuv^C}[
    int defeated_count_;           // vC[|G̗݌vitF[Yis̏Ɏgpj
    bool boss_spawned_;            // ݂̃tF[YŃ{Xɏoǂ̃tO

    int current_phase_;            // ݂̐istF[YiEF[ujԍ
    int required_kills_;           // ̃tF[Yւ̈ڍsA܂̓{XoɕKvȓG̓
    std::weak_ptr<Boss> current_boss_;           // ݏoĂ{XIuWFNgւ̃|C^ionullptrjĂ{XIuWFNgւ̃|C^ionullptrj

public:
    // RXgN^ / fXgN^
    // [] Ȃ
    // [o] Ȃ
    // [p] IuWFNg̐Ejs
    EnemyManager();
    ~EnemyManager();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �t�F�[�Y�ⓢ�����A�^�C�}�[�Ȃǂ̐i�s�󋵂�������i���Z�b�g�j����
    void Initialize();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �^�C�}�[�ɉ������G�̐����A�{�X�̏o������A�t�F�[�Y�ڍs�����Ȃǂ�s��
    void Update();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ��ʏ�Ɏ��̃t�F�[�Y�܂ł̗v��������A�{�X�o�����̌x��UI�Ȃǂ�`�悷��
    void Draw();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �I�u�W�F�N�g���X�g����񂵁A���S��ԁi�L�������ς݁j�̓G����S�Ƀ���������폜����
    void DeleteEnemy();

    // [����] x, y: �������W
    // [�o��] �Ȃ�
    // [����p] �w�肳�ꂽ���W�Ɋ�{�I�ȓG�I�u�W�F�N�g�𐶐����A�Q�[���V�[���i���X�g���j�ɓo�^����
    void SpawnEnemy(float x, float y);

    // [����] x, y: ��������W, spawnnum: �������鐔
    // [�o��] �Ȃ�
    // [����p] �v���C���[��ǔ�����^�C�v�A�܂��͓���p�^�[���œ����G�𕡐��������V�[���ɓo�^����
    void SpawnEnemy_Target(float x, float y, int spawnnum);

    // --- �Q�b�^�[�E�Z�b�^�[�Q ---

    // [����] �Ȃ�
    // [�o��] int: ���{�X�i����^�C�v�̓G�j�����݉�ʏ�ɂ��鐔
    // [����p] �Ȃ�
    int GetMidBossCount() const;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �G��|�����J�E���g(defeated_count_)��1���Z����i�G�̎��S���ɌĂ΂��z��j
    void AddDefeatedCount() { defeated_count_++; }

    int GetDefeatedCount() const { return defeated_count_; }   // ���݂̓G��������擾
    int GetRequiredKills() const { return required_kills_; }   // �{�X�o�����ɕK�v�ȖڕW��������擾
    bool IsBossSpawned() const { return boss_spawned_; }       // �{�X�����ɏo�����Ă��邩��擾
    int GetCurrentPhase() const { return current_phase_; }     // ���݂̃t�F�[�Y�ԍ���擾
};