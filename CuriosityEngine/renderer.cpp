#include "renderer.h"

#include <iostream>

void EntityRenderer::render(std::vector<Entity> entities, Shader *shader, const Camera &camera)
{
    for(int i=0; i < entities.size(); i++)
    {
        PrepareEntity(entities[i], shader, camera);
        glDrawElements(GL_TRIANGLES, entities[i].GetModel().GetRawModel()->GetDrawCount(), GL_UNSIGNED_INT, 0);
        UnbindTexturedModel();
    }
}

void EntityRenderer::PrepareEntity(Entity entity, Shader *shader, Camera camera)
{
    TexturedModel model = entity.GetModel();
    Transform transform;
        transform.GetPos() =  entity.GetPos();
        transform.GetRot().x = entity.GetRotX();
        transform.GetRot().y = entity.GetRotY();
        transform.GetRot().z = entity.GetRotZ();
        transform.SetScale(glm::vec3(entity.GetScale().x,entity.GetScale().y ,entity.GetScale().z));
    shader->Update(transform, camera);

    if(entity.GetModel().GetTexture()->getTransparency()==true) glDisable(GL_CULL_FACE);


    glBindVertexArray(model.GetRawModel()->GetVertexArrayObj());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    entity.GetModel().GetTexture()->Bind(0);
	shader->UpdateMaterial(entity.GetModel().GetMaterial());
}

void EntityRenderer::UnbindTexturedModel()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);
}
