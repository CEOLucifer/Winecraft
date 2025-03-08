#include "glad/glad.h"
#include "Render/FrameBuffer.h"
#include "Render/Texture.h"
#include "Debug/Debug.h"
#include "Render/RenderBuffer.h"

using namespace std;

FrameBuffer::~FrameBuffer() { glDeleteFramebuffers(1, &id); }

void FrameBuffer::BindTexture(Sp<Texture> tex)
{
    int attachment;
    int internalFormat = tex->GetInternalFormat();
    switch (internalFormat)
    {
    case GL_RGB:
    case GL_RGBA:
        attachment = GL_COLOR_ATTACHMENT0;
        break;
    case GL_DEPTH24_STENCIL8:
        attachment = GL_DEPTH_STENCIL_ATTACHMENT;
        break;
    default:
        Debug::LogError("invalid internal format");
        break;
    }

    BindTexture(tex, attachment);
}

void FrameBuffer::BindTexture(Sp<Texture> tex, int attachment)
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D,
                           tex->GetID(), 0);

    texture = tex;
}

void FrameBuffer::BindRGBA(Sp<Texture> tex)
{
    BindTexture(tex, GL_COLOR_ATTACHMENT0);
}

void FrameBuffer::BindDepthStencil(Sp<Texture> tex)
{
    BindTexture(tex, GL_DEPTH_STENCIL_ATTACHMENT);
}

void FrameBuffer::BindRenderBuffer(Sp<RenderBuffer> renderBuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, renderBuffer->GetID());

    this->renderBuffer = renderBuffer;
}

bool FrameBuffer::IsCompleted()
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

Sp<FrameBuffer> FrameBuffer::Create()
{
    Sp<FrameBuffer> This(new FrameBuffer);
    glGenFramebuffers(1, &This->id);
    return This;
}

Sp<FrameBuffer> FrameBuffer::CreateUtility(int width, int height)
{
    auto This = Create();

    auto rgba = Texture::CreateRGBA(width, height);
    This->BindRGBA(rgba);

    auto renderBuffer = RenderBuffer::Create(width, height);
    This->BindRenderBuffer(renderBuffer);

    assert(This->IsCompleted());
    return This;
}