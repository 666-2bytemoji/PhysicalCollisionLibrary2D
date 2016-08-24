#include "OBB.h"
#include "AABB.h"
#include "Circle.h"
#include "Capsule.h"
#include "ConvexHull.h"
#include "Geometric.h"

#include "DxLib.h"


OBB::OBB(Vector2D *pos, double width, double height, double angle)
    : ColliderShape(pos, Vector2D(width, height))
    , _elemWidth(width, 0)
    , _elemHeight(0, height)
{
    _elemWidth.Rotate(angle);
    _elemHeight.Rotate(angle);
}


OBB::~OBB()
{
}


Vector2D OBB::GetCenter() const
{
    return Vector2D(_center->_x, _center->_y);
};


double OBB::GetMinX() const
{
    double wX = _elemWidth._x;
    double hX = _elemHeight._x;

    double minX = - abs(wX) - abs(hX);
    return _center->_x + minX;
}


double OBB::GetMaxX() const
{
    double wX = _elemWidth._x;
    double hX = _elemHeight._x;

    double maxX = abs(wX) + abs(hX);
    return _center->_x + maxX;
}


double OBB::GetMinY() const
{
    double wY = _elemWidth._y;
    double hY = _elemHeight._y;

    double minY = - abs(wY) - abs(hY);
    return _center->_y + minY;
}


double OBB::GetMaxY() const
{
    double wY = _elemWidth._y;
    double hY = _elemHeight._y;

    double maxY = abs(wY) + abs(hY);
    return _center->_y + maxY;
}


bool OBB::CollisionWith(const ColliderShape *collider) const
{
    return collider->CollisionDetection(this);
}


bool OBB::CollisionDetection(const Circle *collider) const
{
    //円の中心点とOBBの距離が円の半径より近ければ当たった
    return (SqDistFromPoint(collider->GetCenter())
        < (collider->GetRadius() * collider->GetRadius()));
}


bool OBB::CollisionDetection(const AABB *collider) const
{
    auto center = collider->GetCenter();
    auto size = collider->GetSize();

    //AABBをOBBとみなしてOBBvsOBBの判定をする
    OBB obb(&center, size._x * 0.5, size._y * 0.5, 0);
    return CollisionDetection(&obb);
}


bool OBB::CollisionDetection(const OBB *collider) const
{
    //ベクトルの内積を算出
    double radA = 0;
    double radB = 0;
    double L = 0;

    //分離軸Be2
    radA = abs(Vector2D::Dot(_elemWidth, collider->_elemHeight))
        + abs(Vector2D::Dot(_elemHeight, collider->_elemHeight));

    radB = Vector2D::Dot(collider->_elemHeight, collider->_elemHeight);

    //(PlayerとSloopの距離をベクトルで得る)・sloop->e2
    L = abs((_center->_x - collider->_center->_x) * collider->_elemHeight._x
        +   (_center->_y - collider->_center->_y) * collider->_elemHeight._y);

    //2つの投影距離の和が距離の投影線より長いと当たってない
    if (radA + radB <= L)
        return false;


    //分離軸Be1
    radA = abs(Vector2D::Dot(_elemWidth, collider->_elemWidth))
        + abs(Vector2D::Dot(_elemHeight, collider->_elemWidth));

    radB = Vector2D::Dot(collider->_elemWidth, collider->_elemWidth);

    //(PlayerとSloopの距離をベクトルで得る)・sloop->e1
    L = abs((_center->_x - collider->_center->_x) * collider->_elemWidth._x
        +   (_center->_y - collider->_center->_y) * collider->_elemWidth._y);

    //お互いの分離軸長がお互いの中心の距離より小さいなら、当たった
    if (radA + radB <= L)
        return false;


    //分離軸Ae2
    radB = abs(Vector2D::Dot(_elemHeight, collider->_elemHeight))
        + abs(Vector2D::Dot(_elemHeight, collider->_elemWidth));

    radA = Vector2D::Dot(_elemHeight, _elemHeight);

    //(PlayerとSloopの距離をベクトルで得る)・obb1->e2
    L = abs((_center->_x - collider->_center->_x) * _elemHeight._x
        +   (_center->_y - collider->_center->_y) * _elemHeight._y);

    //お互いの分離軸長がお互いの中心の距離より小さいなら、当たった
    if (radA + radB <= L)
        return false;
    


    radB = abs(Vector2D::Dot(_elemWidth, collider->_elemWidth))
        + abs(Vector2D::Dot(_elemWidth, collider->_elemHeight));

    radA = Vector2D::Dot(_elemWidth, _elemWidth);

    //(PlayerとSloopの距離をベクトルで得る)・obb1->e2
    L = abs((_center->_x - collider->_center->_x) * _elemWidth._x
        +   (_center->_y - collider->_center->_y) * _elemWidth._y);

    //お互いの分離軸長がお互いの中心の距離より小さいなら、当たった
    if (radA + radB <= L)
        return false;

    return true;
}


