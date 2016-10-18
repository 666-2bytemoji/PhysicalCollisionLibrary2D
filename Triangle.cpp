#include "Triangle.h"
#include "AABB.h"
#include "Circle.h"
#include "OBB.h"
#include "Capsule.h"
#include "ConvexHull.h"
#include "Geometric.h"


Triangle::Triangle(Vector2D *vertexA, Vector2D *vertexB, Vector2D *vertexC)
    : _vertexA(vertexA)
    , _vertexB(vertexB)
    , _vertexC(vertexC)
    , ColliderShape(nullptr, Vector2D(1, 1))
{
    _vertexes[0] = _vertexA;
    _vertexes[1] = _vertexB;
    _vertexes[2] = _vertexC;

    _center = new Vector2D((*_vertexA + *_vertexB + *_vertexC) * (1 / 3.0));
}


Triangle::~Triangle()
{
}


double Triangle::GetMinX() const
{
    double minX = MAX;
    for (auto vertex : _vertexes)
    {
        if (vertex->_x < minX)
            minX = vertex->_x;
    }

    return minX;
}


double Triangle::GetMaxX() const
{
    double maxX = MIN;
    for (auto vertex : _vertexes)
    {
        if (maxX < vertex->_x)
            maxX = vertex->_x;
    }

    return maxX;
}


double Triangle::GetMinY() const
{
    double minY = MAX;
    for (auto vertex : _vertexes)
    {
        if (vertex->_y < minY)
            minY = vertex->_y;
    }

    return minY;
}


double Triangle::GetMaxY() const
{
    double maxY = MIN;
    for (auto vertex : _vertexes)
    {
        if (maxY < vertex->_y)
            maxY = vertex->_y;
    }

    return maxY;
}


Vector2D Triangle::GetCenter() const
{
    return *_center;
}


bool Triangle::CollisionWith(const ColliderShape *collider) const
{
    return collider->CollisionDetection(this);
}


bool Triangle::CollisionDetection(const Circle *collider) const
{
    auto closestOnTriangle = GetClosestPointTriangleToPoint(*_vertexA, *_vertexB, *_vertexC, collider->GetCenter());
    _closestCache = closestOnTriangle;

    double sqLength = (closestOnTriangle - collider->GetCenter()).GetSqLength();
    double radius = collider->GetRadius();
    return (sqLength < radius * radius);
}


bool Triangle::CollisionDetection(const AABB *collider) const
{
    return false;
}


bool Triangle::CollisionDetection(const OBB *collider) const
{
    return false;
}


bool Triangle::CollisionDetection(const Capsule *collider) const
{
    return false;
}


bool Triangle::CollisionDetection(const Triangle *collider) const
{
    return false;
}


bool Triangle::CollisionDetection(const ConvexHull *collider) const
{
    return false;
}


Vector2D Triangle::CalcDump(const ColliderShape *collider) const
{
    return collider->CalcDumpWith(this);
}


Vector2D Triangle::CalcDumpWith(const Circle *collider) const
{
    auto center = collider->GetCenter();
    return (_closestCache - center).GetNormalized()
        * (collider->GetRadius() - (_closestCache - center).GetLength());
}


Vector2D Triangle::CalcDumpWith(const AABB *collider) const
{
    return Vector2D::zero;
}


Vector2D Triangle::CalcDumpWith(const OBB *collider) const
{
    return Vector2D::zero;
}


Vector2D Triangle::CalcDumpWith(const Capsule *collider) const
{
    return Vector2D::zero;
}


Vector2D Triangle::CalcDumpWith(const Triangle *collider) const
{
    return Vector2D::zero;
}


Vector2D Triangle::CalcDumpWith(const ConvexHull *collider) const
{
    return Vector2D::zero;
}
