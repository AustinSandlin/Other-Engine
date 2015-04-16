#ifndef InputManager_H
#define InputManager_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include "../GameObjects/GameObject.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#define NOEVENT    0
#define SOUNDEVENT 1
#define MOVEEVENT  2
#define QUITEVENT  3
#define CHANGE_MODE_EVENT 4
#define DELETE_OBJECT 5
#define EDIT_SET_PHYSICS 6
#define EDIT_SAVE_LEVEL 7
#define EDIT_INSERT_OBJECT 8
#define JUMP_EVENT 9
#define LEFT_MOVE_EVENT 10
#define RIGHT_MOVE_EVENT 11
#define FIRE_PROJECTILE_EVENT 12

using namespace std;

class InputManager {
	private:
		static InputManager* inputManager;
		map<char,int> keyMap;
		InputManager();

		InputManager(InputManager const&); // Don't Implement
        void operator=(InputManager const&); // Don't implement

	public:
		static InputManager& get();
		~InputManager();

		int processKeyboardInput(unsigned char key);
};

#endif