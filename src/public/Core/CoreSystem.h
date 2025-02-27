#pragma once

#include "Singleton.h"
#include "Typedef.h"
#include <vector>

class Branch;
class Node;

class CoreSystem : public Singleton<CoreSystem>
{
    friend class Node;
    friend class Branch;

private:
    Sp<Branch> root;

    std::vector<Sp<Node>> nodeVec;

    std::vector<Sp<Node>> destoryingNodes;

public:
    void UpdateAll();

    void OnLoad() override;

private:
    void _processDestroyingNodes();
};