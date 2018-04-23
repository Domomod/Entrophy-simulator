#include "masterrenderer.h"
#include "defines/materials.h"
//
MasterRenderer::MasterRenderer(Shader *shaderPointer, TerrainShader *terrainShaderPointer)
{
    shader = shaderPointer;
    terrainShader = terrainShaderPointer;
}
//
//MasterRenderer::~MasterRenderer()
//{
////dtor
//}
//
void MasterRenderer::Render(std::vector<Entity> entities, std::vector<Terrain> terrains, std::vector<Light> lights, Camera camera)
{
    //Prepare();
    Transform transform;
    shader->Bind();
    shader->LoadLights(lights);
    renderer.render(entities, shader, camera);

	terrainShader->Bind();
	terrainShader->LoadLights(lights);
	terrainShader->Update(transform, camera);
	terrainRenderer.render(terrains, camera, terrainShader);
}
//
////void cleanUp(){
////    shader.cleanUp();
////    terrainShader.cleanUp();
////}
//
void MasterRenderer::Prepare()
{
    glDepthMask(GL_TRUE);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.16f, 0.3f, 1.0f);
}
