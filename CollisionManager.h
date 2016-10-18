#pragma once
#include <vector>
#include "../Singleton.h"
#include "Collider.h"
#include "SpaceTreeAgent.h"
#include "SpaceLinerTree.h"
#include "../PoolingSystem.h"


class CollisionManager : public Singleton<CollisionManager>
{
public:
    CollisionManager();
    ~CollisionManager();

    //ColliderをTreeに登録する
    void SetObjectToTree(Collider *collider);
    
    void RemoveObject(Collider *collider);
    
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
    PoolingSystem<Collider> _colliders;
};

#define COLLISION_MGR CollisionManager::GetInstance()