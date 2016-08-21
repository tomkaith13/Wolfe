//
//  Engine.cpp
//  Sparky
//
//  Created by BIBIN THOMAS on 7/13/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "Window.h"

int Window::mWinMouseX;
int Window::mWinMouseY;
bool Window::mKeyMap[KEY_MAX];
bool Window::mMouseMap[MOUSE_MAX];


Window::Window(std::string winTitle, int winHeight, int winWidth ) : mWinTitle(winTitle),
    mWinHeight(winHeight),
    mWinWidth(winWidth) { }

int
Window::init() {
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    /* Create a windowed mode window and its OpenGL context */
    mEngineWindow = glfwCreateWindow(mWinWidth,
                                     mWinHeight,
                                     mWinTitle.c_str(),
                                     NULL,
                                     NULL);
    if (!mEngineWindow)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(mEngineWindow);
    
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK) {
        std::cout<<" Unable to initialize glew"<<std::endl;
        return -1;
    }
    
    mWindowActionClose = false;
    glfwSetKeyCallback(mEngineWindow, mKeyStateCB);
    glfwSetCursorPosCallback(mEngineWindow, mWinMousePosCB);
    glfwSetMouseButtonCallback(mEngineWindow, mWinMouseButtonCB);
    //glfwSetWindowUserPointer(mEngineWindow, this);
    
    //init keyMap to be all false
    for (int i=0; i < KEY_MAX; i++)
        mKeyMap[i] = false;
    
    for (int i=0;i< MOUSE_MAX; i++)
        mMouseMap[i] = false;
    
    return 0;
}

Window::~Window()
{
    
    glfwDestroyWindow(mEngineWindow);
}

void
Window::close() {
    
    glfwTerminate();

}

bool
Window::isClosed() {
    return mWindowActionClose;
}

void
Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
Window::update() {
    /* Poll for and process events */
    glfwPollEvents();
    
    if (glfwWindowShouldClose(mEngineWindow))
        mWindowActionClose = true;
    
    /* Swap front and back buffers */
    glfwSwapBuffers(mEngineWindow);
    
}

void
Window::mWinMousePosCB(GLFWwindow* win, double x, double y) {
    
    int winHeight, winWidth;
    glfwGetWindowSize(win, &winWidth, &winHeight);
    
    //Window* userWindow = (Window*)glfwGetWindowUserPointer(win);
    
    if ((x >= 0 && x <= winWidth) && (y >=0 && y <= winHeight)) {
        Window::mWinMouseX = x;
        Window::mWinMouseY = y;
    }
    
}

void
Window::mKeyStateCB(GLFWwindow *window,
                    int key, int scancode,
                    int action, int mods) {
    
    if (action != GLFW_RELEASE){
        mKeyMap[key] = true;
    } else {
        mKeyMap[key] = false;
    }
    
}

void
Window::mWinMouseButtonCB(GLFWwindow* window, int button,
                          int action,
                          int mods) {
    
    if (action != GLFW_RELEASE)
        mMouseMap[button] = true;
    else
        mMouseMap[button] = false;
}



std::pair<int, int>
Window::getWinMousePosition() {
    std::pair<int, int> posPair;
    
    posPair.first = Window::mWinMouseX;
    posPair.second = Window::mWinMouseY;
    
    return posPair;
}

bool
Window::isKeyPressed(int key) {
    return mKeyMap[key];
}

bool
Window::isMouseButtonPressed(int key) {
    return mMouseMap[key];
}
