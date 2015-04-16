/*
*  Filename: main.cpp
*  Author:   Tanner Taylor
*  Created:  DATE
*  Due:      DATE
*/

#include <iostream>
#include <fstream>
#include <string>

#include "Managers\SimManager.h"

using namespace std;

void render() {
	SimulationManager::get().render();
}

void mouseInput(int button, int state, int x, int y) {
	SimulationManager::get().mouseInput(button, state, x, y);
}

void keyboardInput(unsigned char key, int x, int y) {
	SimulationManager::get().keyboardInput(key, x, y);
}

void keyUp(unsigned char key, int x, int y) {
	SimulationManager::get().keyUp(key, x, y);
}

int main(int argc, char* args[]) {
	// Init glut and make a window.
	glutInit(&argc, args);

	// instantiate managers
	SimulationManager::get();

	// callback functions and init
	glutMouseFunc(mouseInput);
	glutKeyboardFunc(keyboardInput);
	glutKeyboardUpFunc(keyUp);
	glutDisplayFunc(render);

	// loop
	SimulationManager::get().eventLoop();

	return 0;
}