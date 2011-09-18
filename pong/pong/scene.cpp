
#include "scene.h"

// Vertex functions
void Vertex::translate(float x, float y, float z) {
	XYZW[0] += x;
	XYZW[1] += y;
	XYZW[2] += z;
}

// element functions
Element::Element(Vertex new_verts[], int size, GLenum display){
	display_type = display;
	iter = verticies.begin();
	for( int i = 0; i < size; i++) {
		iter = verticies.insert(iter, new_verts[i]);
	}
}

Element::Element(vector<Vertex> new_verts, GLenum display){
	display_type = display;
	iter = verticies.begin();
	for( unsigned int i = 0; i < new_verts.size(); i++) {
		iter = verticies.insert(iter, new_verts[i]);
	}
}

float Element::min_x() {
	float temp_min = NULL;
	for ( unsigned int i = 0; i < verticies.size(); i++) {
		if (temp_min == NULL || verticies[i].XYZW[0] < temp_min)
		{
			temp_min = verticies[i].XYZW[0];
		}
	}
	return temp_min;
}

float Element::max_x() {
	float temp_max = NULL;
	for ( unsigned int i = 0; i < verticies.size(); i++) {
		if (temp_max == NULL || verticies[i].XYZW[0] > temp_max)
		{
			temp_max = verticies[i].XYZW[0];
		}
	}
	return temp_max;
}

float Element::min_y() {
	float temp_min = NULL;
	for ( unsigned int i = 0; i < verticies.size(); i++) {
		if (temp_min == NULL || verticies[i].XYZW[1] < temp_min)
		{
			temp_min = verticies[i].XYZW[1];
		}
	}
	return temp_min;
}

float Element::max_y() {
	float temp_max = NULL;
	for ( unsigned int i = 0; i < verticies.size(); i++) {
		if (temp_max == NULL || verticies[i].XYZW[1] > temp_max)
		{
			temp_max = verticies[i].XYZW[1];
		}
	}
	return temp_max;
}

void Element::set_movement(float x, float y, float z) {
	float length = sqrt(x*x + y * y + z * z);
	
	movement_vector[0] = x/length;
	movement_vector[1] = y/length;
	movement_vector[2] = z/length;
	movement_vector[3] = 1;
}

void Element::move(float magnitude) {

	translate(movement_vector[0] * magnitude, movement_vector[1] * magnitude, movement_vector[2] * magnitude);
}

void Element::translate(float x_magnitude, float y_magnitude, float z_magnitude) {

	for (unsigned int i = 0; i < verticies.size(); i++) {
		verticies[i].translate(x_magnitude, y_magnitude, z_magnitude);
	}
}


// Paddle Functions
void Paddle::translate(float x_magnitude, float y_magnitude, float z_magnitude) {
	if (verticies[2].XYZW[1] >= 0.9f || (verticies[2].XYZW[1] + y_magnitude) > 0.9f || verticies[0].XYZW[1] <= -0.9f || (verticies[0].XYZW[1] + y_magnitude) < -0.9f)
	{
		for (unsigned int i = 0; i < verticies.size(); i++) {
			verticies[i].translate(x_magnitude, 0.0f, z_magnitude);
		}
	} else {
		for (unsigned int i = 0; i < verticies.size(); i++) {
			verticies[i].translate(x_magnitude, y_magnitude, z_magnitude);
		}
	}
}


