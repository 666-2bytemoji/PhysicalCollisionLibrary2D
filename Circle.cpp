#include "Circle.h"
#include "AABB.h"
#include "OBB.h"
#include "Capsule.h"
#include "ConvexHull.h"
#include "Geometric.h"


Circle::Circle(Vector2D *center, double radius)
    : ColliderShape(center, Vector2D(radius, radius))
    , _radius(radius)
{
}


Circle::~Circle()
{
}


Vector2D Circle::GetCenter() const
{
    return Vector2D(_center->_x, _center->_y);
};


double Circle::GetMinX() const
{
    return _center->_x - _radius;
}


double Circle::GetMaxX() const
{
    return _center->_x + _radius;
}


double Circle::GetMinY() const
{
    return _center->_y - _radius;
}


double Circle::GetMaxY() const
{
    return _center->_y + _radius;
}


bool Circle::CollisionWith(const ColliderShape *collider) const
{
    return collider->CollisionDetection(this);
}


bool Circle::CollisionDetection(const Circle *collider) const
{
    double chainedRadius = _radius + collider->_radius;

    return (SqDistFromPoint(_center, collider)
        < (chainedRadius * chainedRadius));
}


bool Circle::CollisionDetection(const AABB *collider) const
{
    //円の中心点とAABBの距離が円の半径より近ければ当たった
    return (collider->SqDistFromPoint(_center) < (_radius * _radius));
}


bool Circle::CollisionDetection(const OBB *collider) const
{
    return collider->CollisionDetection(this);
}


bool Circle::CollisionDetection(const Capsule *collider) const
{
    return collider->CollisionDetection(this);
}


bool Circle::CollisionDetection(const ConvexHull *collider) const
{
    return collider->CollisionDetection(this);
}


Vector2D Circle::CalcDump(const ColliderShape *collider) const
{
    return collider->CalcDumpWith(this);
}


void Circle::SetScale(const Vector2D scale)
{
    _scale = scale;
    _radius = _baseSize._x * scale._x;
}


Vector2D Circle::CalcDumpWith(const Circle *collider) const
{
    //めり込みの向きを出して
    Vector2D dir = *_center - collider->GetCenter();

    //どれくらいめり込んでいるか計算する
    double intersectDepth = (_radius + collider->_radius) - dir.GetLength();

    //向きとめり込み度合を合わせ、めり込み解除のベクトルを計算する
    return dir.GetNormalized() * intersectDepth;
}


Vector2D Circle::CalcDumpWith(const AABB *aabb) const
{
    Vector2D point = *_center;

    //円中心とAABBの最近接点を出す
    Vector2D closestToAABB = aabb->GetClosestPoint(&point);

    //円中心と最近接点を結んでめり込み解除の方向ベクトルをつくる
    Vector2D directionCenterToAABB(closestToAABB, point);

    //どれくらいめり込み解除するかは、
    //めり込み具合 = (円半径 - 円と最近接点の距離)
    double length = directionCenterToAABB.GetLength();
    double dumpScale = _radius - length;

    if (length < EPS)
        return Vector2D::zero;

    directionCenterToAABB *= (dumpScale / length);

    return directionCenterToAABB;
}

Vector2D Circle::CalcDumpWith(const OBB *collider) const
{
    Vector2D vec = collider->CalcDumpWith(this);
    return vec * -1;
}


Vector2D Circle::CalcDumpWith(const Capsule *collider) const
{
    Vector2D vec = collider->CalcDumpWith(this);
    return vec * -1;
}


Vector2D Circle::CalcDumpWith(const ConvexHull *collider) const
{
    Vector2D vec = collider->CalcDumpWith(this);
    return vec * -1;
}


double Circle::SqDistFromPoint(const Vector2D *point, const Circle *sphere) const
{
    Vector2D sphereCenter = sphere->GetCenter();

    //距離の2乗 - 対象円の半径の2乗
    double sqDist =
        (point->_x - sphereCenter._x) * (point->_x - sphereCenter._x)
        + (point->_y - sphereCenter._y) * (point->_y - sphereCenter._y);

    return sqDist;
}
