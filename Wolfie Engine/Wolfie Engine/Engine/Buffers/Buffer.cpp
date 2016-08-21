//
//  Buffer.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/25/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "Buffer.h"

Buffer::Buffer(GLuint count, GLuint strideCount, GLfloat* data, GLenum drawStyle, int mode) :
mBuffElementCount(count), mBuffStrideCount(strideCount), mBufferDrawStyle(drawStyle)
{
    if (mode == SINGLE_VERTEX_ATTRIB_BUFFER) {
        glGenBuffers(1,&mBufferID);
        bind();
        glBufferData(GL_ARRAY_BUFFER, count , data, mBufferDrawStyle);
        unbind();
    } else if (mode == BATCHED_VERTEX_ATTRIB_BUFFER) {
        mBuffStrideCount = 0; // this has no meaning
        glGenBuffers(1,&mBufferID);
        bind();
        glBufferData(GL_ARRAY_BUFFER, count , data, mBufferDrawStyle);
        unbind();
    }

}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &mBufferID);
}

void Buffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
}

void Buffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLint Buffer::getElementCount()
{
    return mBuffElementCount;
}

GLint Buffer::getStrideCount()
{
    return mBuffStrideCount;
}