bool OBB::CollisionDetection(const Capsule *collider) const
{
    return collider->CollisionDetection(this);
}


bool OBB::CollisionDetection(const ConvexHull *collider) const
{
    return false;
}


Vector2D OBB::CalcDump(const ColliderShape *collider) const
{
    return collider->CalcDumpWith(this);
}


Vector2D OBB::CalcDumpWith(const Circle *collider) const
{
    Vector2D circleCenter = collider->GetCenter();
    Vector2D dir = GetClosestPoint(circleCenter) - circleCenter;

    double length = dir.GetLength();
    if (EPS < length)
        dir *= (collider->GetRadius() - length) / length;

    return dir;
}


Vector2D OBB::CalcDumpWith(const AABB *collider) const
{
    auto center = collider->GetCenter();
    auto size = collider->GetSize();

    //AABBをOBBとみなしてOBBvsOBBの判定をする
    OBB obb(&center, size._x * 0.5, size._y * 0.5, 0);
    return CalcDumpWith(&obb);
}


Vector2D OBB::CalcDumpWith(const OBB *collider) const
{
    auto vertexesA = GetVertexes();
    auto vertexesB = collider->GetVertexes();

    //点の含まれ方から処理パターンを分岐する判定
    std::vector<Vector2D> containedA;
    std::vector<Vector2D> containedB;

    const OBB *obbA = this;
    const OBB *obbB = collider;

    //Aの頂点がB内部にあるか計測
    for (size_t i = 0; i < vertexesA.size(); ++i)
    {
        if (ContainInConvexHull(vertexesB, vertexesA[i]))
            containedA.push_back(vertexesA[i]);
    }

    //Bの頂点がA内部にあるか計測
    for (size_t i = 0; i < vertexesB.size(); ++i)
    {
        if (ContainInConvexHull(vertexesA, vertexesB[i]))
            containedB.push_back(vertexesB[i]);
    }

    //小数点誤差等でcontain判定がなければ終了
    if (containedA.size() == 0 && containedB.size() == 0)
        return Vector2D::zero;

    //(済?)1. 点が1点づつ重なっているパターン
    if (containedA.size() == containedB.size())
    {

            obbA = const_cast<OBB*>(this);
            obbB = const_cast<OBB*>(collider);
        //最近接点どうしを検出して
        Vector2D closestOnA = obbA->GetClosestPoint(*obbB->_center);
        Vector2D closestOnB = obbB->GetClosestPoint(*obbA->_center);

        Vector2D vec = closestOnB - closestOnA;

        if (containedA.size() == 1)
        {
            Vector2D temp = closestOnA;
            closestOnA = closestOnB;
            closestOnB = temp;
            vec.GetRotated(180);
        }

        if (vec.GetSqLength() < EPS)
            return Vector2D::zero;

        //どちらの軸に深くめり込んでいるか出す
        double dotWidth = Vector2D::Dot(obbB->_elemWidth.GetNormalized(), vec);
        double dotHeight = Vector2D::Dot(obbB->_elemHeight.GetNormalized(), vec);

        bool shooter = abs(dotWidth) < abs(dotHeight);
        Vector2D v = (shooter) ? obbB->_elemWidth.GetNormalized() : obbB->_elemHeight.GetNormalized();

        //複数交差した場合(平行 & 頂点が重なった場合)の検出
        /* TODO : closestペアで作るベクトルの大きさ(物体同士が早く動く場合)に対応 */
        //1. 中心点どうしのベクトル上に、最近接点のベクトルがあるか
        double a = abs(Vector2D::Cross( (closestOnB - closestOnA).GetNormalized()
                                        , (*obbA->_center - *obbB->_center).GetNormalized()));
        double b = 0;
        if (a < 0.5)
        {
            //2. 弾きたい方向と中心点は直線状にあるか(重なってるなら直線状にあるはず)
            b = abs(Vector2D::Cross(v, (*obbA->_center - *obbB->_center).GetNormalized()));
            if (1 - 0.01 < b)
                shooter = !shooter;
        }

        if ( shooter )
        {
            v = obbB->_elemWidth.GetNormalized();
            v *= dotWidth;
        }
        else
        {
            v = obbB->_elemHeight.GetNormalized();
            v *= dotHeight;
        }

        DrawFormatStringF(obbA->_center->_x, obbA->_center->_y, GetColor(0xff, 0x00, 0x00), "OBB_A");
        DrawFormatStringF(obbB->_center->_x, obbB->_center->_y, GetColor(0x00, 0xbb, 0x00), "OBB_B");
        DrawFormatStringF(0, 270, GetColor(0x00, 0xbb, 0x00), "a : %f", a);
        DrawFormatStringF(0, 300, GetColor(0x00, 0xbb, 0x00), "b : %f", b);

        DrawCircle(closestOnA._x, closestOnA._y, 3, GetColor(0xff, 0x00, 0x00), true);
        DrawCircle(closestOnB._x, closestOnB._y, 3, GetColor(0x00, 0x00, 0xff), true);
        DrawLine(closestOnA._x, closestOnA._y, closestOnB._x, closestOnB._y, GetColor(0x00, 0x00, 0x00));
//        return Vector2D::zero;

        return v;
    }

    //2(済?). 点が1点のみ重なっているパターン
    if (containedA.size() == 1 || containedB.size() == 1)
    {
        if (containedA.size() == 1)
        {
            obbA = const_cast<OBB*>(this);
            obbB = const_cast<OBB*>(collider);
        }
        else
        {
            obbA = const_cast<OBB*>(collider);
            obbB = const_cast<OBB*>(this);
        }

        std::vector<Vector2D> &contained = (containedA.size() == 1) ? containedA : containedB;

        //対象への最近接点をだす
        Vector2D closest = obbB->GetClosestPoint(*obbA->_center);

        //押し出す方向は中心から最近接点の方向。
        Vector2D vec = (closest - *obbA->_center);

        //押し出す必要が無いなら終了
        if (vec.GetSqLength() < EPS)
            return Vector2D::zero;


        if (containedA.size() == 1)
        {
            Vector2D temp = closest;
            closest = contained[0];
            contained[0] = temp;
        }

        //方向上に最近接点から交差点までの長さ分押し出す
        vec.Normalize();
        vec *= -Vector2D::Dot(vec, (closest - contained[0]));

        DrawCircle(closest._x, closest._y, 3, GetColor(0xff, 0x00, 0x00), true);
        DrawCircle(contained[0]._x, contained[0]._y, 3, GetColor(0x00, 0x00, 0xff), true);
        DrawLine(closest._x, closest._y,
                 closest._x + vec._x, closest._y + vec._y, GetColor(0xff, 0x00, 0x00));
//        return Vector2D::zero;

        return std::move(vec);
    }

    //3. それ以上の点が交差している場合
    if (1 < containedA.size())
    {
        obbA = const_cast<OBB*>(this);
        obbB = const_cast<OBB*>(collider);
    }
    else
    {
        obbA = const_cast<OBB*>(collider);
        obbB = const_cast<OBB*>(this);
    }
    std::vector<Vector2D> &contained = (1 < containedB.size()) ? containedB : containedA;

    //最近接点を取得して
    Vector2D closest = obbB->GetClosestPoint(*obbA->_center);
    //その方向に一番遠い点を出す
    Vector2D support = GetSupportPoint(*obbA->_center, closest, contained);
    Vector2D vec = (*obbA->_center - closest);

    //押し出す必要が無いなら終了
    if (vec.GetSqLength() < EPS)
        return Vector2D::zero;

    if (1 < containedA.size())
    {
        Vector2D temp = closest;
        closest = support;
        support = temp;
    }

    //その点と最近接点を弾けばOK
    vec.Normalize();
    vec *= -Vector2D::Dot(vec, closest - support);

    DrawCircle(closest._x, closest._y, 3, GetColor(0xff, 0x00, 0x00), true);
    DrawCircle(support._x, support._y, 3, GetColor(0x00, 0x00, 0xff), true);
    DrawLine(closest._x, closest._y, closest._x + vec._x, closest._y + vec._y, GetColor(0x00, 0x00, 0xff));
//    return Vector2D::zero;

    //その点と最近接点を弾けばOK
    return std::move(vec);
}


