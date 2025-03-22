#include "Core/CoreSystem.h"
#include "Core/Node.h"
#include "Core/Branch.h"
#include <memory>

using namespace std;

void CoreSystem::UpdateAll()
{
    for (auto each: nodeVec)
    {
        if (!each->isDestroyed)
        {
            each->Update();
        }
        else
        {
            removingNodes.push_back(each);
        }
    }
    _processAddingNodes();
    _processRemovingNodes();
}

void CoreSystem::OnLoad()
{ root = Branch::NewBranch("root"); }

void CoreSystem::_processAddingNodes()
{
    for (auto each: addingNodes)
    {
        nodeVec.push_back(each);
        each->index = nodeVec.size() - 1;
    }
    addingNodes.clear();
}

void CoreSystem::_processRemovingNodes()
{
    for (auto each: removingNodes)
    {
        auto nodeEnd = nodeVec.back();

        // 最后一个元素换到this原来的位置
        nodeVec[each->index] = nodeEnd;

        // 最后一个元素的索引，设置为this的
        nodeEnd->index = each->index;

        nodeVec.pop_back();
    }
    removingNodes.clear();
}