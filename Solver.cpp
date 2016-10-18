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

    //めり込みを解消するベクトルを計算
    _d = collA->CalcDump(collB);
    _dB = _d.GetNormalized();
    _dA = _dB * -1;
}


void Solver::Solve()
{
    Physicalbody *physA = _collA->_physicalbody;
    Physicalbody *physB = _collB->_physicalbody;

    //片方だけ動くなら、動く方をめり込み解除
    if (!physA->IsMovable() == MAX_MASS && physB->IsMovable())
    {
        physB->_move += _d;
        return;
    }
    if (!physB->IsMovable() && physA->IsMovable())
    {
        physA->_move -= _d;
        return;
    }

    double total = physA->GetMass() + physB->GetMass();
    physA->_move -= Vector2D(_d * (physB->GetMass() / total));
    physB->_move += Vector2D(_d * (physA->GetMass() / total));
}


Solver::~Solver()
{
}
