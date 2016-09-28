//
//  Shader.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 7/19/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "fileutils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
    
    GLuint mShaderProgramID;
    
    //shader file names
    const char* mFragShaderFileName;
    const char* mVertexShaderFileName;
    
    //shader IDs
    GLuint mVertexShader;
    GLuint mFragShader;
    
    //private functions
    void linkShader();
        void cleanupShader();
    void load();
    GLint getUniformLocation(const char*);

public:
    
    Shader(const char* fragShader, const char* vertexShader);    
    bool checkValidShaderProg();
    GLuint getProgramID();
    void enable();
    void disable();
    void disableShader();

    void setUniformMatrix4fv(const char* name, const glm::mat4& mat);
    void setUniform1iv(const char* name, GLsizei count, const GLint* vec);
    void setUniformVec4(const char*, glm::vec4);
};

#endif /* Shader_hpp */
