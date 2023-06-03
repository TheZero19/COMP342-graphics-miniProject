#include<iostream>
#include "gamePhysics.h"

//global variables:
float windowWidth = 1280;
float windowHeight = 960;

//function prototype:
void runGame();

int main() {
	
	runGame();

	return 0;
}

void runGame() {
	//initialize a game window:
	InitWindow(windowWidth, windowHeight, "Best Pong Game - KEKW");

	//initially our game is set to MENU state
	GameState gameState = MENU;

	Color backgroundColor = { 0, 0, 0, 255 };

	//variables for the ball
	int ballcentreX, ballcentreY;
	ballcentreX = GetScreenWidth() / 2;
	ballcentreY = GetScreenHeight() / 2;

	//For the paddles
	Paddle leftPaddle;
	leftPaddle.positionX = 40;
	leftPaddle.positionY = GetScreenHeight() / 2 - 70;

	Paddle rightPaddle;
	rightPaddle.positionX = GetScreenWidth() - 40;
	rightPaddle.positionY = GetScreenHeight() / 2 - 70;

	//For the ball
	Ball ball;
	ball.positionX = GetScreenWidth() / 2;
	ball.positionY = GetScreenHeight() / 2;

	//For the winner text
	const char* winnerText = nullptr;

	while (WindowShouldClose() == false) {

		BeginDrawing();
		ClearBackground(backgroundColor);

		DrawFPS(5, 5);

		StartGame(&gameState);

		if (gameState == GAMEPLAY) {
			//Circle for the ball and two rectangles for paddles

			paddleController(&leftPaddle, &rightPaddle, windowHeight);
			ballMechanics(&ball, windowWidth, windowHeight);
			checkCollisionBallandPaddle(&ball, &leftPaddle, &rightPaddle);
			determineWinner(&ball, winnerText);

			//Draw call
			leftPaddle.Draw();
			rightPaddle.Draw();
			ball.Draw();
		}

		EndDrawing();
	}

	CloseWindow();
}