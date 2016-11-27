#pragma once
#include "ColliderShape.h"
#include <array>

class Triangle : public ColliderShape
{
public:
    Triangle(Vector2D *vertexA, Vector2D *vertexB, Vector2D *vertexC);
    ~Triangle();

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

    void Draw() override;
    std::array<Vector2D*, 3> GetVertexes() const { return _vertexes; };

    bool ContainInTriangle(const Vector2D point) const;
    
private:

    void CalcIntersectDump(const Triangle *collider, const size_t index) const;
    
    Vector2D *_vertexA, *_vertexB, *_vertexC;
    std::array<Vector2D*, 3> _vertexes;

    //
    mutable int _result;
    
    //It is ClosestPoint on Circle or Capsule's Bounding Volume;
    mutable Vector2D _closestCache;

    //交差した辺のキャッシュ
    mutable Vector2D _verticalVecCache;
    //交差した頂点のキャッシュ
    mutable Vector2D _intersectCache;
};

