//
//  Group.h
//  Wolfie Engine
//
//  Created by BIBIN THOMAS on 8/29/16.
//  Copyright © 2016 tomkaith13. All rights reserved.
//

#ifndef GROUP_H
#define GROUP_H

#include "Renderable2D.h"
#include <vector>

class Group : public Renderable2D
{
    std::vector<Renderable2D*> mGroupRenderableVec;
    glm::mat4 mGroupTransformMat;
public:
    Group(glm::mat4);
    void submit(Renderer2D*) override;
    void add(Renderable2D*);
    
};


#endif /* GROUP_H */
