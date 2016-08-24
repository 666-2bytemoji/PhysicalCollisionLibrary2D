#include "Capsule.h"
#include "Circle.h"
#include "AABB.h"
#include "OBB.h"
#include "ConvexHull.h"
#include "Geometric.h"


Capsule::Capsule(Vector2D *pt, Vector2D dir, double radius)
    : ColliderShape(pt, Vector2D(radius, dir.GetLength()))
    , _direction(dir)
    , _radius(radius)
{

}


Capsule::~Capsule()
{
}


double Capsule::GetMinX() const
{
    double minPointX = min(GetEdgeA()._x, GetEdgeB()._x);
    return minPointX - _radius;
}


double Capsule::GetMaxX() const
{
    double maxPointX = max(GetEdgeA()._x, GetEdgeB()._x);
    return maxPointX + _radius;
}


double Capsule::GetMinY() const
{
    double minPointY = min(GetEdgeA()._y, GetEdgeB()._y);
    return minPointY - _radius;
}


double Capsule::GetMaxY() const
{
    double maxPointY = max(GetEdgeA()._y, GetEdgeB()._y);
    return maxPointY + _radius;
}


Vector2D Capsule::GetCenter() const
{
    return *_center;
}


bool Capsule::CollisionWith(const ColliderShape *collider) const
{
    return collider->CollisionDetection(this);
}


bool Capsule::CollisionDetection(const Circle *collider) const
{
    auto edgeA = GetEdgeA();
    auto edgeB = GetEdgeB();

    //�J�v�Z���̎���Ƃ̍ŋߐړ_��
    auto closest = GetClosestPointSegmentToPoint(edgeA, edgeB, collider->GetCenter());
    _closestCache = closest - collider->GetCenter();

    //���a���߂��Ƃ���ɂ���Γ�������
    double sqDist = _closestCache.GetSqLength();
    double radius = collider->GetRadius() + _radius;
    return (sqDist <= radius * radius);
}


bool Capsule::CollisionDetection(const AABB *collider) const
{
    auto vertexes = collider->GetVertexes();

    Vector2D edgeA = GetEdgeA();
    Vector2D edgeB = GetEdgeB();
    Vector2D dir = edgeB - edgeA;

    Vector2D closest;
    Vector2D closestOnLine;


    //��ԋ߂��_���ACross�ς����ƂɌ�����
    closestOnLine = vertexes[0];
    double d = abs(Vector2D::Cross(dir.GetNormalized(), vertexes[0] - edgeA));
    for (size_t i = 1; i < 4; ++i)
    {
        double temp = abs(Vector2D::Cross(dir.GetNormalized(), vertexes[i] - edgeA));
        if (temp < d)
        {
            d = temp;
            closestOnLine = vertexes[i];
        }
    }
    closest = GetClosestPointSegmentToPoint(edgeA, edgeB, closestOnLine);

    //�ŋߐړ_����������ɂ��邩�ǂ����𒲂ׂ�
    double dot = Vector2D::Dot(closestOnLine - edgeA, dir);
    bool isOutside = (dot < 0 || dir.GetSqLength() < dot);

    //��������ɂȂ���΁AAABB�̒��_�ȊO�������Ƃ̍ŋߐړ_�ɂȂ�
    if (isOutside)
    {
        //�J�v�Z���̗��[��AABB�̍ŋߐړ_���o����
        Vector2D closestA = collider->GetClosestPoint(&edgeA);
        Vector2D closestB = collider->GetClosestPoint(&edgeB);

        //�߂������ŋߓ_�ɍ̗p
        double lengthA = (closestA - edgeA).GetSqLength();
        double lengthB = (closestB - edgeB).GetSqLength();

        if (lengthA < lengthB)
        {
            closestOnLine = closestA;
            closest = edgeA;
        }
        else
        {
            closestOnLine = closestB;
            closest = edgeB;
        }
    }

    _closestCache = closestOnLine - closest;

    double sqLength = (closestOnLine - closest).GetSqLength();

    //�~�̒��S�_��OBB�̋������~�̔��a���߂���Γ�������
    return (sqLength < (_radius * _radius));
}


