//#ifndef PHYSICSMANAGER_H
//#define PHYSICSMANAGER_H

#ifndef __PhysicsManager__
#define __PhysicsManager__

#include <iostream>
#include <vector>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

#include "GameObject.h"
#include "Player.h"
using namespace std;

class PhysicsManager {
	private:
		static PhysicsManager* physicsManager;
		PhysicsManager();

		PhysicsManager(PhysicsManager const&); // Don't Implement
        void operator=(PhysicsManager const&); // Don't implement
    
        vector<GameObject*> objects;
    
        bool playerCollision;

	public:
		static PhysicsManager& get();
		~PhysicsManager();
    
        void setPlayerCollision(bool playerCollision);
    bool getplayerCollision();

    // physics functions
    void registerPhysicsObject(GameObject*);
    coord requestMove(GameObject* obj);
};

#endif