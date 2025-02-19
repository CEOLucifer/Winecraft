#include "Texture.h"
#include <memory>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>
#include "Debug/Debug.h"

using namespace std;

void TextureFactory::onCreate(std::shared_ptr<Texture> res, std::string path)
{
    Debug::Log(format("loading texture, path:{}", path));

    glGenTextures(1, &res->id);
    glBindTexture(GL_TEXTURE_2D, res->id);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
    //                 GL_REPEAT); 
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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