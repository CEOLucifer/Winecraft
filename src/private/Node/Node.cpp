#include "Node/ParentNode.h"

void Node::Destroy() {}

void Node::SetParent(std::shared_ptr<ParentNode> value)
{
    if (parent)
    {
        auto& childNodes = parent->childNodes;
        childNodes.erase(std::remove(childNodes.begin(),
                                             childNodes.end(),
                                             weak.lock()),
                                 childNodes.end());
    }

    parent = value;

    if (parent)
    {
        auto& childNodes = parent->childNodes;
        childNodes.push_back(weak.lock());
    }
}