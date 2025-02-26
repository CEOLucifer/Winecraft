#pragma once

#include "Singleton.h"
#include "Typedef.h"

class Branch;

class CoreSystem : public Singleton<CoreSystem>
{
private:
    Sp<Branch> root;

public:
    void UpdateAll();

    void OnLoad() override;

    Sp<Branch> GetRoot() { return root; }

private:
    void updateBranch(Sp<Branch> node);
};