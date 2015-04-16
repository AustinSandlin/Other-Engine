//#ifndef SIMMANAGER_H
//#define SIMMANAGER_H

#ifndef __SimManager__
#define __SimManager__

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#endif

#include <ctime>
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Object.h"
#include "SoundManager.h"
#include <GL/freeglut.h>


using namespace std;

class SimulationManager {
	private:
		static SimulationManager* simManager;
    
        GameObject** objects;
        int numObjects;
        Player* player;
        int numCollided;
    
		SimulationManager();

		SimulationManager(SimulationManager const&); // Don't Implement
        void operator=(SimulationManager const&); // Don't implement
        bool* keyStates = new bool[256]; // Create an array of boolean of length 256 (0-255);

	public:
		static SimulationManager& get();
		~SimulationManager();
    
        void eventLoop();
        void render();
    
        void keyPressed(unsigned char key, int x, int y);
        void keyUp(unsigned char key, int x, int y);
        void keyOperations();
        void keyboardInput(unsigned char key, int x, int y);
};

#endif