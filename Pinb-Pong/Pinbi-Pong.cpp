#include "raylib.h"

//Global Variables
int cpu_score = 0;
int player_score = 0;

Color Green = Color{ 38,185,154,255 };
Color Dark_Green = Color{ 20,160,133,255 };
Color Light_Green = Color{ 129,204,184,255 };
Color Yellow = Color{ 243,213,91,255 };

// Objects Creation
class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;

	void Draw() 
	{
		DrawCircle(x, y, radius, Yellow);
	}
	void Update() 
	{
		x += speed_x;
		y += speed_y;
		
		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y *= -1;
		}

		if (x + radius >= GetScreenWidth()) // CPU Wins
		{
			cpu_score++;
			ResetBall();
		}
			
		if (x - radius <= 0) // Player Wins
		{
			player_score++;
			ResetBall();
		}	
	}
	
	void ResetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_choices[2] = { -1,1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)];
		speed_y *= speed_choices[GetRandomValue(0, 1)];

	}
};

class Collider{
private:
	int PosX, PosY;


public:
	
	float width, height;
	int frames_counter = 0;

	void setPos(int spawnX, int spawnY) {
		PosX = spawnX;
		PosY = spawnY;
		
		frames_counter++;

		if (((frames_counter / 120) % 2) == 1)
		{
			spawnX = GetRandomValue(1, 32);
			spawnY = GetRandomValue(1, 20);
			frames_counter = 0;
		}
	}

	int getPosX() {
		return PosX;
	}
	int getPosY() {
		return PosY;
	}
	void Draw()
	{
		
		
		/*PosX = GetScreenWidth() /  spawn_x - width / 2;
		PosY = GetScreenHeight() / spawn_y - height / 2;

		DrawRectangle(PosX,PosY, width, height, WHITE);
		DrawText(TextFormat("%i", frames_counter), 360, 180, 80, LIGHTGRAY);*/
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
	float x, y;
	float width, height;
	int speed;
	void Draw()
	{
		DrawRectangleRounded(Rectangle{ x, y,width, height }, 0.8, 0, WHITE);
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
Collider collider;



int main() {
	
	// Initialization
	 const int screen_width = 1280;
	 const int screen_height = 800;
	InitWindow(screen_width, screen_height, "Pinbi-Pong");
	SetTargetFPS(60);
	float randomX = screen_width / GetRandomValue(1, 32);
	float randomY = screen_height / GetRandomValue(1, 20);
	int frames_counter = 0;

	
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

	//Collider Properties
	collider.height = 40;
	collider.width = 40;
	int spawnX = GetRandomValue(1, 32);
	int spawnY = GetRandomValue(1, 20);


	//Game Loop
	while (!WindowShouldClose()) 
	{
		
		BeginDrawing();

		if (cpu_score == 10)
		{
			ClearBackground(WHITE);
			DrawText("Game Over!", screen_width / 2, screen_height / 2, 60, RED);
		}

		else if (player_score == 10)
		{
			ClearBackground(WHITE);
			DrawText("Player Win!", screen_width / 2, screen_height / 2, 60, GREEN);
		}

		else

		{
			//Updating
			ball.Update();
			player.Update();
			cpu.Update(ball.y);
			collider.setPos(200, 200);

			
			frames_counter++;
			if (((frames_counter / 120) % 2) == 1)
			{
				randomX = GetRandomValue(1, 1200) ;
				randomY = GetRandomValue(1, 720);
				frames_counter = 0;
			}

			//Check Collisions
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
			{
				ball.speed_x *= -1;
			}
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
			{
				ball.speed_x *= -1;
			}
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{randomX, randomY, 80, 80}))
			{
				ball.speed_x *= -1;
			}

			//Draw Elements
			ClearBackground(Dark_Green);
			DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
			DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
			DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
			ball.Draw();
			player.Draw();
			cpu.Draw();
			DrawRectangle(randomX, randomY, 80, 80, LIGHTGRAY);

			//collider.Draw();
			DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
			DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
		}

			
		EndDrawing(); 

	}

	CloseWindow();

	return 0;
}
   