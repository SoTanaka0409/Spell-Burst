#pragma once
#include <vector>
#include <memory>

class Bullet;

// ��ʏ�ɑ��݂���S�Ă̒e�I�u�W�F�N�g��Ǘ�����N���X
// (���ݖ��g�p�܂��͋��d�l�̉\�������邪�A���݂���ꍇ�̓��X�g�Ǘ���s��)
class BulletManager {
private:
    std::vector<std::weak_ptr<Bullet>> bullets; 

public:
    BulletManager();
    ~BulletManager();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �Ǘ����Ă��邷�ׂĂ̒e��j�������X�g���ɂ���
    void Initialize();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �e�e��Update��ĂсA����(is_active_ == false)�Ȓe����X�g���珜�O����delete����
    void Update();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �������Ă��邷�ׂĂ̒e��Draw�֐���Ăяo��
    void Draw();

    // [����] x, y: �������W
    // [�o��] �Ȃ�
    // [����p] �V�����e�𐶐����A�Ǘ����X�g�ɒǉ�����
    void SpawnBullet(float x, float y);

    const std::vector<std::weak_ptr<Bullet>>& GetBullets() const { return bullets; }
};
