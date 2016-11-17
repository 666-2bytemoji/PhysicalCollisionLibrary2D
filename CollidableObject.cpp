#include "CollidableObject.h"
#include "../CollidableObjectManager.h"

std::vector<int32_t> CollidableObject::_collidableBitTable(static_cast<int>(Type::TYPE_NUM), INT32_MAX);

CollidableObject::CollidableObject(Vector2D pos, ColliderShape *shape, Physicalbody *rigidbody)
: _position(pos)
, _direction(0, 1)
, _parent(nullptr)
, _collider(shape, rigidbody, this)
, _type(Type::DEFAULT)
{
    OBJECT_MGR->Add(this);
}


CollidableObject::~CollidableObject()
{
    OBJECT_MGR->Remove(this);
    for (auto child : _children)
    {
        if (child != nullptr)
        {
            child->_parent = nullptr;
            OBJECT_MGR->Remove(child);
        }
    }
}


void CollidableObject::ResetOnFrame()
{
    _collider._physicalbody->_move = Vector2D::zero;
}


void CollidableObject::Update()
{
}


void CollidableObject::CollisionWith(CollidableObject &obj, const Solver &solver)
{
}


void CollidableObject::ContactWith(CollidableObject &obj)
{
    
}


void CollidableObject::LateUpdate()
{
}


void CollidableObject::SetCollidableFlag(Type type, Type opponentType, bool flag)
{
    //�ǂ̃I�u�W�F�N�g�̃r�b�g�����X�V���邩�����o��
    int index = static_cast<int>(type);
    int opponentIndex = static_cast<int>(opponentType);
    
    //�ΏۂƂ̔����ɗp�����r�b�g�̌��������o��
    int32_t mine = static_cast<int32_t>(1 << index);
    int32_t opponent = static_cast<int32_t>(1 << opponentIndex);
    
    //�w�茅��0�ɂ������Ȃ��r�b�g���]���Ă���
    if (!flag)
    {
        mine = INT32_MAX - mine;
        opponent = INT32_MAX - opponent;
    }
    
    mine &= INT32_MAX;
    opponent &= INT32_MAX;
    
    //�w�����������o�������̒l�ōX�V
    _collidableBitTable[index] &= opponent;
    _collidableBitTable[opponentIndex] &= mine;
}


bool CollidableObject::IsCollidablePair(Type type, Type opponentType)
{
    int index = static_cast<int>(type);
    int shift = static_cast<int>(opponentType);
    int32_t opponent = static_cast<int32_t>(1 << shift);
    
    int32_t value = (_collidableBitTable[index] & opponent);
    //�ω��Z���� 0 �łȂ����Γ������ׂ��y�A
    return (value != 0);
}