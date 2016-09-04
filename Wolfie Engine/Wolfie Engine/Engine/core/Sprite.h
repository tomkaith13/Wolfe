//
//  Sprite.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 8/11/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef SPRITE_H
#define SPRITE_H

#include "Renderable2D.h"

class Sprite : public Renderable2D
{
public:
    
    Sprite(glm::vec3 pos, glm::vec2 size, glm::vec4 color) :
        Renderable2D(pos, size, color) { };
    //inline const glm::vec3& getPosition() { return Renderable2D::getPosition(); }
    //inline const glm::vec2& getSize() { return Renderable2D::getSize(); }
    //inline const glm::vec4& getColor() { return Renderable2D::getColor(); }
};
#endif /* SPRITE_H */
