#pragma once

#include <vector>

class Node;

class Parentable
{
    friend class Node;

private:
    std::vector<std::shared_ptr<Node>> childNodes;

public:
    virtual ~Parentable() {}

    const std::vector<std::shared_ptr<Node>>& GetChildNodes()
    {
        return childNodes;
    }
};