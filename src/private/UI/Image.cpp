#include "UI/Image.h"
#include "Core/Branch.h"
#include "Render/Renderer.h"


void Image::OnAdded() { renderer = GetParent().lock()->GetChildOrAdd<Renderer>(); }