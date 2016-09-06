//
//  BatchRenderer.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 8/11/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "BatchRenderer.h"

/*
 * Constructor which calls nothing, internally invokes init()
 */
BatchRenderer::BatchRenderer()
{
    init();
}


/*
 * init() is the one who creates the Vertex Array Object, pushes the initial identitiy Matrix to the vao.
 * Then, we create VDBO (Vertex Data Buffer Object) and pass the Vertex Attribute to 
 * VAO specifying how to use the attribute in VDBO. We also fill out the Element Buffer to 
 * specify the indices of the
 */
void BatchRenderer::init()
{
    GLuint indices[MAX_RENERABLE_INDICES];
    GLuint offset = 0;
    mVAO = new VertexArray();
    mIndexCount = 0;
    
    // Top level identity matrix set
    mTransformMatVec.push_back(glm::mat4(1.0f));
    
    // Currently we support a MAX_RENDERABLE_SPRITES sprite buffer of Batched Renderering
    mVDBO = new Buffer(MAX_RENDERED_BUFF_SIZE, 0 , NULL, GL_DYNAMIC_DRAW, BATCHED_VERTEX_ATTRIB_BUFFER);
    
    mVAO->addSingleAttribFromBuffer(*mVDBO,
                                    VERTEX_ATTRIB_LOCATION,
                                    4,
                                    VERTEX_DATA_SIZE,
                                    offsetof(struct VertexData, position));
    mVAO->addSingleAttribFromBuffer(*mVDBO,
                                    COLOR_ATTRIB_LOCATION,
                                    4,
                                    VERTEX_DATA_SIZE,
                                    offsetof(struct VertexData, color));
    mVAO->addSingleAttribFromBuffer(*mVDBO,
                                    TEXTURE_ATTRIB_LOCATION,
                                    2,
                                    VERTEX_DATA_SIZE,
                                    offsetof(struct VertexData, uv));
        
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
    
    //allocate the appropriate Element Buffer
    mEBO = new ElementBuffer(MAX_RENERABLE_INDICES, indices);    
}


/*
 * begin() is where we the the GPU buffer to a local pointer
 */
void BatchRenderer::begin()
{
    mVDBO->bind();
    mVdata = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}


/*
 * submit() is the function where we submit the renderable object to the renderer.
 * This is where we fill in the pointer that is mmaped to the GPU.
 */
void BatchRenderer::submit(Renderable2D* renderable) {
    
    Sprite* renderedSprite = static_cast<Sprite*>(renderable);
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
    
    // Matrix mult is expensive in the game main loop
    // Another optimization for mCurrTransformMat calculation:
    // If this is the identity matrix, then just avoid the mutiplication itself.
    bool identityOptmize = true;
    
    identityOptmize = (mCurrTransformMat == glm::mat4(1.0f))? true : false;
    
    // Point A
    if (identityOptmize)
        mVdata->position = glm::vec4(spritePos, 1.0);
    else
        mVdata->position =   mCurrTransformMat * glm::vec4(spritePos, 1.0);
    mVdata->color = spriteColor;
    mVdata->uv = glm::vec2(0.0, 0.0);
    mVdata++;
    
    //Point B
    if (identityOptmize)
        mVdata->position = glm::vec4(glm::vec3(spritePos.x, spritePos.y + spriteSize.y, spritePos.z), 1.0);
    else
        mVdata->position = mCurrTransformMat * glm::vec4(glm::vec3(spritePos.x, spritePos.y + spriteSize.y, spritePos.z), 1.0);
    mVdata->color = spriteColor;
    mVdata->uv = glm::vec2(0.0, 1.0);
    mVdata++;
    
    //Point C
    if (identityOptmize)
        mVdata->position = glm::vec4(glm::vec3(spritePos.x + spriteSize.x, spritePos.y, spritePos.z), 1.0);
    else
        mVdata->position = mCurrTransformMat * glm::vec4(glm::vec3(spritePos.x + spriteSize.x, spritePos.y, spritePos.z), 1.0);
    mVdata->color = spriteColor;
    mVdata->uv = glm::vec2(1.0, 0.0);
    mVdata++;
    
    //Point D
    if (identityOptmize)
        mVdata->position = glm::vec4(glm::vec3(spritePos.x + spriteSize.x, spritePos.y + spriteSize.y, spritePos.z), 1.0);
    else
        mVdata->position = mCurrTransformMat * glm::vec4(glm::vec3(spritePos.x + spriteSize.x, spritePos.y + spriteSize.y, spritePos.z), 1.0);
    mVdata->color = spriteColor;
    mVdata->uv = glm::vec2(1.0, 1.0);
    mVdata++;
    
    mIndexCount += 6;
}

/*
 * The actual draw call happens in flush()
 */
void BatchRenderer::flush()
{
    
    mVAO->bind();
    mEBO->bind();
    
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
    
    mEBO->unbind();
    mVAO->unbind();
    mIndexCount = 0;
    
    
}

/*
 * end() is used to unmap the GPU buffer
 */
void BatchRenderer::end()
{
    glUnmapBuffer(GL_ARRAY_BUFFER);
    mVDBO->unbind();

}

/*
 * free up Vertex Array Obj, Vertex Data Buffer Obj and Element Buffer Obj
 */
BatchRenderer::~BatchRenderer()
{
    delete mVAO;
    delete mVDBO;
    delete mEBO;
}