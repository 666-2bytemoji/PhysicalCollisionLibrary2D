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
    , _result(0)
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
    auto center = (*_vertexA + *_vertexB + *_vertexC) * (1 / 3.0);
    _center->Set(center._x, center._y);
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
    bool result = false;
    bool opponentResult = false;
 
    _result = 0;
    _intersectCache = Vector2D::zero;
    _verticalVecCache = Vector2D::zero;
    collider->_intersectCache = Vector2D::zero;
    collider->_verticalVecCache = Vector2D::zero;
    
    for (size_t i=0; i<3; ++i)
    {
        if(ContainInTriangle(*collider->_vertexes[i]))
        {
            _result = 1;
            _intersectCache = *collider->_vertexes[i];
            CalcIntersectDump(collider, i);
            result = true;
            break;
        }
    }
    
    for (size_t i=0; i<3; ++i)
    {
        if(collider->ContainInTriangle(*_vertexes[i]))
        {
            _result = 2;
            collider->_intersectCache = *_vertexes[i];
            collider->CalcIntersectDump(collider, i);
            /*
            if (!result)
            {
                _intersectCache = collider->_intersectCache;
                _verticalVecCache = collider->_verticalVecCache;
            }
             */
            opponentResult = true;
            break;
        }
    }

    if (result && opponentResult)
    {
        _result = 3;
        _verticalVecCache = (_intersectCache - collider->_intersectCache);
    }

    return (result || opponentResult);
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

#include "DebugDraw.h"

Vector2D Triangle::CalcDumpWith(const Triangle *collider) const
{
    if (_result == 0)
        return Vector2D::zero;
    
    Vector2D center;
    if (_result == 1)
        center = GetCenter();
    
    if (_result == 2)
    {
        center = collider->GetCenter();
        _intersectCache = collider->_intersectCache;
        _verticalVecCache = collider->_verticalVecCache;
    }

    if (_result == 3)
        return _verticalVecCache;
    
    Vector2D verticalNormalized = _verticalVecCache.GetNormalized();
    double length = (_verticalVecCache.GetLength()
                        -  Vector2D::Dot(verticalNormalized, (_intersectCache - center)));

    verticalNormalized *= length;
    
    if (_result == 1)
        verticalNormalized *= -1;
    
    return verticalNormalized;
}


Vector2D Triangle::CalcDumpWith(const ConvexHull *collider) const
{
    return Vector2D::zero;
}

           
bool Triangle::ContainInTriangle(const Vector2D point) const
{
    size_t endIndex = _vertexes.size() - 1;
            
    for (size_t i = 0; i < endIndex; ++i)
    {
        if (Vector2D::Cross( (point - *_vertexes[i]), *_vertexes[i + 1] - *_vertexes[i] ) < EPS)
            return false;
    }
    
    if (Vector2D::Cross((point - *_vertexes[endIndex]), *_vertexes[0] - *_vertexes[endIndex]) < EPS)
        return false;
    
    return true;
}


void Triangle::CalcIntersectDump(const Triangle *collider, const size_t index) const
{
    size_t startIndex = 0;
    size_t endIndex = 0;
    
    switch(index)
    {
    case 0:
        startIndex = 1;
        endIndex = 2;
        break;
    case 1:
        startIndex = 2;
        endIndex = 0;
        break;
    case 2:
        startIndex = 0;
        endIndex = 1;
        break;
    }
    
    auto vec = *_vertexes[endIndex] - *_vertexes[startIndex];
    _verticalVecCache = Vector2D::Cross(vec, false);
    
    auto cross = Vector2D::Cross(GetCenter() - *_vertexes[endIndex], vec.GetNormalized());
    _verticalVecCache *= cross / _verticalVecCache.GetLength();
}
