#include "shaderLoader.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHARBUFSIZE 128
#define CHARBUFMAXIDX (CHARBUFSIZE - 1)

GLchar *loadShader(char *filename){
    GLchar *charBuf = calloc(CHARBUFSIZE,sizeof(GLchar));
    if (charBuf == NULL)
        return NULL;
    FILE *shader;
    int bufIndex = 0;
    int sourceBufSize = CHARBUFSIZE;
    shader = fopen(filename,"r");
    if (shader == NULL){
        free(charBuf);
        return NULL;        
    }else{        
        while(!feof(shader)){    
            charBuf[bufIndex] = (GLchar) fgetc(shader);
            bufIndex += 1;
            if ((bufIndex % CHARBUFMAXIDX) == 0){
                if (duplicateBuffer(charBuf,sourceBufSize) >= 0){
                    sourceBufSize = sourceBufSize*2;
                }else{
                    free(charBuf);
                    return NULL;
                }    
            }
        }
        fclose(shader);
        charBuf[bufIndex-1] = '\0';
        int size = strlen(charBuf) + 1;
        GLchar *shaderSource = calloc(size,sizeof(GLchar));
        memcpy(shaderSource,charBuf,size);
        destroyBuffer(charBuf);
        return shaderSource;  
    }
}

void destroyBuffer(GLchar *buffer){
    free(buffer);
}


int duplicateBuffer(GLchar *buffer,int currentSize){
    GLchar *expandedBuffer = calloc(currentSize*2,sizeof(GLchar));
    if (expandedBuffer){
        memcpy(expandedBuffer,buffer,currentSize);
        destroyBuffer(buffer);
        buffer = expandedBuffer;
        return 0;
    }else{
        return -1;
    }
}
