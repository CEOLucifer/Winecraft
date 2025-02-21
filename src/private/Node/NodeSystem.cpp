#include "Node/NodeSystem.h"
#include "Node/Node.h"
#include "Node/ParentNode.h"
#include <memory>
#include "TimeSystem.h"

using namespace std;

void NodeSystem::Update()
{
    if (!root)
        return;
    updateNode(root);
}

void NodeSystem::OnLoad() { root = std::make_shared<ParentNode>(); }

void NodeSystem::updateNode(shared_ptr<Node> node)
{
    if (!node)
        return;
    node->OnUpdate();

    if (auto parentNode = dynamic_pointer_cast<ParentNode>(node))
    {
        for (auto eachChild : parentNode->GetChildNodes())
        {
            // 递归地更新子节点
            updateNode(eachChild);
        }
    }
}
