#pragma once
#include "Vector2D.h"

class Rigidbody
{
public:
    Rigidbody(Vector2D &center);
    ~Rigidbody();

    //�Փ˔����̈ʒu�ړ�
    void Integrate();

    //���݂̈ړ��ʕ��A�ʒu��߂�
    void CancelIntegrate();

    Vector2D _move;

private:

    Vector2D &_center;
};

