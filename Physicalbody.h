#pragma once
#include "Vector2D.h"

class Physicalbody
{
public:
    Physicalbody();
    virtual ~Physicalbody() = 0;

    //�Փ˔����̈ʒu�ړ�
    virtual void Integrate() = 0;

    //���݂̈ړ��ʕ��A�ʒu��߂�
    virtual void CancelIntegrate() = 0;

    Vector2D _move;

private:

};

