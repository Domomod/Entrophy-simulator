#include "terrainrenderer.h"

#include "texturedmodel.h"

void TerrainRenderer::render(std::vector<Terrain> terrains, const Camera &camera, TerrainShader* shader)
{
    for(int i=0; i < terrains.size(); i++)
    {
        PrepareTerrain(terrains[i], shader);
        glDrawElements(GL_TRIANGLES, terrains[i].GetModel()->GetDrawCount(), GL_UNSIGNED_INT, 0);
        UnbindTexturedModel();
    }
}

void TerrainRenderer::PrepareTerrain(Terrain terrain, TerrainShader *shader)
{
//    TexturedModel model(terrain.GetModel(), terrain.GetTexture(), terrain.GetMaterial());

    glBindVertexArray(terrain.GetModel()->GetVertexArrayObj());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    terrain.GetTexture()->Bind();
	shader->UpdateMaterial(terrain.GetMaterial());
}

void TerrainRenderer::UnbindTexturedModel()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);
}
