//
//  Buffer.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/25/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum BufferOpMode {
    SINGLE_VERTEX_ATTRIB_BUFFER = 0,
    BATCHED_VERTEX_ATTRIB_BUFFER
};

class Buffer
{
    GLuint mBufferID;
    GLint mBuffStrideCount;
    GLint mBuffElementCount;
    GLenum mBufferDrawStyle;
    
public:
    /*
     This Buffer has two operation modes:
     1) SINGLE_VERTEX_ATTRIB_BUFFER
     */
    Buffer(GLuint count, GLuint strideCount, GLfloat* data, GLenum bufferDrawStyle = GL_STATIC_DRAW, int mode = SINGLE_VERTEX_ATTRIB_BUFFER);

    ~Buffer();
    void bind();
    void unbind();
    GLint getElementCount();
    GLint getStrideCount();
};



#endif /* Buffer_hpp */
