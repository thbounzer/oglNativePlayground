#ifndef SHADERCOMPILER_H
#define	SHADERCOMPILER_H
#include <GLFW/glfw3.h>

GLuint compileShader(char *shaderFilePath, GLint shaderType);
GLint compileProgram(GLint vertexShaderId, GLint fragmentShaderId);
GLuint checkShaderCompilation(GLint shaderId,char *type);




#endif	/* SHADERCOMPILER_H */

