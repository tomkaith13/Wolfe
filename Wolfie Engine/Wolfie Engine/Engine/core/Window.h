//
//  Window.h
//  Sparky
//
//  Created by BIBIN THOMAS on 7/12/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef Window_h
#define Window_h
#include "fileutils.h"
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <utility>
#include <string>

#define KEY_MAX 1024
#define MOUSE_MAX 32

class Window {
    
    const std::string mWinTitle;
    int mWinHeight;
    int mWinWidth;
    GLFWwindow* mEngineWindow;
    bool mWindowActionClose;
    
    /*
     all the input callbacks end are static because glfw needs static methods and hence end with the name convention 'CB'
     */
    static void mWinMousePosCB(GLFWwindow*, double, double);
    static void mKeyStateCB(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mWinMouseButtonCB(GLFWwindow* window, int button, int action, int mods);


    static bool mKeyMap[KEY_MAX];
    static bool mMouseMap[MOUSE_MAX];
    static int mWinMouseX, mWinMouseY;

    
public:

    Window(std::string, int, int);
    ~Window();
    int init();
    
    void update();
    void clear();
    void close();
    bool isClosed();
    bool isKeyPressed(int);
    bool isMouseButtonPressed(int);
    std::pair<int, int> getWinMousePosition();
};



#endif /* Window_h */
