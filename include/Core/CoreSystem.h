#pragma once

#include "../Singleton.h"
#include "Std/SmartPtr.h"
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

    std::vector<Sp<Node>> addingNodes;
    std::vector<Sp<Node>> removingNodes;

public:
    void UpdateAll();

    void OnLoad() override;

private:
    void _processAddingNodes();

    void _processRemovingNodes();
};