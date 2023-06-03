#pragma once
#include "raylib.h"
#include "structsAndEnums.h"

//function prototype
void StartGame(GameState* gameState);
void paddleController(Paddle* leftPaddle, Paddle* rightPaddle, float windowHeight);
void ballMechanics(Ball* ball, float windowWidth, float windowHeight);
void checkCollisionBallandPaddle(Ball* ball, Paddle* leftPaddle, Paddle* rightPaddle);
void restartGame(Ball* ball, const char* winnerText);
void determineWinner(Ball* ball, const char* winnerText);


void StartGame(GameState* gameState) {

	//if the gameState is MENU, don't change the gameState until SPACE button is pressed
	//so this function gets executed only at the start of the game.

	if (*gameState == MENU) {
		const char* gameText = "Press SPACE button to start Pong!";
		int gameTextLength = MeasureText(gameText, 50);

		DrawText(gameText, GetScreenWidth() / 2 - gameTextLength / 2, GetScreenHeight() / 2 - 30, 50, DARKGRAY);
		
		if (IsKeyPressed(KEY_SPACE)) {
			*gameState = GAMEPLAY;
		}
	}
}

void paddleController(Paddle* leftPaddle, Paddle* rightPaddle, float windowHeight) {
	if (IsKeyDown(KEY_W) && leftPaddle->positionY >= 0) {
		(*leftPaddle).positionY -= (*leftPaddle).speed * GetFrameTime();
	}

	if (IsKeyDown(KEY_S) && leftPaddle->positionY <= (windowHeight - leftPaddle->height))
	{
		leftPaddle->positionY += leftPaddle->speed * GetFrameTime();
	}

	if (IsKeyDown(KEY_UP) && rightPaddle->positionY >= 0)
	{
		rightPaddle->positionY -= rightPaddle->speed * GetFrameTime();
	}

	if (IsKeyDown(KEY_DOWN) && (*rightPaddle).positionY <= (windowHeight - rightPaddle->height))
	{
		rightPaddle->positionY += rightPaddle->speed * GetFrameTime();
	}
	
	//Note: -> notation and *() to dereference the pointer are the same thing
}

void ballMechanics(Ball* ball, float windowWidth, float windowHeight) {
	ball->positionX += ball->speedX * GetFrameTime();
	ball->positionY += ball->speedY * GetFrameTime();

	if (ball->positionY < 0) {
		ball->positionY = 0;	//if the value went below zero, it would get stuck at the border
		ball->speedY *= -1;
	}
	if (ball->positionY > GetScreenHeight()) {
		ball->positionY = GetScreenHeight(); //also if the value exceeded, ball would get stuck at the border
		ball->speedY *= -1;
	}
}


void checkCollisionBallandPaddle(Ball* ball, Paddle* leftPaddle, Paddle* rightPaddle) {
	//checking Collision for left paddle
	if (CheckCollisionCircleRec(Vector2{ ball->positionX, ball->positionY }, ball->radius, leftPaddle->getRectangle())) {
		ball->speedX *= -1.1f;
	}

	//checking Collision for right paddle
	if (CheckCollisionCircleRec(Vector2{ ball->positionX, ball->positionY }, ball->radius, rightPaddle->getRectangle())) {
		ball->speedX *= -1.1f;
	}
	//Note: after the collision, the ball will gain the speed by 20%
}

void determineWinner(Ball* ball, const char* winnerText) {
	//if the ball goes to the left, right player wins and vice versa
	if (ball->positionX < 0) {
		winnerText = "Right Player Wins!";
	}
	if (ball->positionX > GetScreenWidth()) {
		winnerText = "Left Player Wins!";
	}

	//if the winnerText is no longer nullptr, it means that we have a winner:
	if (winnerText != nullptr) {
		int textWidth = MeasureText(winnerText, 60);
		
		//Drawing the winner text at approximately the middle of the screen.
		DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 40, 60, DARKGRAY);
		restartGame(ball, winnerText);
	}
}

void restartGame(Ball* ball, const char* winnerText) {
	//if we have a winner and if we press "Space" on keyboard, restart the game:

	if (winnerText != nullptr && IsKeyPressed(KEY_SPACE)) {
		//restarting by restoring the ball's original values:
		ball->positionX = GetScreenWidth() / 2;
		ball->positionY = GetScreenHeight() / 2;
		ball->speedX = 400;
		ball->speedY = 400;

		//and also reset the winnerText back to nullptr:
		winnerText = nullptr;
	}

	return;
}