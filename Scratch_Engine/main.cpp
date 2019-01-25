#include<iostream>
#include "MainGame.h"

using namespace std;

int main(int argc, char *argv[]) {
	MainGame maingame;
	maingame.run();

	cout << "Enter any key to quit....\n";
	int a;
	cin >> a;

	return 0;
}