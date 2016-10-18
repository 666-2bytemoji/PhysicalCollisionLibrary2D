#pragma once
#include "ColliderShape.h"

class Capsule : public ColliderShape
{
public:
    Capsule(Vector2D *pt, Vector2D dir, double radius);
    ~Capsule();

    //Inherit Methods
    double GetMinX() const override;
    double GetMaxX() const override;
    double GetMinY() const override;
    double GetMaxY() const override;
    Vector2D GetCenter() const override;

    //他の衝突判定領域と交差しているかどうか
    virtual bool CollisionWith(const ColliderShape *collider) const override;
    virtual bool CollisionDetection(const Circle *collider) const override;
    virtual bool CollisionDetection(const AABB *collider) const override;
    virtual bool CollisionDetection(const OBB *collider) const override;
    virtual bool CollisionDetection(const Capsule *collider) const override;
    virtual bool CollisionDetection(const Triangle *collider) const override;
    virtual bool CollisionDetection(const ConvexHull *collider) const override;

    //他の衝突判定領域とどのように交差しているか
    virtual Vector2D CalcDump(const ColliderShape *collider) const override;
    virtual Vector2D CalcDumpWith(const Circle *collider) const override;
    virtual Vector2D CalcDumpWith(const AABB *collider) const override;
    virtual Vector2D CalcDumpWith(const OBB *collider) const override;
    virtual Vector2D CalcDumpWith(const Capsule *collider) const override;
    virtual Vector2D CalcDumpWith(const Triangle *collider) const override;
    virtual Vector2D CalcDumpWith(const ConvexHull *collider) const override;

    void SetScale(const Vector2D scale) override;

    void Draw() override;

    //Original Methods
    double GetRadius() const { return _radius; }
    Vector2D GetEdgeA() const { return Vector2D(_center->_x - _direction._x * 0.5, _center->_y - _direction._y * 0.5); }
    Vector2D GetEdgeB() const { return Vector2D(_center->_x + _direction._x * 0.5, _center->_y + _direction._y * 0.5); }

private:

    //カプセルの向きと長さ
    Vector2D _direction;

    //太さとキャップの半径
    double _radius;

    mutable Vector2D _closestCache;
};

