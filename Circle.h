#pragma once
#include "ColliderShape.h"

class Circle : public ColliderShape
{
public:
    Circle(Vector2D *center, double radius);
    ~Circle();

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

    //ある点からこの円までの距離の2乗を返す
    double SqDistFromPoint(const Vector2D *point, const Circle *sphere) const;

    double GetRadius() const { return _radius; }

private:

    double _radius;

};

