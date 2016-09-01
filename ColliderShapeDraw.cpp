#include "DxLib.h"
#include "Circle.h"
#include "AABB.h"
#include "OBB.h"
#include "Capsule.h"
#include "Triangle.h"
#include "ConvexHull.h"
#include "ColliderShape.h"


void Circle::Draw()
{
    auto red = _isCrossed ? 0xff : 0x00;

    DrawCircle(
        static_cast<int>(_center->_x)
        , static_cast<int>(_center->_y)
        , static_cast<int>(_radius)
        , GetColor(red, 0x00, 0x00)
        , false);
}


void AABB::Draw()
{
    auto red = _isCrossed ? 0xff : 0x00;

    DrawBox(
        static_cast<int>(GetMinX())
        , static_cast<int>(GetMinY())
        , static_cast<int>(GetMaxX())
        , static_cast<int>(GetMaxY())
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);

    DrawCircle(static_cast<int>(_center->_x), static_cast<int>(_center->_y), 3, GetColor(red, 0x00, 0x00), true);
}


void OBB::Draw()
{
    auto red = _isCrossed ? 0xff : 0x00;

    auto vertexes = GetVertexes();

    DrawLine(
        static_cast<int>(vertexes[0]._x)
        , static_cast<int>(vertexes[0]._y)
        , static_cast<int>(vertexes[1]._x)
        , static_cast<int>(vertexes[1]._y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);

    DrawLine(
        static_cast<int>(vertexes[1]._x)
        , static_cast<int>(vertexes[1]._y)
        , static_cast<int>(vertexes[2]._x)
        , static_cast<int>(vertexes[2]._y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);

    DrawLine(
        static_cast<int>(vertexes[2]._x)
        , static_cast<int>(vertexes[2]._y)
        , static_cast<int>(vertexes[3]._x)
        , static_cast<int>(vertexes[3]._y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);

    DrawLine(
        static_cast<int>(vertexes[3]._x)
        , static_cast<int>(vertexes[3]._y)
        , static_cast<int>(vertexes[0]._x)
        , static_cast<int>(vertexes[0]._y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);

    DrawCircle(static_cast<int>(_center->_x), static_cast<int>(_center->_y), 3, GetColor(red, 0x00, 0x00), true);
}


void Capsule::Draw()
{
    auto red = _isCrossed ? 0xff : 0x00;

    auto edgeA = GetEdgeA();
    auto edgeB = GetEdgeB();

    DrawCircle(
        static_cast<int>(edgeA._x)
        , static_cast<int>(edgeA._y)
        , static_cast<int>(_radius)
        , GetColor(red, 0x00, 0x00)
        , false);

    DrawCircle(
        static_cast<int>(edgeB._x)
        , static_cast<int>(edgeB._y)
        , static_cast<int>(_radius)
        , GetColor(red, 0x00, 0x00)
        , false);

    Vector2D vertical = _direction;
    vertical.Rotate(90);
    vertical *= _radius / vertical.GetLength();

    DrawLine(
        static_cast<int>(edgeB._x + vertical._x)
        , static_cast<int>(edgeB._y + vertical._y)
        , static_cast<int>(edgeA._x + vertical._x)
        , static_cast<int>(edgeA._y + vertical._y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);
    DrawLine(
        static_cast<int>(edgeB._x - vertical._x)
        , static_cast<int>(edgeB._y - vertical._y)
        , static_cast<int>(edgeA._x - vertical._x)
        , static_cast<int>(edgeA._y - vertical._y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);
}


void Triangle::Draw()
{
    auto vertexes = GetVertexes();

    auto red = _isCrossed ? 0xff : 0x00;

    DrawLine(
        static_cast<int>(vertexes[0]->_x)
        , static_cast<int>(vertexes[0]->_y)
        , static_cast<int>(vertexes[1]->_x)
        , static_cast<int>(vertexes[1]->_y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);

    DrawLine(
        static_cast<int>(vertexes[1]->_x)
        , static_cast<int>(vertexes[1]->_y)
        , static_cast<int>(vertexes[2]->_x)
        , static_cast<int>(vertexes[2]->_y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);

    DrawLine(
        static_cast<int>(vertexes[2]->_x)
        , static_cast<int>(vertexes[2]->_y)
        , static_cast<int>(vertexes[0]->_x)
        , static_cast<int>(vertexes[0]->_y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);
}


void ConvexHull::Draw()
{
    auto red = _isCrossed ? 0xff : 0x00;

    DrawLine(
        static_cast<int>( (_vertexes.end() - 1)->_x )
        , static_cast<int>((_vertexes.end() - 1)->_y)
        , static_cast<int>(_vertexes[0]._x)
        , static_cast<int>(_vertexes[0]._y)
        , static_cast<int>(GetColor(red, 0x00, 0x00))
        , false);

    for (size_t i = 1; i < _vertexes.size(); ++i)
    {
        DrawLine(
            static_cast<int>(_vertexes[i-1]._x)
            , static_cast<int>(_vertexes[i-1]._y)
            , static_cast<int>(_vertexes[i]._x)
            , static_cast<int>(_vertexes[i]._y)
            , static_cast<int>(GetColor(red, 0x00, 0x00))
            , false);
    }
}


void ColliderShape::DrawAABB()
{
    DrawBox(
        static_cast<int>(GetMinX())
        , static_cast<int>(GetMinY())
        , static_cast<int>(GetMaxX())
        , static_cast<int>(GetMaxY())
        , static_cast<int>(GetColor(0xff, 0x00, 0xff))
        , false);
}