//
//  Renderer2D.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/27/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef Renderer2D_hpp
#define Renderer2D_hpp

//#include "Renderable2D.h"
#include <vector>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

class Renderable2D;

// This abstract class is used in Renderer2D.cpp
class Renderer2D
{
public:
    std::vector<glm::mat4> mTransformMatVec;
    glm::mat4 mCurrTransformMat;
    
    virtual void push(float* tMatPtr, bool overwrite = false)
    {
        if (!overwrite)
        {
            mTransformMatVec.push_back(mTransformMatVec.back() * glm::make_mat4(tMatPtr));
        } else {
            mTransformMatVec.push_back(glm::make_mat4(tMatPtr));
        }
        
        mCurrTransformMat = mTransformMatVec.back();
    }
    
    virtual void pop()
    {
        if (mTransformMatVec.size() > 1)
            mTransformMatVec.pop_back();
        
        mCurrTransformMat = mTransformMatVec.back();
    }

    virtual void begin() {}
    virtual void submit(Renderable2D*) = 0;
    virtual void end() {}
    virtual void flush() = 0;
    
};
#endif /* Renderer2D_hpp */
