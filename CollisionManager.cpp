#include "CollisionManager.h"
#include "Solver.h"


CollisionManager::CollisionManager()
    : _spaceTree(-3000, -3000, 3000, 3000, 4)
{
    _treeAgents.reserve(1024);
}


CollisionManager::~CollisionManager()
{
    for (auto oft : _treeAgents)
    {
        oft->RemoveFromLink();
        delete oft;
        oft = nullptr;
    }

    _treeAgents.clear();
    _treeAgents.resize(0);

    _colliders.resize(0);
    _shapes.resize(0);
}


void CollisionManager::SetObjectToTree(Collider *collider)
{
    if (collider->_shape == nullptr)
        return;

    _treeAgents.push_back(new SpaceTreeAgent(collider, _treeAgents.size()));
    _colliders.push_back(collider);
    _shapes.push_back(collider->_shape);
}


void CollisionManager::UpdateTree()
{
    for (auto agent : _treeAgents)
    {
        //��U���X�g����O����
        agent->RemoveFromLink();
        //�ēo�^����
        _spaceTree.RegistColliderShape(agent);

        agent->obj->_shape->_isCrossed = false;
    }
}


void CollisionManager::TestAllCollision()
{
    //����������Ԃ����Փ˃��X�g���쐬
    _spaceTree.SetColList();

    //�Փ˃��X�g���̃y�A���{���ɏՓ˂��邩�`�F�b�N
    for (auto col : _spaceTree._allCollision.colVec)
    {
        auto colA = col.first->_shape;
        auto colB = col.second->_shape;
        auto bodyA = col.first->_physicalbody;
        auto bodyB = col.second->_physicalbody;

        //���ړ�
        bodyA->Integrate();
        bodyB->Integrate();

        //�Փ˔���
        bool result = CollisionDetection(colA, colB);
        colA->_isCrossed = (result || colA->_isCrossed);
        colB->_isCrossed = (result || colB->_isCrossed);

        //�������Ă�����A���ꂼ�ꑊ��Ɠ����������̏���������
        //objA->CollisionWith(*objB);
        //objB->CollisionWith(*objA);

        if (!result)
        {
            bodyA->CancelIntegrate();
            bodyB->CancelIntegrate();
            continue;
        }

        //�Փˉ����I�u�W�F�N�g�쐬
        Solver solver(col.first, col.second);

        //���ړ�����������
        bodyA->CancelIntegrate();
        bodyB->CancelIntegrate();

        //�Փˉ�������
        solver.Solve();
        continue;
    }
}


bool CollisionManager::CollisionDetection(ColliderShape *colA, ColliderShape *colB)
{
    return colA->CollisionWith(colB);
}


void CollisionManager::Debug()
{
    for (auto shape : _shapes)
    {
        shape->Draw();
        shape->DrawAABB();
    }
    for (auto agent : _treeAgents)
    {
        agent->Debug();
    }
    _spaceTree.Debug();
}