#include "glad/glad.h"
#include "Block/Section.h"
#include "Render/Vertex.h"
#include <vector>
#include "Render/Shader/ShaderProgram.h"
#include "Core/Transform.h"
#include "Render/Camera.h"
#include "Core/Branch.h"
#include "Render/Texture.h"


using namespace std;

void Section::Draw(Sp<Camera> camera)
{

}


Section Section::New()
{
    Section This = {};

    return This;
}
