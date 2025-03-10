#include "Core/Node.h"
#include "Core/Branch.h"
#include "Core/CoreSystem.h"

void Node::SetParent(Wp<Branch> value)
{
    // 不能设置父节点为自己本身
    if (value.lock() == thisWeak.lock())
    {
        return;
    }

    auto thisBranch = CastTo<Branch>();

    _removeFromParent();

    if (value.expired()) // value为null，应该将parent置为根节点
    {
        // 设置为根节点
        parent = CoreSystem::Instance()->root;
    }
    else
    {
        parent = value;
    }
    // 添加到新的父结点的子链表中
    if (!parent.expired())
    {
        auto newParent = value.lock();
        if (thisBranch)
        {
            newParent->childBranches.push_back(thisBranch);
        }
        else
        {
            newParent->childNodes.push_back(CastTo<Node>());
        }
    }
}

void Node::_removeFromParent()
{
    Sp<Branch> oldParent = parent.lock();

    // 从旧父结点的子链表中移除
    if (oldParent)
    {
        auto thisBranch = CastTo<Branch>();
        if (thisBranch)
        {
            oldParent->childBranches.remove(thisBranch);
        }
        else
        {
            oldParent->childNodes.remove(thisBranch);
        }
    }
}

void Node::DestroyNode()
{
    isDestroyed = true;
    _removeFromParent();

    if (auto thisBranch = CastTo<Branch>())
    {
        thisBranch->_callOnNodeDestroyedOfChildren();
    }
}
