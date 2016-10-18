#include "ConvexHull.h"
#include "AABB.h"
#include "Circle.h"
#include "OBB.h"
#include "Capsule.h"
#include "Triangle.h"
#include "Geometric.h"

ConvexHull::ConvexHull(std::vector<Vector2D> points)
    : _vertexes(std::move(points))
    , ColliderShape(nullptr, Vector2D(1.0, 1.0))
{

}


ConvexHull::~ConvexHull()
{
}


void ConvexHull::MakeConvexHull(std::vector<Vector2D> vertexes)
{
    //凸包を作って
    _vertexes = MakeConvexHullShape(vertexes);

    /*
//重心を出す
    //生成する三角形の3点
    Vector2D sPt, iPt, ePt;
    //2番目のインデックス
    size_t i_idx;
    //3番目
    size_t e_idx;

    for (size_t s_idx = 0; s_idx < _vertexes.size(); ++s_idx)
    {
        i_idx = s_idx + 1;
        e_idx = s_idx + 2;

        //全ての重心を出す
        sPt = vertex[s_idx];
        iPt = vertex[i_idx];
        ePt = vertex[e_idx];

        _vertexes.push_back( std::move(MakeCentPt(sPt, iPt, ePt)) );

        //最後に、3番目の点が凸包の最後の点に着いたら終了
        if (e_idx == vertex.size() - 1)
            break;
    }
    */

    for (auto ct : _vertexes)
    {
        *_center += ct;
    }

    _center->_x /= static_cast<double>(_vertexes.size());
    _center->_y /= static_cast<double>(_vertexes.size());
}



double ConvexHull::GetMinX() const
{
    double minX = MAX;
    for (auto vertex : _vertexes)
    {
        if (vertex._x < minX)
            minX = vertex._x;
    }

    return minX;
}


double ConvexHull::GetMaxX() const
{
    double maxX = MIN;
    for (auto vertex : _vertexes)
    {
        if (maxX < vertex._x)
            maxX = vertex._x;
    }

    return maxX;
}


double ConvexHull::GetMinY() const
{
    double minY = MAX;
    for (auto vertex : _vertexes)
    {
        if (vertex._y < minY)
            minY = vertex._y;
    }

    return minY;
}


double ConvexHull::GetMaxY() const
{
    double maxY = MIN;
    for (auto vertex : _vertexes)
    {
        if (maxY < vertex._y)
            maxY = vertex._y;
    }

    return maxY;
}


Vector2D ConvexHull::GetCenter() const
{
    return *_center;
}


bool ConvexHull::CollisionWith(const ColliderShape *collider) const
{
    return collider->CollisionDetection(this);
}


bool ConvexHull::CollisionDetection(const Circle *collider) const
{
    return false;
}


bool ConvexHull::CollisionDetection(const AABB *collider) const
{
    return false;
}


bool ConvexHull::CollisionDetection(const OBB *collider) const
{
    return false;
}


bool ConvexHull::CollisionDetection(const Capsule *collider) const
{
    return false;
}


bool ConvexHull::CollisionDetection(const Triangle *collider) const
{
    return false;
}


bool ConvexHull::CollisionDetection(const ConvexHull *collider) const
{
    return false;
}


Vector2D ConvexHull::CalcDump(const ColliderShape *collider) const
{
    return collider->CalcDumpWith(this);
}


Vector2D ConvexHull::CalcDumpWith(const Circle *collider) const
{
    return Vector2D::zero;
}


Vector2D ConvexHull::CalcDumpWith(const AABB *collider) const
{
    return Vector2D::zero;
}


Vector2D ConvexHull::CalcDumpWith(const OBB *collider) const
{
    return Vector2D::zero;
}


Vector2D ConvexHull::CalcDumpWith(const Capsule *collider) const
{
    return Vector2D::zero;
}


Vector2D ConvexHull::CalcDumpWith(const Triangle *collider) const
{
    return Vector2D::zero;
}


Vector2D ConvexHull::CalcDumpWith(const ConvexHull *collider) const
{
    return Vector2D::zero;
}


void ConvexHull::SetScale(const Vector2D scale)
{
    _scale = scale;
}


//点群から凸包を生成
std::vector<Vector2D> ConvexHull::MakeConvexHullShape(std::vector<Vector2D> vertexes)
{
    return std::move(vertexes);
}
