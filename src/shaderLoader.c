#include "shaderLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



GLchar *loadShader(char *filename){
    GLchar *shaderSource;
    int elements = 0;
    unsigned long fileLength;
    FILE *shader;
    shader = fopen(filename,"r");
    if (shader){
        fseek(shader,0,SEEK_END);
        fileLength = ftell(shader);
        fseek(shader,0,SEEK_SET);
        shaderSource = calloc(1,fileLength+sizeof(GLchar));
        if (!shaderSource)
            return NULL;
        fread(shaderSource,1,fileLength,shader);
        elements = fileLength/sizeof(GLchar);
        shaderSource[elements]= '\0';
    }else{
        return NULL;
    }
    fclose(shader);
    return shaderSource;  
}
