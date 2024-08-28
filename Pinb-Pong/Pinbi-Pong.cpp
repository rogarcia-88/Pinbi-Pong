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
		
		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y *= -1;
		}

		if (x + radius >= GetScreenWidth() || x - radius <= 0)
		{
			speed_x *= -1;
		}

	}
};

class Paddle {
protected:
	void LimitMovement() {
		if (y <= 0)
		{
			y = 0;
		}

		if (y + height >= GetScreenHeight())
		{
			y = GetScreenHeight() - height;
		}
	}
public:
	int x, y;
	int width, height;
	int speed;

	void Draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}
	void Update() {
		if (IsKeyDown(KEY_UP))
		{
			y = y - speed;

		}

		if (IsKeyDown(KEY_DOWN))
		{
			y = y + speed;

		}
		LimitMovement();

		

	}
};

class CpuPaddle : public Paddle {
public:
	void Update(int ball_y) {
		if (y + height / 2 > ball_y) 
		{
			y = y - speed;
		}

		if (y + height / 2 <=ball_y)
		{
			y = y + speed;
		}
		LimitMovement();
	}
};

// Objects Instancing
Ball ball; 
Paddle player;
CpuPaddle cpu;

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

	//Paddle Properties
	player.width = 25;
	player.height = 120;
	player.x = screen_width - player.width - 10;
	player.y = screen_height / 2 - player.height / 2;
	player.speed = 6;

	cpu.width = 25;
	cpu.height = 120;
	cpu.x = 10;
	cpu.y = screen_height / 2 - cpu.height / 2;
	cpu.speed = 6;




	while (!WindowShouldClose()) {
		BeginDrawing();

		//Update
		ball.Update();
		player.Update();
		cpu.Update(ball.y);

		//Draw Elements
		ClearBackground(BLACK);
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
		ball.Draw();
		player.Draw();
		cpu.Draw();
		
		
		
		EndDrawing(); 

	}




	CloseWindow();

	return 0;
}
   