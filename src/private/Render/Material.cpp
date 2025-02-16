#include "Render/Material.h"
#include <memory>

using namespace std;

shared_ptr<Material> MaterialFactory::CreateRaw()
{
    shared_ptr<Material> This(new Material);
    return This;
}