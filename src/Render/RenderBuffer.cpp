#include "glad/glad.h"
#include "Render/RenderBuffer.h"

RenderBuffer::~RenderBuffer() { glDeleteRenderbuffers(1, &id); }

Sp<RenderBuffer> RenderBuffer::Create(int width, int height)
{
    Sp<RenderBuffer> This(new RenderBuffer);
    glGenRenderbuffers(1, &This->id);
    glBindRenderbuffer(GL_RENDERBUFFER, This->id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width,
                          height); // !!! 目前只实现支持GL_DEPTH24_STENCIL8
    return This;
}