#include "SpaceTreeAgent.h"

SpaceTreeAgent::SpaceTreeAgent(ColliderShape *arg_obj, int id)
    : next(nullptr)
    , prev(nullptr)
    , cell(nullptr)
    , _shape(arg_obj)
{
    index = id;
}

SpaceTreeAgent::~SpaceTreeAgent()
{
    prev = nullptr;
    next = nullptr;
    cell = nullptr;
    _shape = nullptr;
}

bool SpaceTreeAgent::RemoveFromLink()
{
    //リンクを管理する空間から外れてたら終了
    if (cell == nullptr)
        return false;

    //自分の所属するリンクを管理する空間にリンクから外れると通知
    cell->Pop(this);

    //外したあとリンクを結びつける
    if (prev != nullptr)
        prev->next = next;
    if (next != nullptr)
        next->prev = prev;

    //最後に初期化
    prev = nullptr;
    next = nullptr;
    cell = nullptr;

    return true;
}

void SpaceTreeAgent::Debug()
{
    //DrawFormatString(0, 120 + index * 32, GetColor(0xff, 0x00, 0x00), "cell: %d", cell->mKey);
}