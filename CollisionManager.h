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

    //ColliderをTreeに登録する
    void SetObjectToTree(Collider *collider);
    //Treeの情報を更新する
    void UpdateTree();

    //衝突判定を行う
    void TestAllCollision();

    //衝突判定のみを外部からも呼び出せるようにした
    static bool CollisionDetection(ColliderShape *collA, ColliderShape *collB);

    void Debug();

private:

    SpaceLinerTree _spaceTree;
    std::vector<SpaceTreeAgent *> _treeAgents;
    std::vector<Collider *> _colliders;
    std::vector<ColliderShape *> _shapes;
};

#define COLLISION_MGR CollisionManager::GetInstance()