#pragma once
#include <vector>
#include "Singleton.h"
#include "Collider.h"
#include "SpaceTreeAgent.h"
#include "SpaceLinerTree.h"


class CollisionManager : public Singleton<CollisionManager>
{
public:
    CollisionManager();
    ~CollisionManager();

    //Collider��Tree�ɓo�^����
    void SetObjectToTree(Collider *collider);
    //Tree�̏����X�V����
    void UpdateTree();

    //�Փ˔�����s��
    void TestAllCollision();

    //�Փ˔���݂̂��O��������Ăяo����悤�ɂ���
    static bool CollisionDetection(ColliderShape *collA, ColliderShape *collB);

    void Debug();

private:

    SpaceLinerTree _spaceTree;
    std::vector<SpaceTreeAgent *> _treeAgents;
    std::vector<Collider *> _colliders;
    std::vector<ColliderShape *> _shapes;
};

#define COLLISION_MGR CollisionManager::GetInstance()