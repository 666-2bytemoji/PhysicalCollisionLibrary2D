#pragma once
#include "Vector2D.h"

#define min(x, y) (x < y) ? x : y
#define max(x, y) (x < y) ? y : x

//�􉽊w�v�Z���� 0 �Ƃ݂Ȃ����قǏ������l�̊�l
#define EPS 0.00000001
//�􉽋��Ԃł̍ő��l
#define MAX 1000000000
//�􉽋��Ԃł̍ŏ��l
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


//�_�Ɛ����̋�����2�����Ԃ�
static double SqDistSegmentToPoint(Vector2D start, Vector2D end, Vector2D point)
{
    Vector2D se = end - start;
    Vector2D sp = point - start;
    Vector2D ep = point - end;

    double e = Vector2D::Dot(sp, se);

    //�_ �� �����̊O���ɂ����ꍇ
    if (e <= 0.0)
        return Vector2D::Dot(sp, sp);

    double f = Vector2D::Dot(se, se);
    if (f <= e)
        return Vector2D::Dot(ep, ep);

    return Vector2D::Dot(sp, sp) - e * e / f;
}


//�����Ɠ_�̂��ꂼ���̐������̍ŋߐړ_���Ԃ�
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


//����A�Ɛ���B�̂��ꂼ���̐������̍ŋߐړ_���Ԃ�
static std::pair<Vector2D, Vector2D> GetClosestPointSegmentToSegment(Vector2D startA, Vector2D endA, Vector2D startB, Vector2D endB)
{
    //����A
    Vector2D d1 = endA - startA;
    //����B
    Vector2D d2 = endB - startB;

    //����A���̔䗦
    double s = 0.0;
    //����B���̔䗦
    double t = 0.0;

    //�n�_�ǂ����̃x�N�g�����Ƃ��Ă���
    //���s���ǂ����̔����A�����̐����O�ɂ��邩�ǂ����̊m�F�ɗp����
    Vector2D r = startA - startB;

    //����A�̋�����2��
    double a = Vector2D::Dot(d1, d1);
    //����B�̋�����2��
    double e = Vector2D::Dot(d2, d2);

    //����B���ɐ���A�̎n�_���ˉe
    double f = Vector2D::Dot(d2, r);

    //������A��B���_�Ƃ݂Ȃ����Ȃ�
    if (a <= 0 && e <= 0)
    {
        //���̓_�ǂ������Ԃ�
        return std::make_pair(startA, startB);
    }

    //����A���_�̏ꍇ
    if (a <= 0)
    {
        s = 0.0;

        //����B���Ɏˉe���ʂ��N�����v
        t = Clamp(f / e, 1.0, 0.0);
    }
    else
    {
        //����A���ɐ���B�̎n�_���ˉe
        double c = Vector2D::Dot(d1, r);

        //����B���_�̏ꍇ
        if (e <= 0)
        {
            t = 0.0;
            //����A���Ɏˉe���ʂ��N�����v
            s = Clamp(-c / a, 0.0, 1.0);
        }
        else
        {
            double b = Vector2D::Dot(d1, d2);

            /*
            MEMO:
                s = (b * t - c) / a;
                t = (b * s + f) / e;
                �Ƃ��ăK�E�X�����@���g��
            */

            //denom : �L����
            double denom = a * e - b * b;

            //���������s�łȂ��ꍇ
            if (denom != 0.0)
            {
                //s�ɂ��ăK�E�X�̏����@���K�p��
                //����A�ƒ���B�̍ŋߐړ_���v�Z
                s = Clamp((b * f - c * e) / denom, 0.0, 1.0);
            }
            else
            {
                s = 0.0;
            }

            //����B���̐���A�ɑ΂����ŋߐړ_���v�Z
            t = (b * s + f) / e;

            //t�̌��ʂ����Ƃɐ���A�̎ˉe���ʂ��N�����v
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


static bool ContainInConvexHull(const std::vector<Vector2D> &vertexes, const Vector2D &point)
{
    size_t endIndex = vertexes.size() - 1;

    for (size_t i = 0; i < endIndex; ++i)
    {
        //�e���_�łł��������̊O���ɂ��������I��
        if (Vector2D::Cross((point - vertexes[i]), (vertexes[i + 1]) - vertexes[i]) < EPS)
            return false;
    }

    //�Ō��ƍŏ��̒��_�ō��������Ɣ���
    if (Vector2D::Cross((point - vertexes[endIndex]), (vertexes[0] - vertexes[endIndex])) < EPS)
        return false;

    //�����܂Ŕ������炷�ׂĂ̐����̓����ɂ��邱�ƂɂȂ�
    return true;
}


//�x�_(�_�Q���ł��������ɍł������_)�𓾂�
static Vector2D GetSupportPoint(Vector2D start, Vector2D end, std::vector<Vector2D> &vertexes)
{
    double temp = 0;
    double dist = 0;
    Vector2D point;
    Vector2D dir = (end - start).GetNormalized();

    for (size_t i = 0; i < vertexes.size(); ++i)
    {
        //���������ɂ����Ƃ����ϒl���傫���_�������_�Ƃ݂Ȃ�
        temp = Vector2D::Dot(dir, vertexes[i] - start);
        if (dist <= temp)
        {
            dist = temp;
            point = vertexes[i];
        }
    }

    return std::move(point);
}


static Vector2D GetClosestPointTriangleToPoint(Vector2D &a, Vector2D &b, Vector2D &c, Vector2D point)
{
    Vector2D closest;

    //point �� sSeg �̊O�����`�F�b�N
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

    //point �� iSeg �̊O�����`�F�b�N
    Vector2D ia(b, point);
    double d3 = Vector2D::Dot(si, ia);
    double d4 = Vector2D::Dot(se, ia);
    if (0.0 <= d3 && d4 <= d3)
    {
        closest = b;
        return closest;
    }

    //point �� sSeg �� iseg �̐������ɂ��邩�`�F�b�N
    double vc = d1 * d4 - d3 * d2;
    if (vc <= 0.0 && 0.0 <= d1 && d3 <= 0.0)
    {
        double v = d1 / (d1 - d3);
        closest._x = a._x + v * si._x;
        closest._y = a._y + v * si._y;
        return closest;
    }

    //point �� eSeg �̊O�����`�F�b�N
    Vector2D ea(c, point);
    double d5 = Vector2D::Dot(si, ea);
    double d6 = Vector2D::Dot(se, ea);
    if (0.0 <= d6 && d5 <= d6)
    {
        closest = c;
        return closest;
    }

    //point �� sSeg��eSeg�̕ҏ��ɂ��邩�`�F�b�N
    double vb = d5 * d2 - d1 * d6;
    if (vb <= 0.0 && 0.0 <= d2 && d6 <= 0.0)
    {
        double v = d2 / (d2 - d6);
        closest._x = a._x + v * se._x;
        closest._y = a._y + v * se._y;
        return closest;
    }

    //point �� iSeg��eSeg�̕ҏ��ɂ��邩�`�F�b�N
    double va = d3 * d6 - d5 * d4;
    if (va <= 0.0 && 0.0 <= (d4 - d3) && 0.0 <= (d5 - d6))
    {
        double v = (d4 - d3) / ((d4 - d3) + (d5 - d6));
        closest._x = b._x + v * (c._x - b._x);
        closest._y = b._y + v * (c._y - b._y);
        return closest;
    }

    //�����܂ł�����point�͎O�p�`���ɂ����̂ŁA�d�S���W�ŕ\����
    /*double denom = 1.0 / (va + vb + vc);
    double v = vb * denom;
    double w = vc * denom;
    closest._x = b->x + v * si._x + w * se.x;
    closest._y = b->y + v * si._y + w * se._y;*/
    closest = point;
    return closest;
}


//三角形の頂点の並び順を考慮した面積の2倍を返す
//ABCが反時計周りなら +
//時計回りなら -
//線分とみなせないほど近いなら0
static double GetSignedArea2D(const Vector2D &vertexA, const Vector2D &vertexB, const Vector2D &vertexC)
{
    return (vertexA._x - vertexC._x) * (vertexB._y - vertexC._y)
            - (vertexA._y - vertexC._y) * (vertexB._x - vertexC._x);
}


static bool IsIntersect(const Vector2D &startA, const Vector2D &endA,
                 const Vector2D &startB, const Vector2D &endB)
{
    //AとBの始点で作る三角形の面積と
    double a1 = GetSignedArea2D(startA, endA, startB);
    //AとBの終点で作る三角形の面積が
    double a2 = GetSignedArea2D(startA, endA, endB);
    
    //符号が異なるなら、Aに対してBの始点と終点は異なる側にある = 交差している
    return (a1 * a2 > 0);
}