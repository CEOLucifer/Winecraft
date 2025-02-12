#pragma once

#include "Node/NodeSystem.h"
#include <memory>

class ParentNode;

class Node
{
    friend class ParentNode;

protected:
    std::weak_ptr<Node> weak;

private:
    std::shared_ptr<ParentNode> parent;


public:
    virtual void Init() {}
    virtual void Update(float deltaTime) {}

    void Destroy();

    void SetParent(std::shared_ptr<ParentNode> value);

public:
    template <typename T> static std::shared_ptr<T> Create()
    {
        std::shared_ptr<T> This(new T);
        This->weak = This;
        This->SetParent(NodeSystem::Instance()->root);
        This->Init();
        return This;
    }
};