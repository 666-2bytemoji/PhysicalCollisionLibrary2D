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

    //拡大率を含んだ衝突判定のサイズを得る
    Vector2D GetSize() const
    {
        return Vector2D(_baseSize._x * _scale._x, _baseSize._y * _scale._y);
    }

    //拡大率を考慮しない、衝突判定の元のサイズを得る
    Vector2D GetBaseSize() const { return _baseSize; }

    //拡大率を返す
    Vector2D GetScale() const { return _scale; }

    //大きさの拡大率設定
    virtual void SetScale(const Vector2D scale);

    //空間分割をAABB基準で行うため
    //それぞれの形に最大最小を返させるようにする
    virtual double GetMinX() const = 0;
    virtual double GetMaxX() const = 0;
    virtual double GetMinY() const = 0;
    virtual double GetMaxY() const = 0;

    //図形の中心座標を返す
    virtual Vector2D GetCenter() const = 0;

    //他の衝突判定領域と交差しているかどうか
    virtual bool CollisionWith(const ColliderShape *collider) const = 0;
    virtual bool CollisionDetection(const Circle *collider) const = 0;
    virtual bool CollisionDetection(const AABB *collider) const = 0;
    virtual bool CollisionDetection(const OBB *collider) const = 0;
    virtual bool CollisionDetection(const Capsule *collider) const = 0;
    virtual bool CollisionDetection(const Triangle *collider) const = 0;
    virtual bool CollisionDetection(const ConvexHull *collider) const = 0;

    //他の衝突判定領域とどのように交差しているか
    virtual Vector2D CalcDump(const ColliderShape *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Circle *collider) const = 0;
    virtual Vector2D CalcDumpWith(const AABB *collider) const = 0;
    virtual Vector2D CalcDumpWith(const OBB *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Capsule *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Triangle *collider) const = 0;
    virtual Vector2D CalcDumpWith(const ConvexHull *collider) const = 0;

    //境界ボリュームの線を描く
    virtual void Draw() = 0;
    //境界ボリュームを包む矩形を描く
    void DrawAABB();

    //境界ボリュームを包む境界球を生成する
    //Circle* CreateWrapedCircle() const = 0;
    //境界ボリュームを包む境界球の半径を返す
    //double GetWrapedRadius() const = 0;

    bool _isCrossed;

protected:

    //中心座標
    Vector2D *_center;

    //縦横の元サイズ
    Vector2D _baseSize;

    //拡大率。元の大きさにベクトルの成分を掛け合わせる
    Vector2D _scale;
};

