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
	//���݂̏Փ˃��X�g��capasity
	size_t collCapacity;
	//���ݒT�����̕��؂̈ʒu
	size_t index;
	//�Փ˃��X�g�{��.
	std::vector<std::pair<Collider *, Collider *>>colVec;
};