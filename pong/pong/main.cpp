#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "scene.h"
#include "keyboard.h"
#include "shader.h"
#include "util.h"

#define WINDOW_TITLE "Darren's Pong"

using namespace std;

int CurrentWidth = 800,
	CurrentHeight = 800,
	WindowHandle = 0;

// array for the states of all keys so can accurately detect multiple presses at once
bool keyStates[256] = {false};

// this is my class that contains all the relevant objects and variables for my game
Scene main_scene;



static struct {
    GLuint vertex_buffer, element_buffer;
    GLuint textures[2];
    GLuint vertex_shader, fragment_shader, program;
    
    struct {
        GLint fade_factor;
        GLint textures[2];
    } uniforms;

    struct {
        GLint position;
    } attributes;

    GLfloat fade_factor;
} g_resources;



void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void createMenu(void);
void menu(int);

int main(int argc, char* argv[])
{ 
	// setup glew, glut, create the windows, shaders, vbo, and program
	Initialize(argc, argv);
	
	// loop and do glut stuff
	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[])
{
	// create the window
	InitWindow(argc, argv);
	
	//not sure i need this anymore
	glewExperimental = GL_TRUE;

	// init glew, if errors output and exit
	GLenum GlewInitResult;
	GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) {
		std::cout << "Error: " << glewGetErrorString(GlewInitResult) << "\n";
		exit(EXIT_FAILURE);
	}
	
	//output the current openg version
	std::cout<< "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

	// read the shaders from file and compile/link them
	CreateShaders();

	// create the vbo
	CreateVBO();
	
	// create the menus for our right click action
	createMenu();

	// set the clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char* argv[])
{
	//init glut with a context version of 4
	glutInit(&argc, argv);	
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// set what to do when the window is closed
	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);
	
	// set the window size
	glutInitWindowSize(CurrentWidth, CurrentHeight);

	// use the depth buffer, double buffer, and use alpha
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	//create the window and check for errors
	WindowHandle = glutCreateWindow(WINDOW_TITLE);
	if(WindowHandle < 1) {
		std::cout << "Error: Could not create a rendering window";
		exit(EXIT_FAILURE);
	}
	
	//setting the callback functions
	glutReshapeFunc(ResizeFunction);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUnPressed);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	glutTimerFunc(0, TimerFunction, 0);
	glutCloseFunc(Cleanup);
}

void ResizeFunction(int Width, int Height)
{
	//set the viewport to the new size
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// push vertex data and display it
	main_scene.render_elements();
	
	//swap the buffers because we are done drawing and using doublebuffer
	glutSwapBuffers();

	// redisplay the current window
	glutPostRedisplay();

	// flush GL commands that might be in buffers
	glFlush();
}

void IdleFunction(void)
{
	// redisplay the current window
	glutPostRedisplay();
}

void TimerFunction(int Value)
{
	// do operations based on the current state of the keyboard
	keyOperations();
	
	// update positions of objects
	// do this timed so that no matter what hardware you play on the same movement speeds are acheived
	main_scene.tick();

	// call the timer func again in 10ms
	glutTimerFunc(10, TimerFunction, 1);
}

void menu(int value){
	switch (value) {
		case 0:
			//quit
			glutLeaveMainLoop();
			break;
		case 1:
			// new 2 player game
			break;
		case 2: 
			// new 1 player game
			break;
	}
  // redraw window now
  glutPostRedisplay();
}

void createMenu(void){

  // Create a submenu
   glutCreateMenu(menu);

  // Create the menu
   glutCreateMenu(menu);

  // Create top level menu items
  glutAddMenuEntry("New Two Player Game", 1);
  glutAddMenuEntry("New Single Player Game", 2);
  glutAddMenuEntry("Quit", 0);

  // Let the menu respond on the right mouse button
  glutAttachMenu(GLUT_RIGHT_BUTTON);


}