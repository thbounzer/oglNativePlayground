

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "shaderLoader.h"

static void error_callback(int error, const char* description){
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void renderRedBackground();
void renderMultiBackground(float time);
void renderRedBckgWithShader(GLuint program);
GLuint compileShaders(char *vertexShad, char *fragmentShad);
GLuint checkShaderCompilation(GLint shaderId,char *type);

char* fragmentFile = "/home/carlo/Documents/Sources/Various/oglNativePlayground/shaders/fragmentOne.glsl";
char* vertexFile = "/home/carlo/Documents/Sources/Various/oglNativePlayground/shaders/vertexOne.glsl";

int main(void){
    GLFWwindow* window;
    GLuint program, voa; 
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   
    window = glfwCreateWindow(640, 480, "GLFW NATIVE PLAYGROUND", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    program = compileShaders(vertexFile,fragmentFile);
    glGenVertexArrays(1, &voa);
    glBindVertexArray(voa);
    glPointSize(40.0f);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        renderRedBckgWithShader(program);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &voa);
    glDeleteProgram(program);    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);    
}

void renderRedBackground(){
    static const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR,0,red);
}

void renderRedBckgWithShader(GLuint program){
    static const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR,0,black);
    glUseProgram(program);
    glDrawArrays(GL_POINTS, 0, 1);
}

void renderMultiBackground(float time){
    GLfloat color[] = {sin(time), cos(time), 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR,0,color);    
}

GLuint compileShaders(char *vertexShadFilePath, char *fragmentShadFilePath){
    GLuint vertexShaderId;
    GLuint fragmentShaderId;
    GLuint program, logSize;
    
    GLchar *vertexShader = loadShader(vertexShadFilePath);
    GLchar *fragmentShader = loadShader(fragmentShadFilePath);
    
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
    glCompileShader(vertexShaderId);
    checkShaderCompilation(vertexShaderId,"vertex");

    
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
    glCompileShader(fragmentShaderId);

    checkShaderCompilation(fragmentShaderId,"fragment");
    
     
    program = glCreateProgram();
    glAttachShader(program,vertexShaderId);
    glAttachShader(program,fragmentShaderId);
    glLinkProgram(program);
    
    
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    free(vertexShader);
    free(fragmentShader);    
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
