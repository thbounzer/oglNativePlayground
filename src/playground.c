

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
void renderBlackBckgWithShader(GLuint program);
GLuint compileShader(char *shaderSource, GLint shaderType);
GLuint checkShaderCompilation(GLint shaderId,char *type);


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

void renderMultiBackground(float time){
    GLfloat color[] = {sin(time), cos(time), 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR,0,color);    
}

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
