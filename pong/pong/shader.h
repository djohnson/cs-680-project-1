#ifndef SHADER_H
#define SHADER_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <sstream>

#include <string>
#include <fstream>
#include <streambuf>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "scene.h"
#include "util.h"

using namespace std;



//these are defined in main.cpp
extern Scene main_scene;

static GLuint make_buffer( GLenum ,  Vertex , GLsizei);
static GLuint make_texture(const char *filename);

void CreateVBO(void);
void DestroyVBO(void);
void CreateShaders(void);
void DestroyShaders(void);
void Cleanup(void);
#endif