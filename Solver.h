#ifndef SOLVER_H
#define SOLVER_H

#include "Vector2D.h"

/*
	衝突応答(衝突時のオブジェクト同士のめり込みを解除するため) の
	計算と移動処理を行うクラス
*/

class Collider;
class ColliderShape;
class Rigidbody;
class Elasticbody;
class Physicalbody;

class Solver
{
public:
    Solver(ColliderShape *collA, ColliderShape *collB, Physicalbody *physA, Physicalbody *physB);
	~Solver();

	//めり込みを解除
	void Solve();

    Vector2D GetNormal(Physicalbody *phys) const 
    {
        if (phys == _physA)
            return _dA; 

        if (phys == _physB)
            return _dB;

        return Vector2D::zero;
    }

private:

    //どれくらいめり込んでるか計算
    void CalcDumpScale();

    //衝突したオブジェクト
    ColliderShape *_collA, *_collB;
    Physicalbody *_physA, *_physB;

    //めり込みを解除するベクトル
    Vector2D _d, _dA, _dB;
};

#endif