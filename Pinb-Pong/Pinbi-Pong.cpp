#include "raylib.h"
#include "iostream"



int main() {
	
	// Screen Definitions
	const int screen_width = 1280;
	const int screen_height = 720;
	InitWindow(screen_width, screen_height, "Pinbi-Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		EndDrawing(); 


	}




	CloseWindow();

	return 0;
}
   