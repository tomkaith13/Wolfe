//
//  ElementBuffer.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/25/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef ElementBuffer_hpp
#define ElementBuffer_hpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ElementBuffer
{
    GLuint mbufferID;
    GLuint mIndexCount;
public:
    ElementBuffer(GLuint count, GLuint* data);
    ~ElementBuffer();
    void bind();
    void unbind();
    inline GLuint getIndexCount() { return mIndexCount;};
    
};
#endif /* ElementBuffer_hpp */
