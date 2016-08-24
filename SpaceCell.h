#pragma once
#include "SpaceTreeAgent.h"

//グリッド(格子)クラス
//親ノードを持ち、ノードが辿るルートを管理する

class SpaceTreeAgent;

class SpaceCell
{
public:
    bool Push(SpaceTreeAgent* ot, int key);
    void Pop(SpaceTreeAgent* ot);
    void ResetLink(SpaceTreeAgent* ot);

    SpaceCell();
    virtual ~SpaceCell();


    //空間が親ノードを保持する
    SpaceTreeAgent *parantNode;
    SpaceTreeAgent *GetParentNode();

    //モートン番号
    int mKey;
};