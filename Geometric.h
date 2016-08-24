#pragma once
#include "Vector2D.h"

#define min(x, y) (x < y) ? x : y;
#define max(x, y) (x < y) ? y : x;

//幾何学計算中で 0 とみなせるほど小さい値の基準値
#define EPS 0.00000001
//幾何空間での最大値
#define MAX 1000000000
//幾何空間での最小値
#define MIN -1000000000


template<typename T>
static T Clamp(T value, T min, T max)
{
    if (max < value)
        value = max;
    if (value < min)
        value = min;

    return value;
}


//点と線分の距離の2乗を返す
static double SqDistSegmentToPoint(Vector2D start, Vector2D end, Vector2D point)
{
    Vector2D se = end - start;
    Vector2D sp = point - start;
    Vector2D ep = point - end;

    double e = Vector2D::Dot(sp, se);

    //点 が 線分の外側にある場合
    if (e <= 0.0)
        return Vector2D::Dot(sp, sp);

    double f = Vector2D::Dot(se, se);
    if (f <= e)
        return Vector2D::Dot(ep, ep);

    return Vector2D::Dot(sp, sp) - e * e / f;
}


//線分と点のそれぞれの線分上の最近接点を返す
static Vector2D GetClosestPointSegmentToPoint(Vector2D startA, Vector2D endA, Vector2D point)
{
    Vector2D ab = endA - startA;
    Vector2D d;

    double t = Vector2D::Dot(point - startA, ab);

    if (t <= EPS)
    {
        t = 0.0;
        d = startA;
    }
    else
    {
        double denom = Vector2D::Dot(ab, ab);

        if (denom <= t)
        {
            t = 1.0;
            d = endA;
        }
        else
        {
            t = t / denom;
            d = startA + ab * t;
        }
    }

    return d;
}


//線分Aと線分Bのそれぞれの線分上の最近接点を返す
static std::pair<Vector2D, Vector2D> GetClosestPointSegmentToSegment(Vector2D startA, Vector2D endA, Vector2D startB, Vector2D endB)
{
    //線分A
    Vector2D d1 = endA - startA;
    //線分B
    Vector2D d2 = endB - startB;

    //線分A上の比率
    double s = 0.0;
    //線分B上の比率
    double t = 0.0;

    //始点どうしのベクトルをとっておく
    //平行かどうかの判定、一方の線分外にあるかどうかの確認に用いる
    Vector2D r = startA - startB;

    //線分Aの距離の2乗
    double a = Vector2D::Dot(d1, d1);
    //線分Bの距離の2乗
    double e = Vector2D::Dot(d2, d2);

    //直線B上に線分Aの始点を射影
    double f = Vector2D::Dot(d2, r);

    //線分のAかBが点とみなせるなら
    if (a <= 0 && e <= 0)
    {
        //その点どうしを返す
        return std::make_pair(startA, startB);
    }

    //線分Aが点の場合
    if (a <= 0)
    {
        s = 0.0;

        //線分B上に射影結果をクランプ
        t = Clamp(f / e, 1.0, 0.0);
    }
    else
    {
        //直線A上に線分Bの始点を射影
        double c = Vector2D::Dot(d1, r);

        //線分Bが点の場合
        if (e <= 0)
        {
            t = 0.0;
            //線分A上に射影結果をクランプ
            s = Clamp(-c / a, 0.0, 1.0);
        }
        else
        {
            double b = Vector2D::Dot(d1, d2);

            /*
            MEMO:
                s = (b * t - c) / a;
                t = (b * s + f) / e;
                としてガウス消去法を使う
            */

            //denom : 有理数
            double denom = a * e - b * b;

            //線分が平行でない場合
            if (denom != 0.0)
            {
                //sについてガウスの消去法を適用し
                //直線Aと直線Bの最近接点を計算
                s = Clamp((b * f - c * e) / denom, 0.0, 1.0);
            }
            else
            {
                s = 0.0;
            }

            //直線B上の線分Aに対する最近接点を計算
            t = (b * s + f) / e;

            //tの結果をもとに線分Aの射影結果をクランプ
            if (t < 0.0)
            {
                t = 0.0;
                s = Clamp(-c / a, 0.0, 1.0);
            }
            else if (1.0 < t)
            {
                t = 1.0;
                s = Clamp((b - c) / a, 0.0, 1.0);
            }
        }
    }

    return std::make_pair(startA + d1 * s, startB + d2 * t);
}


