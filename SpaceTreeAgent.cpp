#include "SpaceTreeAgent.h"

SpaceTreeAgent::SpaceTreeAgent(Collider *arg_obj, int id)
    : next(nullptr)
    , prev(nullptr)
    , cell(nullptr)
    , obj(arg_obj)
{
    index = id;
}

SpaceTreeAgent::~SpaceTreeAgent()
{
    prev = nullptr;
    next = nullptr;
    cell = nullptr;
    obj = nullptr;
}

bool SpaceTreeAgent::RemoveFromLink()
{
    //�����N���Ǘ������Ԃ���O��Ă���I��
    if (cell == nullptr)
        return false;

    //�����̏������郊���N���Ǘ������ԂɃ����N����O���ƒʒm
    cell->Pop(this);

    //�O�������ƃ����N�����т���
    if (prev != nullptr)
        prev->next = next;
    if (next != nullptr)
        next->prev = prev;

    //�Ō�ɏ�����
    prev = nullptr;
    next = nullptr;
    cell = nullptr;

    return true;
}

void SpaceTreeAgent::Debug()
{
    DrawFormatString(0, 120 + index * 32, GetColor(0xff, 0x00, 0x00), "cell: %d", cell->mKey);
}