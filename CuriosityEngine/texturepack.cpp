#include "texturepack.h"

void TexturePack::Bind()
{
    //*****BACKGROUND******
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, m_backgroundTexture->GetTexture());

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, m_backgroundTexture->GetTexture()+sizeof(m_backgroundTexture->GetTexture()));

    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, m_backgroundTexture->GetTexture()+sizeof(m_backgroundTexture->GetTexture())+sizeof(m_backgroundTexture->GetTexture()));

    //*****R TEXTURE******
    glActiveTexture(GL_TEXTURE0 + 3);
    glBindTexture(GL_TEXTURE_2D, m_rTexture->GetTexture());

    glActiveTexture(GL_TEXTURE0 + 4);
    glBindTexture(GL_TEXTURE_2D, m_rTexture->GetTexture()+sizeof(m_rTexture->GetTexture()));

    glActiveTexture(GL_TEXTURE0 + 5);
    glBindTexture(GL_TEXTURE_2D, m_rTexture->GetTexture()+sizeof(m_rTexture->GetTexture())+sizeof(m_rTexture->GetTexture()));

    //*****G TEXTURE******
    glActiveTexture(GL_TEXTURE0 + 6);
    glBindTexture(GL_TEXTURE_2D, m_gTexture->GetTexture());

    glActiveTexture(GL_TEXTURE0 + 7);
    glBindTexture(GL_TEXTURE_2D, m_gTexture->GetTexture()+sizeof(m_gTexture->GetTexture()));

    glActiveTexture(GL_TEXTURE0 + 8);
    glBindTexture(GL_TEXTURE_2D, m_gTexture->GetTexture()+sizeof(m_gTexture->GetTexture())+sizeof(m_gTexture->GetTexture()));

    //*****B TEXTURE******
    glActiveTexture(GL_TEXTURE0 + 9);
    glBindTexture(GL_TEXTURE_2D, m_bTexture->GetTexture());

    glActiveTexture(GL_TEXTURE0 + 10);
    glBindTexture(GL_TEXTURE_2D, m_bTexture->GetTexture()+sizeof(m_bTexture->GetTexture()));

    glActiveTexture(GL_TEXTURE0 + 11);
    glBindTexture(GL_TEXTURE_2D, m_bTexture->GetTexture()+sizeof(m_bTexture->GetTexture())+sizeof(m_bTexture->GetTexture()));

    //*****BLEND MAP******
    glActiveTexture(GL_TEXTURE0 + 12);
    glBindTexture(GL_TEXTURE_2D, m_blendMap->GetTexture());
}
