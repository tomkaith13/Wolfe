//
//  Texture2D.hpp
//  Wolfie Engine
//
//  Created by BIBIN THOMAS on 9/3/16.
//  Copyright © 2016 tomkaith13. All rights reserved.
//

#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Texture2D
{
    GLuint mTextureID;
    const char* mFilename;
    int mTextureWidth, mTextureHeight, mTextureCompNum;
    unsigned char* mTextureData;
    
public:
    
    Texture2D(const char* filename);
    void generate();
    void bind();
    void setParamater();
    ~Texture2D();
    
};


#endif /* TEXTURE_2D_H */
