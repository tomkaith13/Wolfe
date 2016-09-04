//
//  VertexArray.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/25/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Buffer.h"
#include "ElementBuffer.h"


class VertexArray
{
    GLuint mVaoID;
    std::vector<Buffer*> mVertexBuffVec;
public:
    VertexArray();
    ~VertexArray();
    void bind();
    void unbind();
    
    void addVertexBuffer(GLuint vapIndex, GLsizei stride, Buffer& vbo);
    void addVertexDataBuffer(Buffer& VDBO, int vertexIndex, int colorIndex, short vertexDataSize);
    void addSingleAttribFromBuffer(Buffer& VDBO, int index, int indexSize, short vertexDataSize, std::size_t startLocation);
};



#endif /* VertexArray_hpp */
