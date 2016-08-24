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

    //‘¼‚ÌÕ“Ë”»’è—Ìˆæ‚ÆŒğ·‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
    virtual bool CollisionWith(const ColliderShape *collider) const override;
    virtual bool CollisionDetection(const Circle *collider) const override;
    virtual bool CollisionDetection(const AABB *collider) const override;
    virtual bool CollisionDetection(const OBB *collider) const override;
    virtual bool CollisionDetection(const Capsule *collider) const override;
    virtual bool CollisionDetection(const ConvexHull *collider) const override;

    //‘¼‚ÌÕ“Ë”»’è—Ìˆæ‚Æ‚Ç‚Ì‚æ‚¤‚ÉŒğ·‚µ‚Ä‚¢‚é‚©
    virtual Vector2D CalcDump(const ColliderShape *collider) const override;
    virtual Vector2D CalcDumpWith(const Circle *collider) const override;
    virtual Vector2D CalcDumpWith(const AABB *collider) const override;
    virtual Vector2D CalcDumpWith(const OBB *collider) const override;
    virtual Vector2D CalcDumpWith(const Capsule *collider) const override;
    virtual Vector2D CalcDumpWith(const ConvexHull *collider) const override;

    void SetScale(const Vector2D scale) override;

    void Draw() override;

    //‚ ‚é“_‚©‚ç‚±‚Ì‰~‚Ü‚Å‚Ì‹——£‚Ì2æ‚ğ•Ô‚·
    double SqDistFromPoint(const Vector2D *point, const Circle *sphere) const;

    double GetRadius() const { return _radius; }

private:

    double _radius;

};

