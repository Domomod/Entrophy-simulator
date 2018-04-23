
#ifndef SIMPLETEXTURE_H
#define SIMPLETEXTURE_H

#include <string>
#include <iostream>
#include <GL/glew.h>

class SimpleTexture
{
public:
    SimpleTexture();
    SimpleTexture(const std::string& fileName1);

    void LoadTexture(const std::string& fileName1);
    void Bind(unsigned int unit);

    GLuint GetTexture() { return m_texture; }

    ~SimpleTexture();
protected:
private:
    GLuint m_texture;
};

#endif // SIMPLETEXTURE_H
