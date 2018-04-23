#include "terrain.h"

#include "iostream"

#include <cmath>

#include "texture.h"
#include "stb_image.h"
#include "shader.h"
#include "vec3math.h"
#include <cassert>

void Terrain::generateTerrain()
{

    std::string fileName1 = "./res/textures/heightmap.jpg";

    int width1, height1, numComponents1;
    unsigned char* imageData1 = stbi_load((fileName1).c_str(), &width1, &height1, &numComponents1, 4);

    const int count = VERTEX_COUNT * VERTEX_COUNT;
    Vertex vertices[count];
    glm::vec3 *positions = new glm::vec3[count];
    glm::vec3 *normals = new glm::vec3[count];
    glm::vec2 *textureCoords = new glm::vec2[count];
    unsigned int* indices = new unsigned int[6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1)];
    int vertexPointer = 0;
    for(int j=0;j<VERTEX_COUNT;j++){
        for(int i=0;i<VERTEX_COUNT;i++){


            //calculate the coordinates on height map
            int x = (i/(float)VERTEX_COUNT)* width1;
            int y = (j/(float)VERTEX_COUNT)* height1;

            //calculate the height
            int data = imageData1[(x + y * width1)*4]; //potraktuj obraz jako ciag danych rgba rgba rgba
            float height = (data/255.0f) - 0.5f;
            heights[j][i] = 100 * height;

            //calculate normal
            float heightL = i> 0 ? imageData1[((x-1) + y * width1)*4] : 0.0f;
            float heightR = i< VERTEX_COUNT-1 ? imageData1[((x+1) + y * width1)*4] : 0.0f;
            float heightD = j> 0 ? imageData1[(x + (y-1) * width1)*4] : 0.0f;
            float heightU = j< VERTEX_COUNT-1 ? imageData1[(x + (y+1) * width1)*4] : 0.0f;
            glm::vec3 newNormal = glm::vec3(heightD - heightU,2.0f,heightL - heightR);
            Vec3Math::normalize(&newNormal);

            positions[vertexPointer].x = (float)i/((float)VERTEX_COUNT - 1) * TERRAIN_SIZE;
            positions[vertexPointer].y = heights[j][i];
            positions[vertexPointer].z = (float)j/((float)VERTEX_COUNT - 1) * TERRAIN_SIZE;
            normals[vertexPointer].x = newNormal.x;
            normals[vertexPointer].y = newNormal.y;
            normals[vertexPointer].z = newNormal.z;
            textureCoords[vertexPointer].x = (float)i/((float)VERTEX_COUNT - 1);
            textureCoords[vertexPointer].y = (float)j/((float)VERTEX_COUNT - 1);
            vertexPointer++;
        }
    }

    int pointer = 0;
    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    for(int i=0; i < count; i++)
    {
        vertices[i].SetPos(positions[i]);
        vertices[i].SetNormal(normals[i]);
        vertices[i].SetTexCoord(textureCoords[i]);
    }

    m_model= new Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, 6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));
}

float Terrain::GetHeight(float x, float z)
{
    float gridSquareSize = TERRAIN_SIZE / (float) (VERTEX_COUNT-1);
	int gridX = x / gridSquareSize; //gridX--;
	int gridZ = z / gridSquareSize; //gridZ--;
    //gridZ = VERTEX_COUNT - gridZ;
    //gridX = VERTEX_COUNT - gridX;

	if (gridX >= VERTEX_COUNT - 1 || gridX < 0 ||
		gridZ >= VERTEX_COUNT - 1 || gridZ < 0)
		return 0;

    float xCoord = fmod(x, gridSquareSize)/gridSquareSize;
    float zCoord = fmod(z, gridSquareSize)/gridSquareSize;
    float answer = 0;

    if( xCoord < zCoord)
    {
    answer = Vec3Math::barryCentric(
                                    glm::vec3(0.0f, heights[gridZ][gridX], 0.0f),
                                    glm::vec3(1.0f, heights[gridZ+1][gridX], 0.0f),
                                    glm::vec3(1.0f, heights[gridZ + 1][gridX + 1], 1.0f),
                                    glm::vec2(zCoord, xCoord) );
    }
    else
    {
    answer = Vec3Math::barryCentric(
                                    glm::vec3(0, heights[gridZ][gridX], 0),
                                    glm::vec3(0, heights[gridZ][gridX+1], 1),
                                    glm::vec3(1, heights[gridZ + 1][gridX + 1], 1),
                                    glm::vec2(zCoord, xCoord) );
    }
    return answer;
	//return heights[gridZ][gridX+1];
}

Terrain::~Terrain()
{
    //dtor
}
