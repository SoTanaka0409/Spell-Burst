#pragma once
#include <vector>

class Enemy;
class Boss;

// �G�L�����N�^�[�̐����E�i�s�t�F�[�Y�𓝊�����Ǘ��N���X
// �{�X�o������̊Ď���A���݂̃t�F�[�Y�i�E�F�[�u�j�ɉ������G�̃X�|�[���𐧌䂷��
class EnemyManager {
private:
    int spawnTimer;              // �G��o���i�X�|�[���j������Ԋu��v��^�C�}�[
    int defeatedCount;           // �v���C���[���|�����G�̗݌v���i�t�F�[�Y�i�s�̏������Ɏg�p�j
    bool bossSpawned;            // ���݂̃t�F�[�Y�Ń{�X�����ɏo���������ǂ����̃t���O

    int currentPhase;            // ���݂̐i�s�t�F�[�Y�i�E�F�[�u�j�ԍ�
    int requiredKills;           // ���̃t�F�[�Y�ւ̈ڍs�A�܂��̓{�X�o���ɕK�v�ȓG�̓�����
    Boss* currentBoss;           // ���ݏo�����Ă���{�X�I�u�W�F�N�g�ւ̃|�C���^�i���o������nullptr�j

public:
    // �R���X�g���N�^ / �f�X�g���N�^
    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �I�u�W�F�N�g�̐����E�j����s��
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
    // [����p] �G��|�����J�E���g(defeatedCount)��1���Z����i�G�̎��S���ɌĂ΂��z��j
    void AddDefeatedCount() { defeatedCount++; }

    int GetDefeatedCount() const { return defeatedCount; }   // ���݂̓G��������擾
    int GetRequiredKills() const { return requiredKills; }   // �{�X�o�����ɕK�v�ȖڕW��������擾
    bool IsBossSpawned() const { return bossSpawned; }       // �{�X�����ɏo�����Ă��邩��擾
    int GetCurrentPhase() const { return currentPhase; }     // ���݂̃t�F�[�Y�ԍ���擾
};