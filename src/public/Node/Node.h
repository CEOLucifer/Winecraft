#pragma once

#include "Node/NodeSystem.h"
#include "Parentable.h"
#include <memory>

class ParentNode;
class Parentable;


class Node
{
protected:
    std::weak_ptr<Node> weak;

private:
    std::shared_ptr<Parentable> parent;


public:
    virtual void OnInit() {}

    virtual void OnUpdate(float deltaTime) {}

    virtual void OnDestory() {}

    void Destroy();

    void SetParentNode(std::shared_ptr<ParentNode> value);

    void SetParentable(std::shared_ptr<Parentable> value);

    template <typename T> std::shared_ptr<T> CastTo()
    {
        return std::dynamic_pointer_cast<T>(weak.lock());
    }

public:
    template <typename T> static std::shared_ptr<T> Create()
    {
        std::shared_ptr<T> This(new T);
        This->weak = This;
        This->SetParentNode(NodeSystem::Instance()->GetRoot());
        This->OnInit();
        return This;
    }
};