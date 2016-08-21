//
//  SimpleSprite.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/27/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "SimpleSprite.h"

SimpleSprite::SimpleSprite(glm::vec3 position, glm::vec2 size, glm::vec4 color):
    Renderable2D(position, size, color)
{
    mVao = new VertexArray();
    
    //counting new vertice starting from origin in the clockwise direction
    GLfloat vertices[] = {
            position.x,          position.y,          position.z, 1.0,
            position.x,          position.y + size.y, position.z, 1.0,
            position.x + size.x, position.y,          position.z, 1.0,
            position.x + size.x, position.y + size.y, position.z, 1.0
        
        
    };
    mVbo = new Buffer(4 * 4 * sizeof(GLfloat), 4 , vertices);
    mVao->addVertexBuffer(0, 4, *mVbo);
    
    GLfloat colors[] = {
        color.x, color.y, color.z, 1.0,
        color.x, color.y, color.z, 1.0,
        color.x/3, color.y/3, color.z/3, 1.0,
        color.x/2, color.y/2, color.z/2, 1.0/2,
    };
    
    mCbo = new Buffer(4 * 4 * sizeof(GLfloat), 4 , colors);
    mVao->addVertexBuffer(1, 4, *mCbo);
    
    GLuint indices[] = {
            0, 1, 2,
            1, 3, 2
    };
    
    mEbo = new ElementBuffer(6, indices);
}

SimpleSprite::~SimpleSprite()
{
    
    delete mVao;
    delete mVbo;
    delete mCbo;
    delete mEbo;
}