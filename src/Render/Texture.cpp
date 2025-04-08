#include <glad/glad.h>
#include "Render/Texture.h"
#include "stb/stb_image.h"
#include <string>
#include "ArduinoJson.h"
#include <format>

void Texture::Use(int position, int type)
{
    glActiveTexture(position);
    glBindTexture(type, id);
}

void Texture::OnResourceCreation(const JsonDocument& doc)
{
    String targetStr = doc["target"];


    if (targetStr == "2D") // 2D纹理
    {
        String path = doc["path"];
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

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
            // 通过原文件的通道数，判断纹理的格式
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;


            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            Debug::Log(std::format("texture created, path: {}", path));
        }
        else
        {
            Debug::LogError(
                    std::format("Failed to load texture, path:{}", path));
        }
        stbi_image_free(data);
        target = GL_TEXTURE_2D;
        internalFormat = format;
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if (targetStr == "cubeMap") // 天空盒
    {
        JsonArrayConst six = doc["six"];

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        // 似乎不需要flip y
        stbi_set_flip_vertically_on_load(false);

        int width, height, nrChannels;
        unsigned char* data;
        for (unsigned int i = 0; i < six.size(); i++)
        {
            data = stbi_load(six[i].as<String>().c_str(), &width, &height,
                             &nrChannels, 0);

            // 检查纹理格式
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;


            // ！！！！！！！！！！
            // interalformat是程序中表示的格式；而format是图片文件的真实格式，必须正确。
            // internalformat可以和format不一样。
            // 在cubeMap中，六张图片的internalformat必须一致，否则采样是全黑的。在这里设置为GL_RGBA。
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width,
                         height, 0, format, GL_UNSIGNED_BYTE, data);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,
                        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,
                        GL_CLAMP_TO_EDGE);

        target = GL_TEXTURE_CUBE_MAP;
        internalFormat = format;
        Debug::Log(std::format("cube map texture created"));
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

}

Sp<Texture> Texture::CreateRaw(GLenum internalFormat, GLenum format, int width,
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

    glBindTexture(GL_TEXTURE_2D, 0);
    return This;
}

Sp<Texture> Texture::CreateRGBA(int width, int height)
{
    return CreateRaw(GL_RGBA, GL_RGBA, width, height, GL_UNSIGNED_BYTE);
}

Sp<Texture> Texture::CreateDepthStencil(int width, int height)
{
    return CreateRaw(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, width, height,
                     GL_UNSIGNED_INT_24_8);
}

Texture::~Texture()
{ glDeleteTextures(1, &id); }
