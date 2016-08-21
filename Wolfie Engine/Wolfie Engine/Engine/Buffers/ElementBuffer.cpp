//
//  ElementBuffer.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/25/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(GLuint count, GLuint* data) : mIndexCount(count)
{
    glGenBuffers(1, &mbufferID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_DYNAMIC_DRAW);
    unbind();
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &mbufferID);
}

void ElementBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbufferID);
}

void ElementBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
