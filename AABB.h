#pragma once
#include "ColliderShape.h"
#include <vector>

/*
    X����Y���ɕ��s�ȋ�`�̏Փ˔���̈�
*/

class Circle;

class AABB : public ColliderShape
{
public:
    AABB(Vector2D *upperLeft, Vector2D size);
    ~AABB();

    double GetMinX() const override;
    double GetMaxX() const override;
    double GetMinY() const override;
    double GetMaxY() const override;

    //���̏Փ˔���̈�ƌ������Ă��邩�ǂ���
    virtual bool CollisionWith(const ColliderShape *collider) const override;
    virtual bool CollisionDetection(const Circle *collider) const override;
    virtual bool CollisionDetection(const AABB *collider) const override;
    virtual bool CollisionDetection(const OBB *collider) const override;
    virtual bool CollisionDetection(const Capsule *collider) const override;
    virtual bool CollisionDetection(const ConvexHull *collider) const override;

    //���̏Փ˔���̈�Ƃǂ̂悤�Ɍ������Ă��邩
    virtual Vector2D CalcDump(const ColliderShape *collider) const override;
    virtual Vector2D CalcDumpWith(const Circle *collider) const override;
    virtual Vector2D CalcDumpWith(const AABB *collider) const override;
    virtual Vector2D CalcDumpWith(const OBB *collider) const override;
    virtual Vector2D CalcDumpWith(const Capsule *collider) const override;
    virtual Vector2D CalcDumpWith(const ConvexHull *collider) const override;

    Vector2D GetCenter() const override;

    void Draw() override;

    double SqDistFromPoint(const Vector2D *point) const;
    Vector2D GetClosestPoint(const Vector2D *point) const;

    //���_�̔z����擾
    std::vector<Vector2D> GetVertexes() const;
};