#pragma once
#include <vector>
#include "../Utility/Singleton.h"
#include "../Utility/PoolingSystem.h"
#include "ColliderShape.h"
#include "SpaceTreeAgent.h"
#include "SpaceLinerTree.h"


class CollisionManager : public Singleton<CollisionManager>
{
public:
    CollisionManager();
    ~CollisionManager();

    //ColliderをTreeに登録する
    void SetObjectToTree(ColliderShape *collider);
    
    void RemoveObject(ColliderShape *collider);
    
    void Clear();
    
    //Treeの情報を更新する
    void UpdateTree();

    //衝突判定を行う
    void TestAllCollision();

    //衝突判定のみを外部からも呼び出せるようにした
    static bool CollisionDetection(ColliderShape *collA, ColliderShape *collB);

    void Debug();

private:

    SpaceLinerTree _spaceTree;
    PoolingSystem<SpaceTreeAgent> _treeAgents;
    PoolingSystem<ColliderShape> _colliders;

    long _detectionCount;
};

#define COLLISION_MGR CollisionManager::GetInstance()