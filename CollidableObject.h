#pragma once
#include <functional>
#include <vector>
#include "Vector2D.h"
#include "Collider.h"

class CollidableObject
{
public:
    CollidableObject(Vector2D pos, ColliderShape* shape, Physicalbody *rigidbody);
    ~CollidableObject();

    void AddAction(std::function<void()> action);
    virtual void Update();

    void SetPosition(Vector2D pos) { _position = pos; }
    void SetMove(Vector2D move) { _collider._physicalbody->_move = move; }

    void Inegrate() { _collider._physicalbody->Integrate(); }
    void ResetOnFrame();

protected:

    Vector2D _position;
    Collider _collider;

private:

    std::vector<std::function<void()>> _actions;

};

