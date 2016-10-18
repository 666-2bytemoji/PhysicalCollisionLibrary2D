#pragma once
#include "Vector2D.h"

const static double MAX_MASS = 99999999;

class Physicalbody
{
public:
    Physicalbody(long mass);
    virtual ~Physicalbody() = 0;

    //仮移動
    virtual void Integrate() = 0;

    //仮移動を取り消す
    virtual void CancelIntegrate() = 0;

    long GetMass() const { return _mass; }
    bool IsMovable() const { return (_mass != MAX_MASS); }

    //1フレーム中の移動ベクトル
    Vector2D _move;

protected:

    //質量(衝突時の押されにくさ)
    long _mass;
};

