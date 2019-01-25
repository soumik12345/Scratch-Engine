#include "MainGame.h"



MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 800;
	_screenHeight = 600;
}


MainGame::~MainGame()
{
}

void MainGame::run() {
	initSystems();
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Scratch Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
}