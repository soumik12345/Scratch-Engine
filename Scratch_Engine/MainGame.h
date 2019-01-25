#pragma once
#include<SDL.h>
#include<GL/glew.h>


class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	void initSystems();

private:
	SDL_Window* _window;
	int _screenWidth, _screenHeight;
};

