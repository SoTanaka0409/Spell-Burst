#pragma once
#include <list>

class Collider;

class ColliderManager
{
public:
    ColliderManager();
    ~ColliderManager();

    void Update();
    void Draw();

    static ColliderManager* GetInstance()
    {
        if (Instance == nullptr)
        {
            Instance = new ColliderManager();
        }//

        return Instance;
    }

    static void Finalize()
    {
        if (Instance != nullptr)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

public:
    // �R���C�_�[�ǉ�
    void AddCollider(Collider* Collider);

    // �R���C�_�[�S�폜
    void DeleteAllCollider();

    // �폜����K�v�̂���I�u�W�F�N�g������΍폜����
    // note: �S�ẴI�u�W�F�N�g�̍X�V���I�������ɌĂяo��
    void DeleteAllColliderIfNeeded();

    void RemoveCollider(Collider* collider_);
    //// �w�肵���^�O�̃R���C�_�[��擾
    //// note: �Y������I�u�W�F�N�g����������ꍇ�A�ŏ��Ɍ������I�u�W�F�N�g��Ԃ�
    //Collider* GetColliderByTag(Collider::Tag tag_);

    //// �w�肵���^�O�̃R���C�_�[�̃��X�g��擾
    //// note: �Y������I�u�W�F�N�g����������ꍇ�A���X�g�����đS�ẴI�u�W�F�N�g��Ԃ�
    //std::vector<Collider*> GetColliderListByTag(Collider::Tag tag_);
    
    // ���ǉ�
    std::list<Collider*>& GetColliderList();


private:
    std::list<Collider*> collider_list_;    // �R���C�_�[��Ǘ����郊�X�g

    

    static ColliderManager* Instance;
};