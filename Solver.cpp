#include "Solver.h"
#include "Collider.h"

#include "Vector2D.h"
#include "Rigidbody.h"

Solver::Solver(ColliderShape *collA, ColliderShape *collB, Physicalbody *physA, Physicalbody *physB)
    : _collA(collA)
    , _collB(collB)
    , _physA(physA)
    , _physB(physB)
{
    CalcDumpScale();
}


void Solver::CalcDumpScale()
{
    //めり込みを解消するベクトルを計算
    _d = _collA->CalcDump(_collB);
    _dB = _d.GetNormalized();
    _dA = _dB * -1;
}


void Solver::Solve()
{
    //片方だけ動くなら、動く方をめり込み解除
    if (!_physA->IsMovable() == MAX_MASS && _physB->IsMovable())
    {
        _physB->_move += _d;
        return;
    }
    if (!_physB->IsMovable() && _physA->IsMovable())
    {
        _physA->_move -= _d;
        return;
    }

    double total = _physA->GetMass() + _physB->GetMass();
    _physA->_move -= Vector2D(_d * (_physB->GetMass() / total));
    _physB->_move += Vector2D(_d * (_physA->GetMass() / total));
}


Solver::~Solver()
{
}
