#pragma once

#include <memory>
#include "Node.h"
#include <vector>

class ParentNode : public Node
{
private:
    std::vector<std::shared_ptr<Node>> childNodes;

public:
    const std::vector<std::shared_ptr<Node>>& GetChildNodes()
    {
        return childNodes;
    }

    void AddChildNode(std::shared_ptr<Node> node)
    {
        childNodes.push_back(node);
        node->parent = weak.lock();
    }
};