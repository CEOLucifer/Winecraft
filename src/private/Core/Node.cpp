#include "Core/Node.h"
#include "Core/Branch.h"

void Node::SetParent(Wp<Branch> value)
{
    Sp<Branch> oldParent = parent.lock();
    auto thisBranch = CastTo<Branch>();

    // 从旧父结点的子链表中移除
    if (oldParent)
    {
        if (thisBranch)
        {
            oldParent->childBranches.remove(thisBranch);
        }
        else
        {
            oldParent->childNodes.remove(thisBranch);
        }
    }

    auto newParent = value.lock();
    parent = value;
    // 添加到新的父结点的子链表中
    if (newParent)
    {
        if (thisBranch)
        {
            newParent->childBranches.push_back(thisBranch);
        }
        else
        {
            newParent->childNodes.push_back(thisWeak.lock());
        }
    }
}