bool Capsule::CollisionDetection(const OBB *collider) const
{
    auto vertexes = collider->GetVertexes();

    Vector2D edgeA = GetEdgeA();
    Vector2D edgeB = GetEdgeB();
    Vector2D dir = edgeB - edgeA;

    Vector2D closest;
    Vector2D closestOnLine;


    //��ԋ߂��_���ACross�ς����ƂɌ�����
    closestOnLine = vertexes[0];
    double d = abs(Vector2D::Cross(dir.GetNormalized(), vertexes[0] - edgeA));
    for (size_t i = 1; i < 4; ++i)
    {
        double temp = abs(Vector2D::Cross(dir.GetNormalized(), vertexes[i] - edgeA));
        if (temp < d)
        {
            d = temp;
            closestOnLine = vertexes[i];
        }
    }
    closest = GetClosestPointSegmentToPoint(edgeA, edgeB, closestOnLine);

    //�ŋߐړ_����������ɂ��邩�ǂ����𒲂ׂ�
    double dot = Vector2D::Dot(closestOnLine - edgeA, dir);
    bool isOutside = (dot < 0 || dir.GetSqLength() < dot);

    //��������ɂȂ���΁AAABB�̒��_�ȊO�������Ƃ̍ŋߐړ_�ɂȂ�
    if (isOutside)
    {
        //�J�v�Z���̗��[��AABB�̍ŋߐړ_���o����
        Vector2D closestA = collider->GetClosestPoint(edgeA);
        Vector2D closestB = collider->GetClosestPoint(edgeB);

        //�߂������ŋߓ_�ɍ̗p
        double lengthA = (closestA - edgeA).GetSqLength();
        double lengthB = (closestB - edgeB).GetSqLength();

        if (lengthA < lengthB)
        {
            closestOnLine = closestA;
            closest = edgeA;
        }
        else
        {
            closestOnLine = closestB;
            closest = edgeB;
        }
    }

    _closestCache = closestOnLine - closest;

    double sqLength = (closestOnLine - closest).GetSqLength();

    //�~�̒��S�_��OBB�̋������~�̔��a���߂���Γ�������
    return (sqLength < (_radius * _radius));
}


bool Capsule::CollisionDetection(const Capsule *collider) const
{
    auto edgeA = GetEdgeA();
    auto edgeB = GetEdgeB();
    auto edgeC = collider->GetEdgeA();
    auto edgeD = collider->GetEdgeB();

    auto closestPair = GetClosestPointSegmentToSegment(edgeA, edgeB, edgeC, edgeD);
    _closestCache = closestPair.first - closestPair.second;

    double sqDist = _closestCache.GetSqLength();
    double radius = _radius + collider->_radius;

    return (sqDist <= radius * radius);
}


bool Capsule::CollisionDetection(const ConvexHull *collider) const
{
    return false;
}


Vector2D Capsule::CalcDump(const ColliderShape *collider) const
{
    return collider->CalcDumpWith(this);
}


Vector2D Capsule::CalcDumpWith(const Circle *collider) const
{
    double length = _closestCache.GetLength();

    double ratio = (EPS < length) ? (abs(_radius + collider->GetRadius()) - length) / length : 0;

    return Vector2D(_closestCache._x * ratio, _closestCache._y * ratio);
}


Vector2D Capsule::CalcDumpWith(const AABB *collider) const
{
    double length = _closestCache.GetLength();

    if (length < EPS)
        return Vector2D::zero;

    double ratio = length - _radius;

    auto v = _closestCache.GetNormalized();
    return Vector2D(v._x * ratio, v._y * ratio);
}


Vector2D Capsule::CalcDumpWith(const OBB *collider) const
{
    double length = _closestCache.GetLength();

    if (length < EPS)
        return Vector2D::zero;

    double ratio = length - _radius;

    auto v = _closestCache.GetNormalized();
    return Vector2D(v._x * ratio, v._y * ratio);
}


Vector2D Capsule::CalcDumpWith(const Capsule *collider) const
{
    double length = _closestCache.GetLength();
    double ratio = (abs(_radius + collider->_radius) - length) / length;

    return Vector2D(_closestCache._x * ratio, _closestCache._y * ratio);
}


Vector2D Capsule::CalcDumpWith(const ConvexHull *collider) const
{
    return Vector2D::zero;
}


void Capsule::SetScale(const Vector2D scale)
{
    _scale = scale;
    _radius = _baseSize._x * scale._x;
}
