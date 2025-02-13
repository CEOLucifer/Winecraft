#pragma once

#include "Node.h"
#include "Parentable.h"

class ParentNode : public Node, public Parentable
{};