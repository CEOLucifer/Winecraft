#include "Font/Font.h"
#include "ThirdParty/ft.h"

Font::~Font()
{
    // 删除每个字形对应的gl texture
    for(auto each : characterMap)
    {
        glDeleteTextures(1, &each.second.TextureID);
    }
}

void Font::OnResourceCreation(const JsonDocument& doc)
{
    Resource::OnResourceCreation(doc);

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        Debug::LogError("ERROR::FREETYPE: Could not init FreeType Library");
    }

    FT_Face face;
    String ttfPath = doc["ttfPath"];
    if (FT_New_Face(ft, ttfPath.c_str(), 0, &face))
    {
        Debug::LogError("ERROR::FREETYPE: Failed to load font");
    }

    // 此函数设置了字体面的宽度和高度，将宽度值设为0表示我们要从字体面通过给定的高度中动态计算出字形的宽度。
    FT_Set_Pixel_Sizes(face, 0, 48);

    //禁用字节对齐限制
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (u32 c = 0; c < 128; c++)
    {
        // 加载字符的字形
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            Debug::LogWarning("ERROR::FREETYPE: Failed to load Glyph");
            continue;
        }
        // 生成纹理
        u32 textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // 设置纹理选项
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 储存字符供之后使用
        Character character = {
                textureID,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };
        characterMap.insert({c, character});
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}


