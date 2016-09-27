//
//  Texture2D.cpp
//  Wolfie Engine
//
//  Created by BIBIN THOMAS on 9/3/16.
//  Copyright © 2016 tomkaith13. All rights reserved.
//

#include "Texture2D.h"

// This needs to be done in a C/C++ file according to the readme specified in  stb_image.h
// hence, not included in texture2d.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(const char* filename)
: mFilename(filename)
{
    mTextureData = stbi_load(filename, &mTextureWidth, &mTextureHeight, &mTextureCompNum, 0);
    if (mTextureData == nullptr)
    {
        std::cout<<"stbi_load failed!!"<<std::endl;
        return;
    }
   
    glGenTextures(1, &mTextureID);
}

// This texture2D function binds the texture as the currently bound texture
// and also generates mipmaps.
void Texture2D::generate()
{
    //glActiveTexture(GL_TEXTURE0);
    bind();
    if (mTextureCompNum == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mTextureWidth, mTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mTextureData);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mTextureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    
}


void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture2D::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
    stbi_image_free(mTextureData);
    
}
