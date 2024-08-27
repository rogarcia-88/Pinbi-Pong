#include "raylib.h"

// Objects Creation
class Ball {
public:
	int x, y;
	int speed_x, speed_y;
	float radius;

	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}
	void Update() {
		x += speed_x;
		y += speed_y;

	}
};

// Objects Instancing
Ball ball;

int main() {
	
	// Screen Definitions
	const int screen_width = 1280;
	const int screen_height = 800;
	InitWindow(screen_width, screen_height, "Pinbi-Pong");
	SetTargetFPS(60);

	//Ball Properties
	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;


	while (!WindowShouldClose()) {
		BeginDrawing();

		//Update
		ball.Update();

		//Draw Elements
		ClearBackground(BLACK);
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
		ball.Draw();
		DrawRectangle(10, screen_height/2 - 60, 25, 120, WHITE);
		DrawRectangle(screen_width-35, screen_height / 2 - 60, 25, 120, WHITE);
		
		EndDrawing(); 

	}




	CloseWindow();

	return 0;
}
   