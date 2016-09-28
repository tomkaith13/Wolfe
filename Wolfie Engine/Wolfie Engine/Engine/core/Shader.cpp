//
//  Shader.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/19/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "Shader.h"

Shader::Shader(const char* fragShader, const char* vertexShader):
    mFragShaderFileName(fragShader), mVertexShaderFileName(vertexShader),
    mShaderProgramID(-1) {
    
    load();
}

void Shader::load()
{
    //creating program id used for both vertex and fragment shader
    mShaderProgramID = glCreateProgram();
    char infoLogBuffer[512];
    
    
    //Creating vertex shader
    mVertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLint mVertexShaderCompileStatus = 0;
    
    std::string vShaderText = file_reader(mVertexShaderFileName);
    const char* mVertexShaderSource = vShaderText.c_str();
    
    glShaderSource(mVertexShader, 1, &mVertexShaderSource, NULL);
    glCompileShader(mVertexShader);
    
    glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &mVertexShaderCompileStatus);
    
    if (mVertexShaderCompileStatus == GL_FALSE)
    {
        std::cout<<"Vertex Shader Compilation failed"<<std::endl;
        
        glGetShaderInfoLog(mVertexShader, 512, NULL, infoLogBuffer);
        std::cout<<infoLogBuffer<<std::endl;
        
        //cleanup both shaders
        mShaderProgramID = -1;
        cleanupShader();
        
        return;
    }
    
    std::cout<<"Vertex shader: Compiled"<<std::endl;
    //Creating fragment shader
    mFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLint mFragShaderCompileStatus = 0;
    
    std::string fShaderText = file_reader(mFragShaderFileName);
    const char* mFragShaderSource = fShaderText.c_str();
    glShaderSource(mFragShader, 1, &mFragShaderSource, NULL);
    glCompileShader(mFragShader);
    
    glGetShaderiv(mFragShader, GL_COMPILE_STATUS, &mFragShaderCompileStatus);
    
    if (mFragShaderCompileStatus == GL_FALSE)
    {
        std::cout<<"Fragment Shader Compilation failed"<<std::endl;
        glGetShaderInfoLog(mFragShader, 512, NULL, infoLogBuffer);
        std::cout<<infoLogBuffer<<std::endl;
        
        
        //cleanup both shaders
        mShaderProgramID = -1;

        cleanupShader();
        
        return;
    }
    
    std::cout<<"Fragment shader: Compiled"<<std::endl;
    linkShader();
    std::cout<<"shader program: Linked"<<std::endl;



}

void Shader::linkShader() {
    GLint linkStatus;
    char linkInfoLogBuffer[512];
    
    glAttachShader(mShaderProgramID, mVertexShader);
    glAttachShader(mShaderProgramID, mFragShader);
    
    //Link shader program
    glLinkProgram(mShaderProgramID);
    glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &linkStatus);
    
    if (linkStatus == GL_FALSE) {
        glGetProgramInfoLog(mShaderProgramID, 512, NULL, linkInfoLogBuffer);
        
        std::cout<<"Shader Linking failed! "<<linkInfoLogBuffer<<std::endl;
        mShaderProgramID = -1;

        
        disableShader();
        cleanupShader();
        return;
    }
    
    //finally, disable the use of the shader in the program
    disableShader();
    cleanupShader();
    
}

void Shader::disableShader() {
    
    glDetachShader(mShaderProgramID, mVertexShader);
    glDetachShader(mShaderProgramID, mFragShader);
    //cleanupShader();
    
}

void Shader::cleanupShader() {
    
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}

bool Shader::checkValidShaderProg()
{
    if (mShaderProgramID == -1)
        return false;
    else
        return true;
}

GLuint Shader::getProgramID()
{
    return mShaderProgramID;
}

void Shader::enable()
{
    glUseProgram(mShaderProgramID);
}

void Shader::disable()
{
    glUseProgram(0);
}

GLint Shader::getUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(mShaderProgramID, uniformName);
    
}

void Shader::setUniformMatrix4fv(const char* name, const glm::mat4& mat)
{
    glUniformMatrix4fv(getUniformLocation(name),
                       1,
                       GL_FALSE,
                       glm::value_ptr(mat));
}

void Shader::setUniformVec4(const char* name, glm::vec4 vec)
{
    glUniform4fv(getUniformLocation(name),
                       1,                 
                       glm::value_ptr(vec));
}

void Shader::setUniform1iv(const char* name, GLsizei count, const GLint* vec)
{
    glUniform1iv(getUniformLocation(name),
                 count,
                 vec);
}

