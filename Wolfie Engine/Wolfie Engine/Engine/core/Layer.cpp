//
//  Layer.cpp
//  Wolfie Engine
//
//  Created by BIBIN THOMAS on 8/25/16.
//  Copyright © 2016 tomkaith13. All rights reserved.
//

#include "Layer.h"

Layer::Layer(Shader* shader,
             Renderer2D* renderer,
             glm::mat4 mvpMat) :
        mLayerShader(shader),
        mLayerRenderer(renderer),
        mLayerMVPMat(mvpMat)
{
    mLayerShader->enable();
    mLayerShader->setUniformMatrix4fv("mvp", mvpMat);
    mLayerShader->disable();
    
}

void Layer::add(Renderable2D* renderable)
{
    mLayerVec.push_back(renderable);
}

void Layer::render()
{
    
    mLayerShader->enable();
    mLayerRenderer->begin();
    
    for(auto sprite : mLayerVec)
        mLayerRenderer->submit(sprite);
    
    mLayerRenderer->flush();
    
    mLayerRenderer->end();
    mLayerShader->disable();
}

Layer::~Layer()
{
    for(auto renderable : mLayerVec)
        delete renderable;
}



