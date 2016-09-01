#include "AABB.h"
#include "Circle.h"
#include "OBB.h"
#include "Capsule.h"
#include "Triangle.h"
#include "ConvexHull.h"


AABB::AABB(Vector2D *center, Vector2D size)
    : ColliderShape(center, size)
{
}


AABB::~AABB()
{
}


Vector2D AABB::GetCenter() const
{
    return Vector2D(_center->_x, _center->_y);
}


double AABB::GetMinX() const
{
    auto size = GetSize();
    return _center->_x - size._x / 2;
}


double AABB::GetMaxX() const
{
    auto size = GetSize();
    return _center->_x + size._x / 2;
}


double AABB::GetMinY() const
{
    auto size = GetSize();
    return _center->_y - size._y / 2;
}


double AABB::GetMaxY() const
{
    auto size = GetSize();
    return _center->_y + size._y / 2;
}


bool AABB::CollisionWith(const ColliderShape *collider) const
{
    return collider->CollisionDetection(this);
}


bool AABB::CollisionDetection(const Circle *collider) const
{
    return collider->CollisionDetection(this);
}


bool AABB::CollisionDetection(const AABB *collider) const
{
    return (collider->GetMinX() < GetMaxX()
        && collider->GetMaxX() > GetMinX()
        && collider->GetMinY() < GetMaxY()
        && collider->GetMaxY() > GetMinY());
}


bool AABB::CollisionDetection(const OBB *collider) const
{
    return collider->CollisionDetection(this);
}


bool AABB::CollisionDetection(const Capsule *collider) const
{
    return collider->CollisionDetection(this);
}


bool AABB::CollisionDetection(const Triangle *collider) const
{
    return false;
}


bool AABB::CollisionDetection(const ConvexHull *collider) const
{
    return collider->CollisionDetection(this);
}


Vector2D AABB::CalcDump(const ColliderShape *collider) const
{
    return collider->CalcDumpWith(this);
}


Vector2D AABB::CalcDumpWith(const Circle *collider) const
{
    Vector2D vec = collider->CalcDumpWith(this);
    return vec * -1;
}


Vector2D AABB::CalcDumpWith(const AABB *collider) const
{
    //�㉺�̂߂荞�ݓx
    double upperIntersection = GetMaxY() - collider->GetMinY();
    double lowerIntersection = collider->GetMaxY() - GetMinY();

    //���E�̂߂荞�ݓx
    double leftIntersection = GetMaxX() - collider->GetMinX();
    double rightIntersection = collider->GetMaxX() - GetMinX();

    //���������Ɛ��������̂߂荞�ݓx
    double verticalIntersection;
    double horizontalIntersection;

    Vector2D dir(*_center, *collider->_center);

    //�㉺�̔���
    if (0 < dir._y * Vector2D::down._y)
    {
        verticalIntersection = -upperIntersection;
    }
    else
    {
        verticalIntersection = lowerIntersection;
    }

    //���E�̔���
    if (0 < dir._x * Vector2D::right._x)
    {
        horizontalIntersection = -leftIntersection;
    }
    else
    {
        horizontalIntersection = rightIntersection;
    }

    //���������̂߂荞�݂�����
    if (horizontalIntersection * horizontalIntersection
    > verticalIntersection * verticalIntersection)
    {
        return Vector2D(0, verticalIntersection);
    }

    return Vector2D(horizontalIntersection, 0);
}


Vector2D AABB::CalcDumpWith(const OBB *collider) const
{
    Vector2D vec = collider->CalcDumpWith(this);
    return vec * -1;
}


Vector2D AABB::CalcDumpWith(const Capsule *collider) const
{
    Vector2D vec = collider->CalcDumpWith(this);
    return vec * -1;
}


Vector2D AABB::CalcDumpWith(const Triangle *collider) const
{
    return Vector2D::zero;
}


Vector2D AABB::CalcDumpWith(const ConvexHull *collider) const
{
    Vector2D vec = collider->CalcDumpWith(this);
    return vec * -1;
}


double AABB::SqDistFromPoint(const Vector2D *point) const
{
    double sqDist = 0.0;
    //�e���ɑ΂��āAAABB����_���͂ݏo�Ă����ꍇ�̋������v�Z�B
    double Dist = point->_x;

    //�_��AABB�̊O�ɂ������炻�̎��̋��������Z
    if (point->_x < GetMinX())
    {
        sqDist += (GetMinX() - point->_x) * (GetMinX() - point->_x);
    }
    else if (GetMaxX()< point->_x)
    {
        sqDist += (point->_x - GetMaxX()) * (point->_x - GetMaxX());
    }

    Dist = point->_y;
    if (point->_y < GetMinY())
    {
        sqDist += (GetMinY() - point->_y) * (GetMinY() - point->_y);
    }
    else if (GetMaxY()< point->_y)
    {
        sqDist += (point->_y - GetMaxY()) * (point->_y - GetMaxY());
    }

    //�����̕�����Ԃ�
    return sqDist;
}


Vector2D AABB::GetClosestPoint(const Vector2D *point) const
{
    Vector2D closest;

    //�_��AABB�̊O�ɂ������炻�̎��̋��������Z
    if (point->_x < GetMinX())
    {
        closest._x = GetMinX();
    }
    else if (GetMaxX() < point->_x)
    {
        closest._x = GetMaxX();
    }
    else
        closest._x = point->_x;

    //�_��AABB�̊O�ɂ������炻�̎��̋��������Z
    if (point->_y < GetMinY())
    {
        closest._y = GetMinY();
    }
    else if (GetMaxY() < point->_y)
    {
        closest._y = GetMaxY();
    }
    else
        closest._y = point->_y;

    return closest;
}


std::vector<Vector2D> AABB::GetVertexes() const
{
    std::vector<Vector2D> vertexes
    {
        Vector2D(GetMinX(), GetMinY())
        , Vector2D(GetMaxX(), GetMinY())
        , Vector2D(GetMaxX(), GetMaxY())
        , Vector2D(GetMinX(), GetMaxY())
    };

    return std::move(vertexes);
}