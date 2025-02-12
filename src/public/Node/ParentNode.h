#pragma once

#include <memory>
#include "Node.h"
#include <vector>

class ParentNode : public Node
{
    friend class Node;

private:
    std::vector<std::shared_ptr<Node>> childNodes;

public:
    const std::vector<std::shared_ptr<Node>>& GetChildNodes()
    {
        return childNodes;
    }
};