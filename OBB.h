#pragma once
#include "ColliderShape.h"
#include <vector>

class OBB : public ColliderShape
{
public:
    OBB(Vector2D *pos, double width, double height, double angle);
    ~OBB();

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

    //OBBを回転させる(度数指定)
    void Rotate(double angle);
    void LookAt(Vector2D dir);

    double SqDistFromPoint(const Vector2D point) const;
    Vector2D GetClosestPoint(const Vector2D point) const;

    //頂点の配列を取得
    std::vector<Vector2D> GetVertexes() const;

    bool Contain(Vector2D point) const;

private:

    Vector2D _elemWidth, _elemHeight;
};

