#pragma once
#include <utility>
#include <vector>
#include "ColliderShape.h"
#include <algorithm>

class CollList
{
public:

	CollList();
	~CollList();

	void Init();
	void Sort();

	void Reflesh();
	void ResetPos();
	void Debug();

    void Write(ColliderShape *obj1, ColliderShape *obj2);
	unsigned long GetPairNum() const { return colVec.size(); }


	////
	//現在の衝突リストのcapasity
	size_t collCapacity;
	//現在探索中の分木の位置
	size_t index;
	//衝突リスト本体.
    std::vector<std::pair<ColliderShape *, ColliderShape *>>colVec;
};