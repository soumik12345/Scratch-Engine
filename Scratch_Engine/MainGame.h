#pragma once
#include<SDL.h>
#include<GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"

enum  class GameState {
	PLAY, EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	SDL_Window* _window;
	int _screenWidth, _screenHeight;
	GameState _gameState;
	Sprite _sprite;
	GLSLProgram _colorProgram;

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void initShaders();
};
