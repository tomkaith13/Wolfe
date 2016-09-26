//
//  Renderable2D.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 8/11/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef Renderable2D_hpp
#define Renderable2D_hpp

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Renderer2D.h"
#include "Texture2D.h"

//class Renderer2D;

/* 
 This is an abstract class for all renderables
 */

struct VertexData
{
    glm::vec4 position;
    glm::vec4 color;
    glm::vec2 uv;
    float tid;

};

class Renderable2D{
protected:
    
    glm::vec3 mPosition;
    glm::vec2 mSize;
    glm::vec4 mColor;
    std::vector<glm::vec2> mVecUV;
    GLuint mIndices[6];
    Texture2D* mTextureObj;


public:
    Renderable2D() {}
    Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color, Texture2D* tObj = nullptr) :
    mPosition(position), mSize(size) , mColor(color), mTextureObj(tObj) {
        mIndices[0] = 0;
        mIndices[1] = 1;
        mIndices[2] = 2;
        
        mIndices[3] = 1;
        mIndices[4] = 3;
        mIndices[5] = 2;
        
        mVecUV.push_back(glm::vec2(0,0));
        mVecUV.push_back(glm::vec2(0,1));
        mVecUV.push_back(glm::vec2(1,0));
        mVecUV.push_back(glm::vec2(1,1));
    };
        
    inline const GLuint getTid()
    {
        if (mTextureObj)
            return mTextureObj->getTid();
        else
            return 0;
    }
    inline Texture2D* getTextureObj() { return mTextureObj; }
    inline const glm::vec3& getPosition() { return mPosition;}
    inline const glm::vec2& getSize() { return mSize;}
    inline const glm::vec4& getColor() { return mColor;}
    inline GLuint* getIndices() { return mIndices; }
    inline const std::vector<glm::vec2>& getUV() { return mVecUV; }
    
    virtual void submit(Renderer2D* renderer)
    {
        renderer->submit(this);
    }
    
};
#endif /* Renderable2D_hpp */
