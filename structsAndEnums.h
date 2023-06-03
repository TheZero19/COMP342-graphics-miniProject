#pragma once

//to select game state:
enum GameState {
	MENU,
	GAMEPLAY
};

struct Ball {
	float positionX, positionY; //represents the centre of the ball/circle
	float radius = 10;
	float speedX = 400;
	float speedY = 400;

	void Draw() {
		DrawCircle((int)positionX, (int)positionY, (int)radius, RED);
	}

};

struct Paddle {
	float positionX, positionY;  //represents the top-left of the paddle/rectangle
	float speed = 1000;
	float width = 20;
	float height = 140;

	void Draw() {
		//the offset helps us draw rectangle from the top portion of the rectangle instead of the centre position.
		DrawRectangle((int)(positionX), (int)(positionY), (int)width, (int)height, WHITE);
	}

	//returning "Rectangle" type for our collision
	Rectangle getRectangle() {
		return Rectangle{ positionX, positionY, width, height };
	}
};