//
//  main.cpp - This file exists merely as a way to show the user how to use the functions created by
//              the engine's APIs.
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/11/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "Wolfie.h"
#include <vector>
#include <chrono>
#include <random>

#define FPS_VIEWER 1

int main(void)
{
    //GLuint shaderProgID;
    Window engineWindow("Wolfie", 600, 800);
    std::vector<Sprite> spriteVec;
    
    if (engineWindow.init() == -1)
    {
        std::cout<<"Engine initialization error"<<std::endl;
        return -1;
    }
    
    //creating shader program
    Shader shObj(FRAGMENT_SHADER_SOURCE, VERTEX_SHADER_SOURCE);
    //shaderProgID = shObj.getProgramID();
    
    if(!shObj.checkValidShaderProg())
    {
        std::cout<<"Shader compilation issues"<<std::endl;
        return -1;
    }

    // Transformation Calculations
    //model matrix
    
    glm::mat4 modelMat(1.0f);
    //modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f));
    //modelMat = glm::rotate(modelMat, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //modelMat = glm::scale(modelMat, glm::vec3(1.0f, 1.0f, 1.0f));
    
    // View matrix
    glm::mat4 viewMat = glm::lookAt(
                                    glm::vec3(125,5,5), // Camera in World Space
                                    glm::vec3(125,125,0), // and looks at the origin
                                    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                    );
    
    //Projection Matrix
    glm::mat4 projMat = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    
    // final MVP transform
    glm::mat4 mvpMat = projMat * viewMat * modelMat;

    //Randomization logic for sprite colors using <chrono> and <random>
    std::chrono::system_clock::time_point sysTimePoint = std::chrono::system_clock::now();
    double seed = sysTimePoint.time_since_epoch().count();
    std::mt19937 gen(seed);
    
    std::uniform_real_distribution<double> dist;
    
    
    TileLayer *spriteLayer = new TileLayer(&shObj, new BatchRenderer(), mvpMat);
    
    for(int i = 0; i < 250;i += 2.0) {
        for(int j = 0; j < 250; j += 2.0) {
            
            spriteLayer->add(new Sprite(glm::vec3(i, j, 0.0f),
                                        glm::vec2(5.0f, 5.0f),
                                        glm::vec4(dist(gen), dist(gen), dist(gen), 1.0f)
                                        ));
        }
    }
    
#if FPS_VIEWER
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
        spriteLayer->render();
        
        engineWindow.update();
        
        if (engineWindow.isKeyPressed(GLFW_KEY_W))
            std::cout<<" W is pressed!!"<<std::endl;
        
        if (engineWindow.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            std::cout<<"Mouse Left clicked!"<<std::endl;
            std::cout<<"Mouse x:"<<engineWindow.getWinMousePosition().first;
            std::cout<<" Mouse y:"<<engineWindow.getWinMousePosition().second<<std::endl;
        }
        
#if FPS_VIEWER
        frames++;
        if (timer.elaspedTime() - time > 1.0f) {
            time += 1.0f;
            std::cout<<"Fps:"<<frames<<std::endl;
            frames = 0;
        }
#endif
        
    }
    shObj.disableShader();
    engineWindow.close();
    
    return 0;
}