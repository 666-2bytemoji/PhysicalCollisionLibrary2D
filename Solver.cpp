#include "Solver.h"
#include "Collider.h"

#include "Vector2D.h"
#include "Rigidbody.h"

Solver::Solver(Collider *collA, Collider *collB)
    : _collA(collA)
    , _collB(collB)
{
    CalcDumpScale();
}


void Solver::CalcDumpScale()
{
    const ColliderShape *collA = _collA->_shape;
    const ColliderShape *collB = _collB->_shape;

    //�߂荞�݂���������x�N�g�����v�Z
    d = collA->CalcDump(collB);
}

void Solver::Solve()
{
    Rigidbody *physA = _collA->_rigidbody;
    Rigidbody *physB = _collB->_rigidbody;

    physA->_move -= Vector2D(d * 0.5);
    physB->_move += Vector2D(d * 0.5);

    /*
    //�ǂ���������Ȃ�A�������߂荞�݉���
    if ((physA->_isMovable && physB->_isMovable)
        || (!physA->_isMovable && !physB->_isMovable))
    {
        physA->_move -= Vector2D(d * 0.5);
        physB->_move += Vector2D(d * 0.5);
        return;
    }

    //�Е����������Ȃ�A���������߂荞�݉���
    if (!physA->_isMovable && physB->_isMovable)
    {
        physB->_move += d;
        return;
    }
    if (!physB->_isMovable && physA->_isMovable)
    {
        physA->_move -= d;
        return;
    }
    */

}

Solver::~Solver()
{
}
