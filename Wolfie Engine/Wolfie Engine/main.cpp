//
//  main.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/11/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "Wolfie.h"
#define BATCH_RENDERER

int main(void)
{
    GLuint shaderProgID;
    Window engineWindow("Wolfie", 600, 800);
    
    if (engineWindow.init() == -1)
    {
        std::cout<<"Engine initialization error"<<std::endl;
        return -1;
    }
    
    //creating shader program
    Shader shObj(FRAGMENT_SHADER_SOURCE, VERTEX_SHADER_SOURCE);
    shaderProgID = shObj.getProgramID();
    
    if(!shObj.checkValidShaderProg())
    {
        std::cout<<"Shader compilation issues"<<std::endl;
        return -1;
    }
    
#ifdef BATCH_RENDERER
    
    Sprite sprite1(glm::vec3(-1.0f, -1.0f, 0.0f),
                   glm::vec2(3.0f, 3.0f),
                   glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
                   );
    Sprite sprite2(glm::vec3(0.0f, 0.0f, 0.0f),
                   glm::vec2(3.0f, 3.0f),
                   glm::vec4(0.1f, 0.8f, 0.8f, 1.0f)
                   );
    
    Sprite sprite3(glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(3.0f, 3.0f),
                   glm::vec4(1.0f, 0.8f, 0.8f, 1.0f)
                   );
    
    
#else
    
    SimpleSprite sprite1(glm::vec3(-1.0f, -1.0f, 0.0f),
                         glm::vec2(3.0f, 3.0f),
                         glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
                         );
    SimpleSprite sprite2(glm::vec3(0.0f, 0.0f, 0.0f),
                         glm::vec2(3.0f, 3.0f),
                         glm::vec4(0.1f, 0.8f, 0.8f, 1.0f)
                         );
    
    SimpleSprite sprite3(glm::vec3(1.0f, 1.0f, 0.0f),
                         glm::vec2(3.0f, 3.0f),
                         glm::vec4(1.0f, 0.8f, 0.8f, 1.0f)
                         );
    
#endif
    
    
    // Transformation Calculations
    //model matrix
    
    glm::mat4 modelMat(1.0f);
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMat = glm::scale(modelMat, glm::vec3(1.5f, 1.5f, 1.0f));
    
    // View matrix
    glm::mat4 viewMat = glm::lookAt(
                                    glm::vec3(0,0,15), // Camera in World Space
                                    glm::vec3(0,0,0), // and looks at the origin
                                    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                    );
    
    //Projection Matrix
    glm::mat4 projMat = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    
    // final MVP transform
    glm::mat4 mvpMat = projMat * viewMat * modelMat;
    
    // enable the shader (glUseProgram)
    shObj.enable();
    shObj.setUniformMatrix4fv("mvp", mvpMat);
    
#ifdef BATCH_RENDERER
    BatchRenderer renderer;
#else
    Simple2DRenderer renderer;
#endif
    
    Timer timer;
    
    while(!engineWindow.isClosed())
    {
        timer.start();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        engineWindow.clear();
        
        
        //body of the draw
#ifdef BATCH_RENDERER
        renderer.begin();
        renderer.submit(&sprite1);
        renderer.submit(&sprite2);
        renderer.submit(&sprite3);
        renderer.end();
#else
        renderer.submit(&sprite1);
        renderer.submit(&sprite2);
        renderer.submit(&sprite3);
#endif
        
        renderer.flush();
        
        engineWindow.update();
        
        if (engineWindow.isKeyPressed(GLFW_KEY_W))
            std::cout<<" W is pressed!!"<<std::endl;
        
        if (engineWindow.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            std::cout<<"Mouse Left clicked!"<<std::endl;
            std::cout<<"Mouse x:"<<engineWindow.getWinMousePosition().first;
            std::cout<<" Mouse y:"<<engineWindow.getWinMousePosition().second<<std::endl;
        }
        
        //glBindVertexArray(0);
        std::cout<<"Timer stopped. duration:"<<timer.stop()<<std::endl;
        timer.reset();
    }
    
    engineWindow.close();
    
    return 0;
}