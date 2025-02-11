#pragma once

#include "Singleton.h"
#include <memory>


class Node;
class ParentNode;

class NodeSystem : public Singleton<NodeSystem>
{
private:
    std::shared_ptr<ParentNode> root;

public:
    void Update(float deltaTime);

private:
    void updateNode(std::shared_ptr<Node> node, float deltaTime);
};