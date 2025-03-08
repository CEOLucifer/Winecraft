#include "Core/CoreSystem.h"
#include "Core/Node.h"
#include "Core/Branch.h"
#include <memory>

using namespace std;

void CoreSystem::UpdateAll()
{
    for (auto each : nodeVec)
    {
        if (!each->isDestroyed)
        {
            each->Update();
        }
        else
        {
            destoryingNodes.push_back(each);
        }
    }
    _processDestroyingNodes();
}

void CoreSystem::OnLoad() { root = Branch::Create("root"); }

void CoreSystem::_processDestroyingNodes()
{
    for (auto each : destoryingNodes)
    {
        auto nodeEnd = nodeVec.back();

        // 最后一个元素换到this原来的位置
        nodeVec[each->index] = nodeEnd;

        // 最后一个元素的索引，设置为this的
        nodeEnd->index = each->index;

        nodeVec.pop_back();
    }
    destoryingNodes.clear();
}