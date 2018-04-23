#include "texture.h"
#include "stb_image.h"
#include "shader.h"

#include <cassert>
#include <iostream>


extern Shader shader;

Texture::Texture()
{
    hasTransparency=false;
};

Texture::Texture(const std::string& fileName1, const std::string& fileName2, const std::string& fileName3)
{
    int width1, height1, numComponents1;
    int width2, height2, numComponents2;
    int width3, height3, numComponents3;
    unsigned char* imageData1 = stbi_load((fileName1).c_str(), &width1, &height1, &numComponents1, 4);
    unsigned char* imageData2 = stbi_load((fileName2).c_str(), &width2, &height2, &numComponents2, 4);
    unsigned char* imageData3 = stbi_load((fileName3).c_str(), &width3, &height3, &numComponents3, 4);

    if(imageData1 == NULL)
        std::cerr << "Texture loading failed for texture1" << fileName1 << std::endl;
    if(imageData2 == NULL)
        std::cerr << "Texture loading failed for texture2" << fileName2 << std::endl;
    if(imageData3 == NULL)
        std::cerr << "Texture loading failed for texture2" << fileName3 << std::endl;

    //first texture - texture
    glGenTextures(3, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData1);

    //second texture - normal map
    glBindTexture(GL_TEXTURE_2D, m_texture+sizeof(m_texture));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData2);

    //third texture - height map
    glBindTexture(GL_TEXTURE_2D, m_texture+sizeof(m_texture)+sizeof(m_texture));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width3, height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData3);


    stbi_image_free(imageData1);
    stbi_image_free(imageData2);
    stbi_image_free(imageData3);

    hasTransparency=false;
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

void Texture::LoadTexture(const std::string& fileName1, const std::string& fileName2, const std::string& fileName3)
{
    int width1, height1, numComponents1;
    int width2, height2, numComponents2;
    int width3, height3, numComponents3;
    unsigned char* imageData1 = stbi_load((fileName1).c_str(), &width1, &height1, &numComponents1, 4);
    unsigned char* imageData2 = stbi_load((fileName2).c_str(), &width2, &height2, &numComponents2, 4);
    unsigned char* imageData3 = stbi_load((fileName3).c_str(), &width3, &height3, &numComponents3, 4);

    if(imageData1 == NULL)
        std::cerr << "Texture loading failed for texture1" << fileName1 << std::endl;
    if(imageData2 == NULL)
        std::cerr << "Texture loading failed for texture2" << fileName2 << std::endl;
    if(imageData3 == NULL)
        std::cerr << "Texture loading failed for texture2" << fileName3 << std::endl;

    //first texture - texture
    glGenTextures(3, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData1);

    //second texture - normal map
    glBindTexture(GL_TEXTURE_2D, m_texture+sizeof(m_texture));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData2);

    //third texture - height map
    glBindTexture(GL_TEXTURE_2D, m_texture+sizeof(m_texture)+sizeof(m_texture));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width3, height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData3);


    stbi_image_free(imageData1);
    stbi_image_free(imageData2);
    stbi_image_free(imageData3);

    hasTransparency=false;
}

void Texture::Bind(unsigned int unit)
{
    assert(unit >= 0 && unit <= 31);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, m_texture+sizeof(m_texture));

    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, m_texture+sizeof(m_texture)+sizeof(m_texture));
}

Texture& Texture::operator=(const Texture& other)
{
    if (this == &other) return *this; // handle self assignment

    m_texture = other.m_texture;
    m_normal_map = other.m_normal_map;
    m_height_map = other.m_height_map;

    return *this;
}
