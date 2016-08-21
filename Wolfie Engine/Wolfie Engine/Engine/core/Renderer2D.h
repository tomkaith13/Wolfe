//
//  Renderer2D.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/27/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef Renderer2D_hpp
#define Renderer2D_hpp

#include "Renderable2D.h"


// This abstract class is used in Renderer2D.cpp
class Renderer2D
{
protected:
    virtual void submit(Renderable2D*) = 0;
    virtual void flush() = 0;
};
#endif /* Renderer2D_hpp */
