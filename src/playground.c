

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "shaderCompiler.h"

static void error_callback(int error, const char* description){
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void renderRedBackground();
void renderMultiBackground(float time);
void renderBlackBckgWithShader(GLuint program);
void renderBlackBgWithTriangleMoving(GLuint program);


#ifdef __APPLE__ && __MACH__
    char* fragmentFile = "/Users/thbounzer/Documents/Sources/C/oglNativePlayground/shaders/fragmentOne.glsl";
    char* vertexFile = "/Users/thbounzer/Documents/Sources/C/oglNativePlayground/shaders/basicTriangle.glsl";
#elif __linux__
    char* fragmentFile = "/home/thbounzer/Documents/Sources/C/oglNativePlayground/shaders/fragmentOne.glsl";
    char* vertexFile = "/home/thbounzer/Documents/Sources/C/oglNativePlayground/shaders/basicTriangle.glsl";
#else
    
#endif
    
    
int main(void){
    GLFWwindow* window;
    GLuint program, voa, vertexShaderId, fragmentShaderId; 
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
    vertexShaderId = compileShader(vertexFile,GL_VERTEX_SHADER);
    fragmentShaderId = compileShader(fragmentFile,GL_FRAGMENT_SHADER);
    program = compileProgram(vertexShaderId,fragmentShaderId);
    glGenVertexArrays(1, &voa);
    glBindVertexArray(voa);
    
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        renderBlackBgWithTriangleMoving(program);
        
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

void renderBlackBckgWithShader(GLuint program){
    static const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR,0,black);
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void renderBlackBgWithTriangleMoving(GLuint program){
    static const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat position[] = {(float) sin(glfwGetTime())*0.5f, (float) cos(glfwGetTime())*0.6f,0.0f, 0.0f };
    glClearBufferfv(GL_COLOR,0,black);
    glUseProgram(program);
    glVertexAttrib4fv(0,position);
    glDrawArrays(GL_TRIANGLES, 0, 3);    
}

void renderMultiBackground(float time){
    GLfloat color[] = {sin(time), cos(time), 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR,0,color);    
}