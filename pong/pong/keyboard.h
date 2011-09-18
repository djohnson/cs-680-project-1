#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "scene.h"
using namespace std;

//these are defined in main.cpp
extern bool keyStates[256];
extern Scene main_scene;

void keyPressed(unsigned char, int, int);
void keyUnPressed(unsigned char, int, int);
void keyOperations(void);

#endif