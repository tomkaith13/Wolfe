//
//  BatchRenderer.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 8/11/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef BATCHRENDERER_H
#define BATCHRENDERER_H

#include <vector>
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "ElementBuffer.h"
#include "Sprite.h"
#include "Texture2D.h"

//Batch Renderer known limits
#define MAX_RENDERABLE_SPRITES 65000
#define VERTEX_DATA_SIZE sizeof(VertexData) // 4 position floats  + 4 color floats defined in Renderable2D.h
#define MAX_RENDERED_BUFF_SIZE MAX_RENDERABLE_SPRITES * VERTEX_DATA_SIZE * 4
#define MAX_RENERABLE_INDICES 6 * MAX_RENDERABLE_SPRITES

//Texture Vector limits
#define MAX_TEXTURE_VEC 32

#define VERTEX_ATTRIB_LOCATION 0
#define COLOR_ATTRIB_LOCATION  1
#define TEXTURE_ATTRIB_LOCATION 2
#define TEXTURE_ID_ATTRIB_LOCATION 3


/* 
 This is class which defined the Batch Renderer.
 Unlike, the SimpleRenderer, this renderer initialize
 a huge predefined buffer with known limits and then submits the 
 Rendererable's Vertex Data to it
 
 */

class BatchRenderer : public Renderer2D
{
    VertexArray* mVAO;
    Buffer* mVDBO; // complete vertex data - vertices colors and textures.
    ElementBuffer* mEBO;
    
    VertexData* mVdata;
    unsigned int mIndexCount;
    
    // Vector for textures
    std::vector<const Texture2D*> mTextureVec;
    
    void init();
    
public:
    
    BatchRenderer();
    ~BatchRenderer();
    void begin() override;
    void end() override;
    void submit(Renderable2D*) override;
    void flush() override;    
};

#endif /* BATCHRENDERER_H */
