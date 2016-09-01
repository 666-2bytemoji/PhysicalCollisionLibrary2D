#ifndef SOLVER_H
#define SOLVER_H

#include "Vector2D.h"

/*
	�Փˉ���(�Փˎ��̃I�u�W�F�N�g���m�̂߂荞�݂��������邽��) ��
	�v�Z�ƈړ��������s���N���X
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

	//�߂荞�݂�����
	void Solve();

private:

	//�ǂꂭ�炢�߂荞��ł邩�v�Z
	void CalcDumpScale();

	//�Փ˂����I�u�W�F�N�g
	const Collider *_collA, *_collB;

	//�߂荞�݂���������x�N�g��
	Vector2D d;
};

#endif