#include "Texture.h"
#include <memory>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>
#include "Debug/Debug.h"

using namespace std;

void TextureFactory::onCreate(Sp<Texture> res, string path)
{
    Debug::Log(format("loading texture, path:{}", path));

    glGenTextures(1, &res->id);
    glBindTexture(GL_TEXTURE_2D, res->id);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
    //                 GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(
        true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data =
        stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // 检查纹理格式
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        Debug::Log(format("Failed to load texture, path:{}", path));
    }
    stbi_image_free(data);
}

Sp<Texture> TextureFactory::CreateRaw(int internalFormat, int format, int width,
                                      int height, int type)
{
    Sp<Texture> This(new Texture);
    glGenTextures(1, &This->id);
    glBindTexture(GL_TEXTURE_2D, This->id);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format,
                 type, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    This->internalFormat = internalFormat;
    This->format = format;
    return This;
}

Sp<Texture> TextureFactory::CreateRGBA(int width, int height)
{
    return CreateRaw(GL_RGBA, GL_RGBA, width, height, GL_UNSIGNED_BYTE);
}

Sp<Texture> TextureFactory::CreateDepthStencil(int width, int height)
{
    return CreateRaw(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, width, height,
                     GL_UNSIGNED_INT_24_8);
}

Sp<Texture> TextureFactory::CreateCube(const std::array<std::string, 6>& paths)
{
    Sp<Texture> This(new Texture);
    glGenTextures(1, &This->id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, This->id);

    // 似乎不需要flip y
    stbi_set_flip_vertically_on_load(false);

    int width, height, nrChannels;
    unsigned char* data;
    for (unsigned int i = 0; i < paths.size(); i++)
    {
        data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width,
                     height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return This;
}

Texture::~Texture() { glDeleteTextures(1, &id); }
