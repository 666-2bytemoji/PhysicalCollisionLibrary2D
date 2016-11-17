#pragma once
#include "Vector2D.h"

class Vector2D;
class Circle;
class AABB;
class OBB;
class Capsule;
class Triangle;
class ConvexHull;
class Collider;

class ColliderShape
{
    friend class CollisionManager;
public:
    ColliderShape(Vector2D *pivot, Vector2D size);
    virtual ~ColliderShape();

    //境界ボリュームの拡大率を踏まえた大きさを取得する
    Vector2D GetSize() const
    {
        return Vector2D(_baseSize._x * _scale._x, _baseSize._y * _scale._y);
    }

    //境界ボリュームの拡大率を考慮しないときの大きさを取得する
    Vector2D GetBaseSize() const { return _baseSize; }

    //境界ボリュームの拡大率を取得する
    Vector2D GetScale() const { return _scale; }

    void SetCollider(Collider* collider) { _collider = collider; }
    Collider* GetColliderPtr() const { return _collider; }

    //境界ボリュームの拡大率を設定する
    virtual void SetScale(const Vector2D scale);

    //各軸においての最大最小点を返す
    virtual double GetMinX() const = 0;
    virtual double GetMaxX() const = 0;
    virtual double GetMinY() const = 0;
    virtual double GetMaxY() const = 0;

    //中心座標を取得する
    virtual Vector2D GetCenter() const = 0;

    //境界ボリュームどうしが交差しているかどうか
    virtual bool CollisionWith(const ColliderShape *collider) const = 0;
    virtual bool CollisionDetection(const Circle *collider) const = 0;
    virtual bool CollisionDetection(const AABB *collider) const = 0;
    virtual bool CollisionDetection(const OBB *collider) const = 0;
    virtual bool CollisionDetection(const Capsule *collider) const = 0;
    virtual bool CollisionDetection(const Triangle *collider) const = 0;
    virtual bool CollisionDetection(const ConvexHull *collider) const = 0;

    //交差を解除する際のベクトルを得る
    virtual Vector2D CalcDump(const ColliderShape *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Circle *collider) const = 0;
    virtual Vector2D CalcDumpWith(const AABB *collider) const = 0;
    virtual Vector2D CalcDumpWith(const OBB *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Capsule *collider) const = 0;
    virtual Vector2D CalcDumpWith(const Triangle *collider) const = 0;
    virtual Vector2D CalcDumpWith(const ConvexHull *collider) const = 0;

    //境界ボリュームの描画
    virtual void Draw() = 0;
    //境界ボリュームを包める大きさのAABBを描画する
    void DrawAABB();

    //境界ボリュームを包める大きさの球を得る
    //Circle* CreateWrapedCircle() const = 0;
    //境界ボリュームを包める大きさの球の半径
    //double GetWrapedRadius() const = 0;

    bool _isCrossed;

    //判定のみで物理処理を行わないかどうか
    bool _isDetectionOnly;

protected:

    //中心点
    Vector2D *_center;

    //拡大率を考慮しないとき(拡大率 1,1)の大きさ
    Vector2D _baseSize;

    //拡大率
    Vector2D _scale;

    Collider* _collider;
};

