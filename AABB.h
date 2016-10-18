#pragma once
#include "ColliderShape.h"
#include <vector>

/*
X軸とY軸に平行な矩形の衝突判定領域
*/


class AABB : public ColliderShape
{
public:
    AABB(Vector2D *upperLeft, Vector2D size);
    ~AABB();

    double GetMinX() const override;
    double GetMaxX() const override;
    double GetMinY() const override;
    double GetMaxY() const override;

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

    Vector2D GetCenter() const override;

    void Draw() override;

    double SqDistFromPoint(const Vector2D *point) const;
    Vector2D GetClosestPoint(const Vector2D *point) const;

    //頂点の配列を取得
    std::vector<Vector2D> GetVertexes() const;
};