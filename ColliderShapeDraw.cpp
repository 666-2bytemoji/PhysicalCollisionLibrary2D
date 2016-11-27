#include "Circle.h"
#include "AABB.h"
#include "OBB.h"
#include "Capsule.h"
#include "Triangle.h"
#include "ConvexHull.h"
#include "ColliderShape.h"
#include "../DebugDraw.h"


void Circle::Draw()
{
    auto color = _isCrossed ? ColorPalette::RED4 : ColorPalette::BLACK4;
    DrawCircle(*_center, _radius, color, false);
}


void AABB::Draw()
{
    auto color = _isCrossed ? ColorPalette::RED4 : ColorPalette::BLACK4;

    DrawRectWithPoint(
        static_cast<float>(GetMinX())
        , static_cast<float>(GetMinY())
        , static_cast<float>(GetMaxX())
        , static_cast<float>(GetMaxY())
        , color
        , false);

    DrawCircle(*_center, 3, color, true);
}


void OBB::Draw()
{
    auto color = _isCrossed ? ColorPalette::RED4 : ColorPalette::BLACK4;
    auto vertexes = GetVertexes();

    DrawLine(vertexes[0], vertexes[1], color);
    DrawLine(vertexes[1], vertexes[2], color);
    DrawLine(vertexes[2], vertexes[3], color);
    DrawLine(vertexes[3], vertexes[0], color);

    DrawLine(*_center, *_center + _elemWidth, color);
    DrawLine(*_center, *_center + _elemHeight, color);
    
    DrawCircle(*_center, 3, color, true);
}


void Capsule::Draw()
{
    auto color = _isCrossed ? ColorPalette::RED4 : ColorPalette::BLACK4;

    auto edgeA = GetEdgeA();
    auto edgeB = GetEdgeB();

    DrawCircle(edgeA, _radius, color, false);
    DrawCircle(edgeB, _radius, color, false);

    Vector2D vertical = _direction;
    vertical.Rotate(90);
    vertical *= _radius / vertical.GetLength();

    DrawLine(edgeB + vertical
             , edgeA + vertical
             , color);
    DrawLine(edgeB - vertical
             , edgeA - vertical
             , color);
    
}


void Triangle::Draw()
{
    auto color = _isCrossed ? ColorPalette::RED4 : ColorPalette::BLACK4;
    auto vertexes = GetVertexes();
    
    DrawLine(*vertexes[0], *vertexes[1], color);
    DrawLine(*vertexes[1], *vertexes[2], color);
    DrawLine(*vertexes[2], *vertexes[0], color);

    /*
    DrawLine( (*vertexes[0] + *vertexes[1]) * 0.5
             , (*vertexes[0] + *vertexes[1]) * 0.5 + Vector2D::Cross((*vertexes[1] - *vertexes[0]), false), color);
    */
     
    auto center = GetCenter();
    DrawCircle(center, 3, ColorPalette::BLACK4, true);
    //DrawLine(center, center + _verticalVecCache, ColorPalette::GREEN4);
}


void ConvexHull::Draw()
{
    auto color = _isCrossed ? ColorPalette::RED4 : ColorPalette::BLACK4;

    DrawLine( *(_vertexes.end() - 1), _vertexes[0], color);

    for (size_t i = 1; i < _vertexes.size(); ++i)
    {
        DrawLine(_vertexes[i-1], _vertexes[i], color);
    }
}


void ColliderShape::DrawAABB()
{
    auto color = _isCrossed ? ColorPalette::RED4 : ColorPalette::BLACK4;
    
    DrawRectWithPoint(
        static_cast<int>(GetMinX())
        , static_cast<int>(GetMinY())
        , static_cast<int>(GetMaxX())
        , static_cast<int>(GetMaxY())
        , color
        , false
        );
}