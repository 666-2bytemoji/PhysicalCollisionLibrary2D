#pragma once
#include "Vector2D.h"

class Vector2D;
class Circle;
class AABB;
class OBB;
class Capsule;
class Triangle;
class ConvexHull;

class ColliderShape
{
public:
    ColliderShape(Vector2D *pivot, Vector2D size);
    virtual ~ColliderShape();

    //�g�嗦���܂񂾏Փ˔���̃T�C�Y�𓾂�
    Vector2D GetSize() const
    {
        return Vector2D(_baseSize._x * _scale._x, _baseSize._y * _scale._y);
    }

    //�g�嗦���l�����Ȃ��A�Փ˔���̌��̃T�C�Y�𓾂�
    Vector2D GetBaseSize() const { return _baseSize; }

    //�g�嗦��Ԃ�
    Vector2D GetScale() const { return _scale; }

    //�傫���̊g�嗦�ݒ�
    virtual void SetScale(const Vector2D scale);

    //��ԕ�����AABB��ōs������
    //���ꂼ��̌`�ɍő�ŏ���Ԃ�����悤�ɂ���
    virtual double GetMinX() const = 0;
    virtual double GetMaxX() const = 0;
    virtual double GetMinY() const = 0;
    virtual double GetMaxY() const = 0;

    //�}�`�̒��S���W��Ԃ�
    virtual Vector2D GetCenter() const = 0;

    //���̏Փ˔���̈�ƌ������Ă��邩�ǂ���
    virtual bool CollisionWith(const ColliderShape *collider) const = 0;
    virtual bool CollisionDetection(const Circle *collider) const = 0;
    virtual bool CollisionDetection(const AABB *collider) const = 0;
    virtual bool CollisionDetection(const OBB *collider) const = 0;
    virtual bool CollisionDetection(const Capsule *collider) const = 0;
    virtual bool CollisionDetection(const Triangle *collider) const = 0;
    virtual bool CollisionDetection(const ConvexHull *collider) const = 0;

    //���̏Փ˔���̈�Ƃǂ̂悤�Ɍ������Ă��邩
    virtual Vector2D CalcDump(const ColliderShape *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Circle *collider) const = 0;
    virtual Vector2D CalcDumpWith(const AABB *collider) const = 0;
    virtual Vector2D CalcDumpWith(const OBB *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Capsule *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Triangle *collider) const = 0;
    virtual Vector2D CalcDumpWith(const ConvexHull *collider) const = 0;

    //���E�{�����[���̐���`��
    virtual void Draw() = 0;
    //���E�{�����[�����ދ�`��`��
    void DrawAABB();

    //���E�{�����[�����ދ��E���𐶐�����
    //Circle* CreateWrapedCircle() const = 0;
    //���E�{�����[�����ދ��E���̔��a��Ԃ�
    //double GetWrapedRadius() const = 0;

    bool _isCrossed;

protected:

    //���S���W
    Vector2D *_center;

    //�c���̌��T�C�Y
    Vector2D _baseSize;

    //�g�嗦�B���̑傫���Ƀx�N�g���̐������|�����킹��
    Vector2D _scale;
};

