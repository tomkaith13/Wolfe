//
//  VertexArray.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/25/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "VertexArray.h"



VertexArray::VertexArray()
{
    glGenVertexArrays(1, &mVaoID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mVaoID);
}

void VertexArray::bind()
{
    glBindVertexArray(mVaoID);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(GLuint vapIndex, GLsizei stride, Buffer& vbo)
{
    
    mVertexBuffVec.push_back(&vbo);
    
    bind();
    vbo.bind();
    
    glEnableVertexAttribArray(vapIndex);
    glVertexAttribPointer(vapIndex, vbo.getStrideCount(), GL_FLOAT, GL_FALSE, vbo.getStrideCount() * sizeof(GL_FLOAT), 0);
    //glEnableVertexAttribArray(vapIndex);
    //
    
    vbo.unbind();
    unbind();
    
    glDisableVertexAttribArray(vapIndex);
}

void VertexArray::addVertexDataBuffer(Buffer& VDBO, int vertexIndex, int colorIndex, short vertexDataSize)
{
    bind();
    VDBO.bind();
    
    glEnableVertexAttribArray(vertexIndex);
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(vertexIndex, 4, GL_FLOAT, GL_FALSE, vertexDataSize, (const GLvoid*) 0);
    glVertexAttribPointer(colorIndex, 4, GL_FLOAT, GL_FALSE, vertexDataSize, (const GLvoid*) (4 * sizeof(GLfloat)));
    
    
    VDBO.unbind();
    unbind();
    glDisableVertexAttribArray(vertexIndex);
    glDisableVertexAttribArray(colorIndex);

}



