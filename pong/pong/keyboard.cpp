#include "keyboard.h"
#include <time.h>

int count = 0;

void keyOperations (void) {
	
	if (keyStates[27]) {
		glutLeaveMainLoop();
	}
	if (keyStates['o']) {
		if ( !main_scene.game_started ) {
			count += 1;
			main_scene.game_started = true;
			srand( (unsigned)time(NULL) );

			float min_x = 0.3f;
			float max_x = 1.0f;

			float min_y = 0.3f;
			float max_y = 1.0f;

			float x = (max_x - min_x) * ((float)rand()/RAND_MAX)+min_x;
			float y = (max_y - min_y) * ((float)rand()/RAND_MAX)+min_y;

			int x_neg, y_neg;

			x_neg = (rand()%10 > 4) ? -1 : 1;
			y_neg = (rand()%10 > 4) ? -1 : 1;

			main_scene.ball.set_movement( x* x_neg, y * y_neg, 0.0f);
		}
	}
//	if (keyStates['l']) {
//		main_scene.ball.set_movement(-0.05f, -0.1f, 0.0f);
//	}
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true;
	//std::cout << "keyboardDown on " << key << "\n";
}

void keyUnPressed(unsigned char key, int x, int y) {
	keyStates[key] = false;
	//std::cout << "KeyboardUP on " << key << "\n" << "count: " << count << "\n";
}
