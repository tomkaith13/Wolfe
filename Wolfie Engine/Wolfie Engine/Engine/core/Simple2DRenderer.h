//
//  Simple2DRenderer.h
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/27/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef Simple2DRenderer_h
#define Simple2DRenderer_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <deque>
#include "Renderer2D.h"
#include "SimpleSprite.h"

class Simple2DRenderer : public Renderer2D
{
    std::deque<SimpleSprite*> mRenderQueue;
public:
    void submit(Renderable2D*) override;
    void  flush() override;
    
};



#endif /* Simple2DRenderer_h */
