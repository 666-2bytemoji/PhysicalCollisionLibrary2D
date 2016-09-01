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

    //‘¼‚ÌÕ“Ë”»’è—Ìˆæ‚ÆŒğ·‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
    virtual bool CollisionWith(const ColliderShape *collider) const override;
    virtual bool CollisionDetection(const Circle *collider) const override;
    virtual bool CollisionDetection(const AABB *collider) const override;
    virtual bool CollisionDetection(const OBB *collider) const override;
    virtual bool CollisionDetection(const Capsule *collider) const override;
    virtual bool CollisionDetection(const Triangle *collider) const override;
    virtual bool CollisionDetection(const ConvexHull *collider) const override;

    //‘¼‚ÌÕ“Ë”»’è—Ìˆæ‚Æ‚Ç‚Ì‚æ‚¤‚ÉŒğ·‚µ‚Ä‚¢‚é‚©
    virtual Vector2D CalcDump(const ColliderShape *collider) const override;
    virtual Vector2D CalcDumpWith(const Circle *collider) const override;
    virtual Vector2D CalcDumpWith(const AABB *collider) const override;
    virtual Vector2D CalcDumpWith(const OBB *collider) const override;
    virtual Vector2D CalcDumpWith(const Capsule *collider) const override;
    virtual Vector2D CalcDumpWith(const Triangle *collider) const override;
    virtual Vector2D CalcDumpWith(const ConvexHull *collider) const override;

    void Draw() override;
    std::array<Vector2D*, 3> GetVertexes() const { return _vertexes; };

private:

    Vector2D *_vertexA, *_vertexB, *_vertexC;
    std::array<Vector2D*, 3> _vertexes;

    mutable Vector2D _closestCache;
};

