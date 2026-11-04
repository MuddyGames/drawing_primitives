#include "stdio.h"

#include "raylib.h"

#include "../include/game.h"

Texture2D game_pad; // Declare the gamepad texture globally

void InitGame()
{
	printf("Game Initialized!\n");
	game_pad = LoadTexture("resources/R36SControls480.png"); // Load the gamepad texture
}

void UpdateGame()
{
	DrawText("Game Updating...", 50, 170, 20, DARKBLUE);
}

void DrawGame()
{
	DrawText("Raylib Starter Kit!", 50, 50, 20, DARKBLUE);
	DrawTexture(game_pad, 0, 0, WHITE); // Draw the gamepad texture
}

void CloseGame()
{
	printf("Game Closed!\n");
	UnloadTexture(game_pad);
}
