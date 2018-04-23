
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
    Texture();
    Texture(const std::string& fileName1, const std::string& fileName2="./res/textures/default_normal.jpg", const std::string& fileName3="./res/textures/default_disp.png");
    void Add_Normal_Map();
    void Bind(unsigned int unit);
    void LoadTexture(const std::string& fileName1, const std::string& fileName2="./res/textures/default_normal.jpg", const std::string& fileName3="./res/textures/default_disp.png");

    void setTransparency(bool value){ hasTransparency = value; }
    bool getTransparency() { return hasTransparency; }

    GLuint GetTexture() { return m_texture; }

    Texture& operator=(const Texture& other);

    virtual ~Texture();
protected:
private:
    bool hasTransparency;

    GLuint m_texture;
    GLuint m_normal_map;
    GLuint m_height_map;
};

#endif // TEXTURE_H
