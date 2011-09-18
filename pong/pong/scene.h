#ifndef SCENE_H
#define SCENE_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "util.h"
using namespace std;

static const double PI = 3.14159265358979323846;

class Vertex
{
	public:
		float XYZW[4];
		float RGBA[4];
		void translate(float, float, float);		
};

class Element {

	public:
		Element() {};
		
		// constructor for when passing an array of floats in
		Element(Vertex[], int, GLenum);
		
		// constructor for when passing verticies via vector
		Element(vector<Vertex>, GLenum);
		
		// triangle_strip, fan, etc
		GLenum display_type;

		vector<Vertex> verticies;
		vector<Vertex>::iterator iter;

		// direction the object is moving
		float movement_vector[4];

		// translate the object in the direction of it's movement vector by a set amount
		void move(float);

		void set_movement(float, float, float);

		// manual adjustment functions
		void translate(float, float, float);
		void set_color(char, float[4]);

		// return the min/max x/y value of the verticies
		float max_x();
		float min_x();
		float max_y();
		float min_y();
};

class Paddle : public Element {
	public:
		Paddle() {};
		Paddle(Vertex new_verts[], int size, GLenum display) : Element(){
			display_type = display;
			iter = verticies.begin();
			for( int i = 0; i < size; i++) {
				iter = verticies.insert(iter, new_verts[i]);
			}
		};
		void translate(float, float, float);
};

class Scene {

public:
	Scene();

	// elements stores the random geometry that I just need to set and forget
	vector<Element> elements;
	
	// ball and paddles are elements with special properties: movement  collision detection etc
	Element ball;
	Paddle leftPaddle;
	Paddle rightPaddle;
	
	// scores

	int left_score, right_score;

	// game_started is used to halt game logic until a button press says go
	bool game_started;

	// two_player determines if one paddle should be cpu controlled or not
	bool two_player;

	// the radius of the ball
	float ball_radius;

	// the magnitude to move the ball each turn
	float game_speed;

	//
	void new_ball();

	//render_elements loops through and draws everything 
	void render_elements();
	void tick();

	Element dotted_line_up_x_dir(Vertex start, float segment_size); 
};


//these are defined in main.cpp
extern bool keyStates[256];
extern Scene main_scene;

#endif