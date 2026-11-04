#include <stdio.h>

#include "raylib.h"

#include "../include/game.h"

const int screenWidth = 800;
const int screenHeight = 600;

void GameLoop(void);

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Set the window to be resizable
	InitWindow(screenWidth, screenHeight, "Raylib Template StarterKit GPPI");

	// Initialise Game
	InitGame();

	// Set the game to run at 60 frames per second
	SetTargetFPS(60);

	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// Call GameLoop
		GameLoop();
	}

	// Free resources
	CloseGame();
	CloseWindow();
	return 0;
}

int counter = 0;
char message[12];

void GameLoop(void)
{
	// Update Game Data
	// Should be outside BeginDrawing(); and EndDrawing();
	UpdateGame();

	// Draw Game Objects
	BeginDrawing();

	// Clear the background and draw the welcome message
	ClearBackground(RAYWHITE);

	DrawText("Template Project", 50, 80, 20, LIGHTGRAY);
	DrawText("Gameplay Programming I", 50, 110, 18, LIGHTGRAY);

	// Update the counter message
	sprintf(message, "%d", counter);

	DrawText(message, 50, 140, 20, LIGHTGRAY);

	// Draw the Game Objects
	DrawGame();

	counter++;

	EndDrawing();
}