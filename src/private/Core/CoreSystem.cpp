#include "Core/CoreSystem.h"
#include "Core/Node.h"
#include "Core/Branch.h"
#include <memory>

void CoreSystem::UpdateAll()
{
    if (!root)
        return;
    updateBranch(root);
}

void CoreSystem::OnLoad()
{
    root = std::make_shared<Branch>();
    root->thisWeak = root;
    root->name = "root";
}

void CoreSystem::updateBranch(Sp<Branch> branch)
{
    if (!branch)
        return;

    branch->Update();

    for (Sp<Node> each : branch->childNodes)
    {
        each->Update();
    }

    // 递归地更新子分支
    for (Sp<Branch> each : branch->childBranches)
    {
        updateBranch(each);
    }
}
