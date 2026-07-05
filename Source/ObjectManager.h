#pragma once
#include <list>
#include <vector>
#include "Object2D.h"

// 2D�I�u�W�F�N�g�S�̂̃��C�t�T�C�N���𓝊�����Ǘ��N���X
// ���@�A�G�A�e�A�G�t�F�N�g�Ȃǂ̑S�I�u�W�F�N�g����X�g�ŕێ����A�ꊇ�ōX�V�E�`��E�폜��s��
class ObjectManager
{
public:
    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���X�g�̏�������s���B�f�X�g���N�^�ł͊Ǘ����̑S�I�u�W�F�N�g�̃�������������
    ObjectManager();
    ~ObjectManager();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���X�g�ɓo�^����Ă���S�ẴI�u�W�F�N�g��Draw�֐���Ăяo���A��ʂɕ`�悷��
    void Draw();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���X�g�ɓo�^����Ă���S�ẴI�u�W�F�N�g��Update�֐���Ăяo���A���W���Ԃ�X�V����
    void Update();

    // [����] object2D: �ǉ��ΏۂƂȂ�I�u�W�F�N�g�̃|�C���^
    // [�o��] �Ȃ�
    // [����p] �������ꂽ�I�u�W�F�N�g��Ǘ����X�g(object_2d_list_)�ɒǉ�����
    void AddObject(Object2D* object2D);

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���X�g��̑S�ẴI�u�W�F�N�g������I�ɔj���idelete�j���A���X�g���ɂ���i�V�[���I�����ȂǂɎg�p�j
    void DeleteAll2D();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �폜�t���O�i���S�E���ŏ�ԂȂǁj�������Ă���I�u�W�F�N�g����X�g����T���o���A���S�Ƀ���������j�����ă��X�g���珜�O����
    void DeleteAll2DIfNeeded();

    // [����] tag_: �����������I�u�W�F�N�g�̃^�O�iPlayer, Enemy, Bullet�Ȃǁj
    // [�o��] Object2D*: ����Ɉ�v�����ŏ��̃I�u�W�F�N�g�̃|�C���^�i������Ȃ��ꍇ��nullptr�j
    // [����p] �Ȃ�
    Object2D* GetObject2DByTag(Object2D::Tag2D tag_);

    // [����] tag_: �����������I�u�W�F�N�g�̃^�O
    // [�o��] std::vector<Object2D*>: ����Ɉ�v�����S�ẴI�u�W�F�N�g�̃|�C���^��i�[�����z��
    // [����p] �Ȃ�
    std::vector<Object2D*> GetObject2DListByTag(Object2D::Tag2D tag_);

    // --- �Q�b�^�[�Q ---
    // ���݊Ǘ����Ă���I�u�W�F�N�g�̑�����擾����
    size_t GetObjectCount() const { return object_2d_list_.size(); }

    // �I�u�W�F�N�g�̃��X�g�S�̂ւ̎Q�Ƃ�擾����i�Փ˔���̑������菈���ȂǂɎg�p�j
    const std::list<Object2D*>& GetObjectList() const { return object_2d_list_; }

private:
    std::list<Object2D*> object_2d_list_;   // �ғ����̑S2D�I�u�W�F�N�g��ێ����郊�X�g�i�}���E�폜��������std::list��g�p�j
    Object2D* player_2d_ = nullptr;       // �v���C���[�I�u�W�F�N�g�ւ̃|�C���^�i�����A�N�Z�X�p�̃L���b�V���Ƃ��ĕێ��j
};