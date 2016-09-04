//
//  Renderable2D.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/27/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef SIMPLESPRITE_H
#define SIMPLESPRITE_H

#include <glm/glm.hpp>
#include "VertexArray.h"
#include "Buffer.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Renderable2D.h"

/*
 This is the basic sprite renderable which is a rectangle,
 placed at 'position' vector of 'size' size having 'color'
 color.
 
 The renderable has its own VAO, VBO, and EBO.
 This is not an efficient drawing method but exists only as a teaching method.
 
 The reason for the inefficiency is because the each sprite only pushes
 its own vertex data to the GPU rather than the renderer batching up
 a whole group of sprite. 
 
 This is where the BatchRenderer comes in.
 */

class SimpleSprite : public Renderable2D
{
    VertexArray* mVao;
    Buffer* mVbo;
    Buffer*  mCbo;
    ElementBuffer* mEbo;  
    
public:
    SimpleSprite(glm::vec3 position, glm::vec2 size, glm::vec4 color);
    ~SimpleSprite();
    inline VertexArray* getVAO() { return mVao;}
    inline Buffer* getVBO() { return mVbo;}
    inline ElementBuffer* getEBO() { return mEbo;}
    inline const glm::vec3& getPosition() { return Renderable2D::getPosition();}
    inline const glm::vec2& getSize() { return Renderable2D::getSize();}
    inline const glm::vec4& getColor() { return Renderable2D::getColor();}
    
};
#endif /* SIMPLESPRITE_H */
