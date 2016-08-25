//
//  main.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/11/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "Wolfie.h"
#include <vector>
#include <chrono>
#include <random>
#define BATCH_RENDERER
//#define FPS_VIEWER

int main(void)
{
    GLuint shaderProgID;
    Window engineWindow("Wolfie", 1000, 1200);
    std::vector<Sprite> spriteVec;
    
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
    
    std::chrono::system_clock::time_point sysTimePoint = std::chrono::system_clock::now();
    double seed = sysTimePoint.time_since_epoch().count();
    std::mt19937 gen(seed);
    
    std::uniform_real_distribution<double> dist;
    
    for(int i = 0; i < 254;i += 1.0) {
        for(int j = 0; j < 254; j += 1.0) {
            Sprite tmpSprite(glm::vec3(i, j ,0.0f),
                             glm::vec2(1.0f, 1.0f),
                             glm::vec4(dist(gen),dist(gen), dist(gen), 1.0f));
            spriteVec.push_back(tmpSprite);
            
        }
    }
    
    
    
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
    modelMat = glm::scale(modelMat, glm::vec3(1.0f, 1.0f, 1.0f));
    
    // View matrix
    glm::mat4 viewMat = glm::lookAt(
                                    glm::vec3(125,125,90), // Camera in World Space
                                    glm::vec3(125,125,0), // and looks at the origin
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
    
#ifdef FPS_VIEWER
    Timer timer;
    unsigned short frames = 0;
    timer.start();
    float time = 0;
#endif
    
    while(!engineWindow.isClosed())
    {
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        engineWindow.clear();
        
        
        //body of the draw
#ifdef BATCH_RENDERER
        renderer.begin();
        
        //renderer.submit(&sprite1);
        //renderer.submit(&sprite2);
        //renderer.submit(&sprite3);
         
        
        
        for(auto sprite : spriteVec) {
            renderer.submit(&sprite);
        }
         
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
#ifdef FPS_VIEWER
        frames++;
        //std::cout<<"elasped time:"<<timer.elaspedTime()<<std::endl;
        if (timer.elaspedTime() - time > 1.0f) {
            time += 1.0f;
            std::cout<<"Fps:"<<frames<<std::endl;
            frames = 0;
        }
#endif
        
    }
    
    engineWindow.close();
    
    return 0;
}