#include "raylib.h"
#include "iostream"

using namespace std;

int main() {
	std::cout << "Start the game" << endl;

	const int screen_width = 1280;
	const int screen_height = 720;

	InitWindow(screen_width, screen_height, "Pinbi-Pong");


	CloseWindow();

	return 0;
}
   