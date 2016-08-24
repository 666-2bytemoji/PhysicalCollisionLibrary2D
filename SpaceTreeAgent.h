#pragma once
#include "DxLib.h"
#include "SpaceCell.h"
#include "Collider.h"

class SpaceCell;
class Collider;

//オブジェクトのツリー登録を担う
class SpaceTreeAgent
{
public:
    SpaceTreeAgent(Collider* shape, int id);
    virtual ~SpaceTreeAgent();

    bool RemoveFromLink();


    //自身の登録空間
    SpaceCell *cell;

    //自身の当り判定
    Collider *obj;

    //衝突リストの、前後のオブジェクトを持つ格子への双方向リンク
    SpaceTreeAgent *next, *prev;

    //線型四分木のインデックス
    int index;



    void Debug();
};