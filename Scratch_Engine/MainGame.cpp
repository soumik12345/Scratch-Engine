#include "MainGame.h"
#include "Sprite.h"
#include "GLSLProgram.h"
#include "Errors.h"
#include "Primitives.h"
#include<iostream>
#include<string>

using namespace std;


MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 800;
	_screenHeight = 600;
	_gameState = GameState::PLAY;
}

MainGame::~MainGame() {

}

void MainGame::run() {
	initSystems();

	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	gameLoop();
}

void MainGame::initSystems() {
	// Initialize Everything
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create SDL window
	_window = SDL_CreateWindow("Scratch Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
		fatalError("Unable to open SDL window");

	// Create SDL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
		fatalError("Unable to create SDL GL Context");

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
		fatalError("Unable to initialize GLEW");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	initShaders();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.linkShaders();
}

void MainGame::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		default:
			break;
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//cout << evnt.motion.x << " " << evnt.motion.y << endl;
			break;
		}
	}
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawDDALine(0, 0, 300, 500);

	/*
	_colorProgram.use();

	_sprite.draw(); // Sprite Drawing

	_colorProgram.unuse();
	*/

	SDL_GL_SwapWindow(_window);
}

