#pragma once

#include <memory>

class ParentNode;

class Node
{
    friend class ParentNode;

private:
    std::shared_ptr<ParentNode> parent;
    std::weak_ptr<ParentNode> weak;


public:
    virtual void Start() {}
    virtual void Update(float deltaTime) {}
};