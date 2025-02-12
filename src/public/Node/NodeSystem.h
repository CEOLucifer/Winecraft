#pragma once

#include "Singleton.h"
#include <memory>


class Node;
class ParentNode;

class NodeSystem : public Singleton<NodeSystem>
{
    friend class Node;

private:
    std::shared_ptr<ParentNode> root;

public:
    void Update(float deltaTime);

    void OnLoad() override;

private:
    void updateNode(std::shared_ptr<Node> node, float deltaTime);
};