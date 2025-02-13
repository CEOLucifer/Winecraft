#include "Node/ParentNode.h"

void Node::Destroy() {}

void Node::SetParentNode(std::shared_ptr<ParentNode> value)
{
    SetParentable(value);
}

void Node::SetParentable(std::shared_ptr<Parentable> value)
{
    if (parent)
    {
        auto& childNodes = parent->childNodes;
        childNodes.erase(
            std::remove(childNodes.begin(), childNodes.end(), weak.lock()),
            childNodes.end());
    }

    parent = value;

    if (parent)
    {
        auto& childNodes = parent->childNodes;
        childNodes.push_back(weak.lock());
    }
}