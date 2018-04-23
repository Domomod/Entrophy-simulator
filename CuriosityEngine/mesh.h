#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "obj_loader.h"
#include "material.h"

//do przechywowania w sumie mog³o by byæ struktur¹

class Vertex
{
public:
    Vertex()
    {

    }
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,1,0), const glm::vec3& tangent = glm::vec3(0,0,0))
    {
        this->pos = pos;
        this->texCoord = texCoord;
        this->normal = normal;
        this->tangent = tangent;
    }

    inline void SetPos(glm::vec3 pos) { this->pos = pos; }
    inline glm::vec3* GetPos() { return &pos; }
    inline void SetTexCoord(glm::vec2 texCoord) { this->texCoord = texCoord; }
    inline glm::vec2* GetTexCoord() { return &texCoord; }
    inline void SetNormal(glm::vec3 normal) { this->normal = normal; }
    inline glm::vec3* GetNormal() { return &normal; }
    inline void SetTangent(glm::vec3 tangent ) { this->tangent = tangent; }
    inline glm::vec3* GetTangent() { return &tangent; }

protected:
private:
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;
    glm::vec3 tangent;
};

class Mesh
{
public:
    Mesh();
    Mesh(Vertex* vertices, unsigned int numVerticies, unsigned int* indices, unsigned int numIndices);
    Mesh(const std::string& fileName);


    void LoadMesh(const std::string& fileName);
    void Draw();

    virtual ~Mesh();

    inline GLuint& GetVertexArrayObj() { return m_vertexArrayObject; }
    inline unsigned int& GetDrawCount() { return m_drawCount; }

    Mesh& operator=(const Mesh& other);
    Mesh(const Mesh& other);
protected:
private:

    void InitMesh(const IndexedModel& model);

    enum
    {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,

        TANGENT_VB,
        INDEX_VB,

        NUM_BUFFERS
    };

    const Material *m_material;
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif // MESH_H
