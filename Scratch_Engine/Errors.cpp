#include "Errors.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<SDL.h>

using namespace std;

void fatalError(string errorString) {
	cout << errorString << endl;
	cout << "Enter any key to quit.... ";
	int inp;
	cin >> inp;
	SDL_Quit();
	exit(69);
}