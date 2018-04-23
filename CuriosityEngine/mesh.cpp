#include "mesh.h"
#include "obj_loader.h"
#include <vector>

#include <sstream>
#include <windows.h>
#include <iostream>

Mesh::Mesh()
{

}

Mesh::Mesh(const std::string& fileName)
{
    IndexedModel model = OBJModel(fileName).ToIndexedModel();
    InitMesh(model);
}

Mesh::Mesh(const Mesh& other)
{
    this->m_drawCount = other.m_drawCount;
    this->m_material = other.m_material;
    this->m_vertexArrayObject = other.m_vertexArrayObject;
    for(int i = 0; i < NUM_BUFFERS; i++)
    this->m_vertexArrayBuffers[i] = other.m_vertexArrayBuffers[i];
}

Mesh::Mesh(Vertex* verticies, unsigned int numVerticies, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel model;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    positions.reserve(numVerticies);
    texCoords.reserve(numVerticies);

    for(unsigned int i = 0; i < numVerticies; i++)
    {
        model.positions.push_back(*verticies[i].GetPos());
        model.texCoords.push_back(*verticies[i].GetTexCoord() );
        model.normals.push_back(*verticies[i].GetNormal() );
        model.tangents.push_back(*verticies[i].GetTangent() );
    }

    for(unsigned int i = 0; i < numIndices; i++)
        model.indices.push_back(indices[i]);

    InitMesh(model);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::LoadMesh(const std::string& fileName)
{
    IndexedModel model = OBJModel(fileName).ToIndexedModel();
    InitMesh(model);
}

void Mesh::InitMesh(const IndexedModel& model)
{
    m_drawCount = model.indices.size();

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);    //wysy³aj kopie zmiennej nie wskaŸnik do niej !!!
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);   //wysy³a informafcje z pamiêci RAM do GPU

    //GL_STATIC_DRAW- zalokuj pamiêc w miejscu ³atwym do odczytrania kosztem szybkoœci zapisu, poniewa¿ nie zamierzam zmieniaæ tych danych

    //texCoords
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

    //normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

    //tangents
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TANGENT_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.tangents.size() * sizeof(model.tangents[0]), &model.tangents[0], GL_STATIC_DRAW);

    //indices
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::Draw()
{


    glBindVertexArray(m_vertexArrayObject);

    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

    glBindVertexArray(0);
}

Mesh& Mesh::operator=(const Mesh& other)
{
    //if (this == &other) return *this; // handle self assignment

    this->m_drawCount = other.m_drawCount;
    this->m_material = other.m_material;
    this->m_vertexArrayObject = other.m_vertexArrayObject;
    for(int i = 0; i < NUM_BUFFERS; i++)
    {
    this->m_vertexArrayBuffers[i] = other.m_vertexArrayBuffers[i];
    }

    return *this;
}

