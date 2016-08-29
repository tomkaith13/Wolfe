//
//  TileLayer.h
//  Wolfie Engine
//
//  Created by BIBIN THOMAS on 8/28/16.
//  Copyright © 2016 tomkaith13. All rights reserved.
//

#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include "Shader.h"
#include "Renderable2D.h"
#include "Renderer2D.h"
#include <GLM/glm.hpp>



/*
 * 2D Layer which has its own vector of renderables and 2D renderer
 */
class TileLayer : public Layer
{
public:
    TileLayer(Shader*, Renderer2D*, glm::mat4);
};

#endif /* TILELAYER_H */
