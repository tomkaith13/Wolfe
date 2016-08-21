//
//  Renderer2D.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/27/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "Simple2DRenderer.h"


void Simple2DRenderer::submit(Renderable2D* sprite)
{
    mRenderQueue.push_back((SimpleSprite*)sprite);
}

void Simple2DRenderer::flush()
{
    SimpleSprite* sprite;    
    
    while(!mRenderQueue.empty())
    {
        sprite = mRenderQueue.front();
        sprite->getVAO()->bind();
        sprite->getEBO()->bind();
        
        glDrawElements(GL_TRIANGLES, sprite->getEBO()->getIndexCount(), GL_UNSIGNED_INT, 0);
        
        sprite->getEBO()->unbind();
        sprite->getVAO()->unbind();
        mRenderQueue.pop_front();
    }
}