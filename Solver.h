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

class Solver
{
public:
    Solver(Collider *collA, Collider *collB);
	~Solver();

	//めり込みを解除
	void Solve();

    Vector2D GetNormal(Collider *coll) const 
    {
        if (coll == _collA)
            return _dA; 

        if (coll == _collB)
            return _dB;

        return Vector2D::zero;
    }

private:

    //どれくらいめり込んでるか計算
    void CalcDumpScale();

    //衝突したオブジェクト
    const Collider *_collA, *_collB;

    //めり込みを解除するベクトル
    Vector2D _d, _dA, _dB;
};

#endif