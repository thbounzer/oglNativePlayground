/* 
 * File:   shaderLoader.h
 * Author: carlo
 *
 * Created on December 10, 2014, 4:06 PM
 */
#include <GLFW/glfw3.h>
#ifndef SHADERLOADER_H
#define	SHADERLOADER_H

GLchar *loadShader(char *filename);

void destroyBuffer(GLchar *buffer);

int duplicateBuffer(GLchar *buffer,int currentSize);

#endif	/* SHADERLOADER_H */

