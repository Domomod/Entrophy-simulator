#include "simpleTexture.h"
#include "stb_image.h"
#include "shader.h"

#include <cassert>
#include <iostream>


extern Shader shader;

SimpleTexture::SimpleTexture()
{

};

SimpleTexture::SimpleTexture(const std::string& fileName1)
{
    int width1, height1, numComponents1;
    unsigned char* imageData1 = stbi_load((fileName1).c_str(), &width1, &height1, &numComponents1, 4);

    if(imageData1 == NULL)
        std::cerr << "Texture loading failed for texture1" << fileName1 << std::endl;

    //first texture - texture
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData1);



    stbi_image_free(imageData1);
}

SimpleTexture::~SimpleTexture()
{
    glDeleteTextures(1, &m_texture);
}

void SimpleTexture::LoadTexture(const std::string& fileName1)
{
    int width1, height1, numComponents1;
    unsigned char* imageData1 = stbi_load((fileName1).c_str(), &width1, &height1, &numComponents1, 4);

    if(imageData1 == NULL)
        std::cerr << "Texture loading failed for texture1" << fileName1 << std::endl;

    //first texture - texture
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData1);

    stbi_image_free(imageData1);
}

void SimpleTexture::Bind(unsigned int unit)
{
    assert(unit >= 0 && unit <= 31);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
