#pragma once
#include <vector>
#include "ColliderShape.h"

class ConvexHull : public ColliderShape
{
public:
    ConvexHull(std::vector<Vector2D> points);
    ~ConvexHull();

    double GetMinX() const override;
    double GetMaxX() const override;
    double GetMinY() const override;
    double GetMaxY() const override;
    Vector2D GetCenter() const override;

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

    void SetScale(const Vector2D scale) override;

    void Draw() override;

    //�_�Q����ʕ�𐶐�
    static std::vector<Vector2D> MakeConvexHullShape(std::vector<Vector2D> vertexes);

private:

    void MakeConvexHull(std::vector<Vector2D> vertexes);

    std::vector<Vector2D> _vertexes;

};