// Scene Functions
Scene::Scene() {
	
	left_score = right_score = 0;

	Vertex left_paddle_verticies[] =
	{
		{ { -0.9f,  0.2f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { -0.8f,  0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.9f, -0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
		{ { -0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	Vertex right_paddle_verticies[] =
	{
		{ {  0.8f,  0.2f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  0.9f,  0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ {  0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
		{ {  0.9f, -0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	Vertex border[] =
	{
		{ { -0.9f,  0.9f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  0.9f,  0.9f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  0.9f, -0.9f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { -0.9f, -0.9f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }
	};

	Vertex left_goal_verts[] =
	{	
		{ { -0.8f,  0.9f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ { -0.8f, -0.9f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }
	};

	Vertex right_goal_verts[] =
	{
		{ {  0.8f,  0.9f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ {  0.8f, -0.9f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }
	};

	new_ball();

	Vertex left_dotted_line_start = { { -0.801f, -0.9f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}};
	Vertex right_dotted_line_start = { { 0.8f, -0.9f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}};

	Element left_dotted_line = dotted_line_up_x_dir(left_dotted_line_start, 0.05f);
	Element right_dotted_line = dotted_line_up_x_dir(right_dotted_line_start, 0.05f);
	
	elements.push_back(left_dotted_line);
	elements.push_back(right_dotted_line);

	Paddle left_paddle(left_paddle_verticies, 4, GL_LINE_LOOP );
	Paddle right_paddle(right_paddle_verticies, 4, GL_TRIANGLE_STRIP );
	leftPaddle = left_paddle;
	rightPaddle = right_paddle;

	Element border_e(border, 4, GL_LINE_LOOP);
	elements.push_back( border_e);

	game_started = false;

}

Element Scene::dotted_line_up_x_dir(Vertex start, float segment_size) {

	vector<Vertex> left_dline_verticies, right_dline_verticies;
	float half_seg = segment_size / 2.0f;
	float quar_seg = half_seg / 2.0f;
	for(float i = -0.9f; i < 0.9f; i += segment_size) {
		start.XYZW[1] = i + quar_seg;
		left_dline_verticies.push_back(start);
		start.XYZW[1] = i + half_seg + quar_seg;
		left_dline_verticies.push_back(start);	
	}
	Element left_dotted_line(left_dline_verticies, GL_LINES);
	return left_dotted_line;
}

void Scene::new_ball() {
	Vertex start_circle = {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
	vector<Vertex> ball_verticies;

	ball_verticies.push_back(start_circle);
	
	ball_radius = 0.05f;
	float deg2rad = float(3.14159)/float(180.0);

	Vertex temp = {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};

	for(int i = 1; i < 361; i++) {
		float x = cos(float(i-1) * deg2rad ) * ball_radius;
		float y = sin(float(i-1) * deg2rad ) * ball_radius;
		temp.XYZW[0] = x;
		temp.XYZW[1] = y;
		ball_verticies.push_back(temp);
	}

	Element circle(ball_verticies, GL_TRIANGLE_FAN);
	ball = circle;

	game_speed = 0.01f;
}

void Scene::tick() {
	//  if game has started move the ball
	if(game_started) {
		ball.move(game_speed);
	}
	//  the ball crosses a y boundary reverse the y component of the movement vector
	if((ball.verticies[0].XYZW[1]+ ball_radius) > 0.9f || (ball.verticies[0].XYZW[1] - ball_radius) < -0.9f) {
		ball.movement_vector[1] *= -1;
	}


	// if ball collides with the paddle reverse the x component of the movement vector
	if(ball.max_x() > rightPaddle.min_x() ) {
		float ball_center_y = ball.verticies[0].XYZW[1];
		if(ball_center_y < rightPaddle.max_y() && ball_center_y > rightPaddle.min_y() ) {
			ball.movement_vector[0] *= -1;
			game_speed += 0.002f;
		}
		else {
			left_score += 1;
			std::cout<< "\n Left Player Scored!!! \n" << "Score: " << left_score << " to " << right_score << "\n";
			new_ball();
			game_started = false;
		}
	}
	if(ball.min_x() < leftPaddle.max_x() ) {
		float ball_center_y = ball.verticies[0].XYZW[1];
		if(ball_center_y < leftPaddle.max_y() && ball_center_y > leftPaddle.min_y() ) {
			ball.movement_vector[0] *= -1;
			game_speed += 0.002f;
		}
		else {
			right_score += 1;
			std::cout<< "\n Right Player Scored!!! \n" << "Score: " << right_score << " to " << left_score << "\n";
			new_ball();
			game_started = false;
		}
	}


	if (keyStates['w']) {
		main_scene.leftPaddle.translate(0, .01f, 0.0f);
	}
	if (keyStates['s']) {
		main_scene.leftPaddle.translate(0,-.01f, 0.0f);
	}
	if (keyStates['i']) {
		main_scene.rightPaddle.translate(0, .01f, 0.0f);
	}
	if (keyStates['k']) {
		main_scene.rightPaddle.translate(0,-.01f, 0.0f);
	}


	if (main_scene.left_score >4 ) {
		std::cout << "Left Player Wins!!!! Final score " << main_scene.left_score << " to " << main_scene.right_score << "\n";
		main_scene.left_score = main_scene.right_score = 0;
	}
	if (main_scene.right_score > 4 ) {
		std::cout << "Right Player Wins!!!! Final score " << main_scene.left_score << " to " << main_scene.right_score << "\n";
		main_scene.left_score = main_scene.right_score = 0;
	}

}

void Scene::render_elements() {

	GLint count = 0;
	GLint size = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		size = elements[i].verticies.size();
		glBufferData(GL_ARRAY_BUFFER, (size * sizeof(Vertex)), &(elements[i].verticies[0]), GL_STATIC_DRAW);
		glDrawArrays(elements[i].display_type, 0, size);

	} 

	glBufferData(GL_ARRAY_BUFFER, (leftPaddle.verticies.size() * sizeof(Vertex)), &(leftPaddle.verticies[0]), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBufferData(GL_ARRAY_BUFFER, (rightPaddle.verticies.size() * sizeof(Vertex)), &(rightPaddle.verticies[0]), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBufferData(GL_ARRAY_BUFFER, (ball.verticies.size() * sizeof(Vertex)), &(ball.verticies[0]), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLE_FAN, 0, ball.verticies.size());

}