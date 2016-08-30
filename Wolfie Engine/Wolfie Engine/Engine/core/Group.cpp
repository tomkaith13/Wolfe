//
//  Group.cpp
//  Wolfie Engine
//
//  Created by BIBIN THOMAS on 8/29/16.
//  Copyright © 2016 tomkaith13. All rights reserved.
//

#include "Group.h"

Group::Group(glm::mat4 tMat):
    mGroupTransformMat(tMat)
{
    
}

void Group::submit(Renderer2D* renderer)
{
    renderer->push(mGroupTransformMat);
    for (auto sprite : mGroupRenderableVec)
        sprite->submit(renderer);
    renderer->pop();
    
}

void Group::add(Renderable2D* renderable)
{
    mGroupRenderableVec.push_back(renderable);
}

