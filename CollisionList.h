#pragma once
#include <utility>
#include <vector>
#include "Collider.h"
#include "DxLib.h"
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

	void Write(Collider *obj1, Collider *obj2);
	unsigned long GetPairNum() const { return colVec.size(); }


	////
	//現在の衝突リストのcapasity
	size_t collCapacity;
	//現在探索中の分木の位置
	size_t index;
	//衝突リスト本体.
	std::vector<std::pair<Collider *, Collider *>>colVec;
};