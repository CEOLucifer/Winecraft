#include "Node/NodeSystem.h"
#include "Node/Node.h"
#include "Node/ParentNode.h"
#include <memory>

using namespace std;

void NodeSystem::Update(float deltaTime)
{
    if (!root)
        return;
    updateNode(root, deltaTime);
}

void NodeSystem::OnLoad() { root = std::make_shared<ParentNode>(); }

void NodeSystem::updateNode(shared_ptr<Node> node, float deltaTime)
{
    if (!node)
        return;
    node->Update(deltaTime);

    if (auto parentNode = dynamic_pointer_cast<ParentNode>(node))
    {
        for (auto eachChild : parentNode->GetChildNodes())
        {
            // 递归地更新子节点
            updateNode(eachChild, deltaTime);
        }
    }
}