Vector2D OBB::CalcDumpWith(const Capsule *collider) const
{
    Vector2D vec = collider->CalcDumpWith(this);
    return vec * -1;
}


Vector2D OBB::CalcDumpWith(const ConvexHull *collider) const
{
    return Vector2D::zero;
}


void OBB::SetScale(Vector2D scale)
{
    _elemWidth *= scale;
    _elemHeight *= scale;
}


bool OBB::Contain(Vector2D point) const
{
    auto vertexes = GetVertexes();

    for (size_t i = 0; i < 3; ++i)
    {
        //各頂点でできる線分の外側にあったら終了
        if (Vector2D::Cross((point - vertexes[i]), (vertexes[i + 1]) - vertexes[i]) >= 0)
            return false;
    }

    //最後と最初の頂点で作る線分と判定
    if (Vector2D::Cross( (point - vertexes[3]), (vertexes[0] - vertexes[3])) >= 0)
        return false;

    //ここまで抜けたらすべての線分の内側にあることになる
    return true;
}


double OBB::SqDistFromPoint(const Vector2D point) const
{
    //距離の平方
    double sqDist = 0.0;

    //最近接点を出す
    Vector2D closestPoint = GetClosestPoint(point);

    //最近接点と点の距離の平方を返す
    closestPoint -= point;
    sqDist = Vector2D::Dot(closestPoint, closestPoint);
    return sqDist;
}


