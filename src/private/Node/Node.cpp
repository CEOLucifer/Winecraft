#include "Node/Node.h"
#include "Node/ParentNode.h"

void Node::Destroy() {}

void Node::SetParent(std::shared_ptr<ParentNode> value)
{
    if (parent)
    {
        parent->childNodes.erase(std::remove(parent->childNodes.begin(),
                                             parent->childNodes.end(),
                                             weak.lock()),
                                 parent->childNodes.end());
    }

    parent = value;

    if (parent)
    {
        parent->childNodes.push_back(weak.lock());
    }
}