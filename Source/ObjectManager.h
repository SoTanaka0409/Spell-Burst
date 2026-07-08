#pragma once
#include <list>
#include <vector>
#include <memory>
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
    void AddObject(std::shared_ptr<Object2D> object2D);

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
    std::shared_ptr<Object2D> GetObject2DByTag(Object2D::Tag2D tag_);

    // [����] tag_: �����������I�u�W�F�N�g�̃^�O
    // [�o��] std::vector<Object2D*>: ����Ɉ�v�����S�ẴI�u�W�F�N�g�̃|�C���^��i�[�����z��
    // [����p] �Ȃ�
    std::vector<std::shared_ptr<Object2D>> GetObject2DListByTag(Object2D::Tag2D tag_);

    // --- �Q�b�^�[�Q ---
    // ���݊Ǘ����Ă���I�u�W�F�N�g�̑�����擾����
    // --- Qb^[Q ---
    // ݊ǗĂIuWFNg̑擾
    size_t GetObjectCount() const { return object_2d_list_.size(); }

    // IuWFNg̃XgŜւ̎QƂ擾iՓ˔̑菈ȂǂɎgpj
    const std::list<std::shared_ptr<Object2D>>& GetObjectList() const { return object_2d_list_; }

private:
    std::list<std::shared_ptr<Object2D>> object_2d_list_;   // ғ̑S2DIuWFNgێ郊Xgi}E폜std::listgpj
    std::weak_ptr<Object2D> player_2d_;       // vC[IuWFNgւ̃|C^iANZXp̃LbVƂĕێj

public:
    template<typename T, typename... Args>
    static std::weak_ptr<T> Instantiate(Args&&... args);
};

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"

template<typename T, typename... Args>
std::weak_ptr<T> ObjectManager::Instantiate(Args&&... args) {
    auto obj = std::make_shared<T>(std::forward<Args>(args)...);
    Master::sceneManager->GetCurrentScene()->GetObjectManager()->AddObject(obj);
    return obj;
}