Vector2D OBB::GetClosestPoint(const Vector2D point) const
{
    Vector2D closest;

    //OBBと点の傾きを得る
    Vector2D OBBsIncVector = point;
    OBBsIncVector -= *_center;

    //OBB分離軸の正規化用ベクトル
    Vector2D OBBsNormalizedElem[2];
    OBBsNormalizedElem[0] = _elemWidth.GetNormalized();
    OBBsNormalizedElem[1] = _elemHeight.GetNormalized();

    //OBBの中心から各分離軸へ投影したときの距離を格納
    double DistFromOBB[2] = { 0, 0 };

    //最近接点はOBBの中心から
    closest._x = _center->_x;
    closest._y = _center->_y;

    //最近接点を出す
    for (int i = 0; i<2; ++i)
    {
        //OBBの傾き軸に垂直に射影して
        //OBBの中央から傾き軸に沿った距離を得る
        DistFromOBB[i] = Vector2D::Dot(OBBsIncVector, OBBsNormalizedElem[i]);
    }

    //OBBの範囲より大きかったらOBB内へ戻す
    if (DistFromOBB[0] > _elemWidth.GetLength()){ DistFromOBB[0] = _elemWidth.GetLength(); }
    if (DistFromOBB[0] < -_elemWidth.GetLength()){ DistFromOBB[0] = -_elemWidth.GetLength(); }

    //OBBの範囲より大きかったらOBB内へ戻す
    if (DistFromOBB[1] > _elemHeight.GetLength()){ DistFromOBB[1] = _elemHeight.GetLength(); }
    if (DistFromOBB[1] < -_elemHeight.GetLength()){ DistFromOBB[1] = -_elemHeight.GetLength(); }

    //各要素の距離を足す
    for (int i = 0; i<2; ++i)
    {
        closest._x += DistFromOBB[i] * OBBsNormalizedElem[i]._x;
        closest._y += DistFromOBB[i] * OBBsNormalizedElem[i]._y;
    }

    return closest;
}


std::vector<Vector2D> OBB::GetVertexes() const
{
    std::vector<Vector2D> vertexes(4, Vector2D::zero);

    vertexes[0] = _elemWidth.GetRotated(180) - _elemHeight + *_center;
    vertexes[1] = _elemWidth - _elemHeight + *_center;
    vertexes[2] = _elemWidth + _elemHeight + *_center;
    vertexes[3] = _elemWidth.GetRotated(180) + _elemHeight + *_center;

    return std::move(vertexes);
}