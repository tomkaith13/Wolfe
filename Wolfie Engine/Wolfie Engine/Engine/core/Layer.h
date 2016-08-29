//
//  Layer.hpp
//  Wolfie Engine
//
//  Created by BIBIN THOMAS on 8/25/16.
//  Copyright © 2016 tomkaith13. All rights reserved.
//

#ifndef LAYER_H
#define LAYER_H

#include "Shader.h"
#include "Renderer2D.h"
#include "Renderable2D.h"
#include <GLM/glm.hpp>
#include <vector>


/*
 * This is the logical class for holding multiple rendererables, the shader 
 * and the respective projection matrix. This is the class which does the mvp
 * calculation on the CPU.
 */

class Layer
{
    Shader* mLayerShader;
    Renderer2D* mLayerRenderer;
    glm::mat4 mLayerMVPMat;
    std::vector<Renderable2D*> mLayerVec;
    
protected:
    Layer( Shader*, Renderer2D*, glm::mat4);
    ~Layer();
public:
    
    void add(Renderable2D*);
    void render();
    
    
};
#endif /* LAYER_H */
