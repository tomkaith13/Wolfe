//
//  BatchRenderer.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 8/11/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "BatchRenderer.h"


BatchRenderer::BatchRenderer()
{
    init();
}

void BatchRenderer::init()
{
    GLuint indices[MAX_RENERABLE_INDICES];
    GLuint offset = 0;
    mVAO = new VertexArray();
    mIndexCount = 0;
    
    
    mVDBO = new Buffer(MAX_RENDERED_BUFF_SIZE, 0 , NULL, GL_DYNAMIC_DRAW, BATCHED_VERTEX_ATTRIB_BUFFER);
    
    mVAO->addVertexDataBuffer(*mVDBO, VERTEX_ATTRIB_LOCATION, COLOR_ATTRIB_LOCATION, VERTEX_DATA_SIZE);
    
    /*
     
     Index pattern looks like this:
     
     1   3 | 5   7 | 9  11
           |       |        ...
     0   2 | 4   6 | 8  10
     
     hence total number of indices in each vertex data is 6 (i.e. two triangles)
     Total vertices is 0 (hence the offset)
     
     */
    
    //fill out the indices buffer data
    for (unsigned int i = 0; i < MAX_RENERABLE_INDICES; i+=6)
    {
        indices[  i  ] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        
        indices[i + 3] = offset + 1;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 2;
        
        offset += 4;
    }
    
    mEBO = new ElementBuffer(MAX_RENERABLE_INDICES, indices);    
}

void BatchRenderer::begin()
{
    mVDBO->bind();
    mVdata = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BatchRenderer::submit(Renderable2D* renderable) {
    Sprite* renderedSprite = (Sprite*)renderable;
    glm::vec2 spriteSize = renderedSprite->getSize();
    glm::vec3 spritePos = renderedSprite->getPosition();
    glm::vec4 spriteColor = renderedSprite->getColor();
    
    
    
    /*
     
     And now for some artwork!! :)
     
     
   B -------- D <-- position + size
     |      |
     |      |
     |      |
   A -------- C
     ^
     |
     |
     
     position
     */
    
    
    // Point A
    mVdata->position = glm::vec4(spritePos, 1.0);
    mVdata->color = spriteColor;
    mVdata++;
    
    //Point B
    mVdata->position = glm::vec4(glm::vec3(spritePos.x, spritePos.y + spriteSize.y, spritePos.z), 1.0);
    mVdata->color = spriteColor;
    mVdata++;
    
    //Point C
    mVdata->position = glm::vec4(glm::vec3(spritePos.x + spriteSize.x, spritePos.y, spritePos.z), 1.0);
    mVdata->color = spriteColor;
    mVdata++;
    
    //Point D
    mVdata->position = glm::vec4(glm::vec3(spritePos.x + spriteSize.x, spritePos.y + spriteSize.y, spritePos.z), 1.0);
    mVdata->color = spriteColor;
    mVdata++;
    
    mIndexCount += 6;
    
   
}

void BatchRenderer::flush()
{
    
    mVAO->bind();
    mEBO->bind();
    
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
    
    mEBO->unbind();
    mVAO->unbind();
    mIndexCount = 0;
    
    
}

void BatchRenderer::end()
{
    glUnmapBuffer(GL_ARRAY_BUFFER);
    mVDBO->unbind();

}