//凸包の内部にpointがあるかどうか
static bool ContainInConvexHull(const std::vector<Vector2D> &vertexes, const Vector2D &point)
{
    size_t endIndex = vertexes.size() - 1;

    for (size_t i = 0; i < endIndex; ++i)
    {
        //各頂点でできる線分の外側にあったら終了
        if (Vector2D::Cross((point - vertexes[i]), (vertexes[i + 1]) - vertexes[i]) > EPS)
            return false;
    }

    //最後と最初の頂点で作る線分と判定
    if (Vector2D::Cross((point - vertexes[endIndex]), (vertexes[0] - vertexes[endIndex])) > EPS)
        return false;

    //ここまで抜けたらすべての線分の内側にあることになる
    return true;
}


//支点(点群中である方向に最も遠い点)を得る
static Vector2D GetSupportPoint(Vector2D start, Vector2D end, std::vector<Vector2D> &vertexes)
{
    double temp = 0;
    double dist = 0;
    Vector2D point;
    Vector2D dir = (end - start).GetNormalized();

    for (size_t i = 0; i < vertexes.size(); ++i)
    {
        //ある方向にもっとも内積値が大きい点を遠い点とみなす
        temp = Vector2D::Dot(dir, vertexes[i] - start);
        if (dist <= temp)
        {
            dist = temp;
            point = vertexes[i];
        }
    }

    return std::move(point);
}


static Vector2D GetClosestPointTriangleToPoint(Vector2D &a, Vector2D &b, Vector2D &c, Vector2D &point)
{
    Vector2D closest;

    //point が sSeg の外側かチェック
    Vector2D si(a, b);
    Vector2D se(a, c);
    Vector2D sa(a, point);
    double d1 = Vector2D::Dot(si, sa);
    double d2 = Vector2D::Dot(se, sa);

    if (d1 <= 0.0 && d2 <= 0.0)
    {
        closest = a;
        return closest;
    }

    //point が iSeg の外側かチェック
    Vector2D ia(b, point);
    double d3 = Vector2D::Dot(si, ia);
    double d4 = Vector2D::Dot(se, ia);
    if (0.0 <= d3 && d4 <= d3)
    {
        closest = b;
        return closest;
    }

    //point が sSeg と iseg の線分上にあるかチェック
    double vc = d1 * d4 - d3 * d2;
    if (vc <= 0.0 && 0.0 <= d1 && d3 <= 0.0)
    {
        double v = d1 / (d1 - d3);
        closest._x = a._x + v * si._x;
        closest._y = a._y + v * si._y;
        return closest;
    }

    //point が eSeg の外側かチェック
    Vector2D ea(c, point);
    double d5 = Vector2D::Dot(si, ea);
    double d6 = Vector2D::Dot(se, ea);
    if (0.0 <= d6 && d5 <= d6)
    {
        closest = c;
        return closest;
    }

    //point が sSegとeSegの編上にあるかチェック
    double vb = d5 * d2 - d1 * d6;
    if (vb <= 0.0 && 0.0 <= d2 && d6 <= 0.0)
    {
        double v = d2 / (d2 - d6);
        closest._x = a._x + v * se._x;
        closest._y = a._y + v * se._y;
        return closest;
    }

    //point が iSegとeSegの編上にあるかチェック
    double va = d3 * d6 - d5 * d4;
    if (va <= 0.0 && 0.0 <= (d4 - d3) && 0.0 <= (d5 - d6))
    {
        double v = (d4 - d3) / ((d4 - d3) + (d5 - d6));
        closest._x = b._x + v * (c._x - b._x);
        closest._y = b._y + v * (c._y - b._y);
        return closest;
    }

    //ここまでくるとpointは三角形内にあるので、重心座標で表せる
    /*double denom = 1.0 / (va + vb + vc);
    double v = vb * denom;
    double w = vc * denom;
    closest._x = b->x + v * si._x + w * se.x;
    closest._y = b->y + v * si._y + w * se._y;*/
    closest = point;
    return closest;
}