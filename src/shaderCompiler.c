#include "shaderCompiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include "shaderLoader.h"


GLuint compileShader(char *shaderFilePath, GLint shaderType){
    GLuint shaderId;
    char *shaderTypeName;
    switch(shaderType){
        case GL_VERTEX_SHADER:
            shaderTypeName = "vertex";
        break;
        case GL_FRAGMENT_SHADER:
            shaderTypeName = "fragment";
        break;
        default:
            return NULL;    /*unsupported shader type*/
    }    
    GLchar *shaderSource = loadShader(shaderFilePath);
    printf("%s Shader:\n",shaderTypeName);
    puts(shaderSource);
    
    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);
    checkShaderCompilation(shaderId,shaderTypeName);
    free(shaderSource);
    return shaderId;
}

GLint compileProgram(GLint vertexShaderId, GLint fragmentShaderId){
    GLint program;
    program = glCreateProgram();
    glAttachShader(program,vertexShaderId);
    glAttachShader(program,fragmentShaderId);
    glLinkProgram(program);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId); 
    return program;
}

GLuint checkShaderCompilation(GLint shaderId,char *type){
    GLuint compilationStatus;
    GLuint logSize;
    compilationStatus = logSize = 0;
    glGetShaderiv(shaderId,GL_COMPILE_STATUS,&compilationStatus);
    if (compilationStatus == GL_FALSE){
        printf("Compilation of %s shader failed! See log:\n",type);
        glGetShaderiv(shaderId,GL_INFO_LOG_LENGTH,&logSize);
        GLchar *infolog = calloc(logSize+1,sizeof(GLchar));
        glGetShaderInfoLog(shaderId,logSize+1,NULL,infolog);
        puts(infolog);
        free(infolog);
        return GL_FALSE;
    }else{
        return GL_TRUE;
    }
}
