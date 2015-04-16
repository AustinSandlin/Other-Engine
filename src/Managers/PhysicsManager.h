#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <iostream>
#include <vector>
#include "../GameObjects/GameObject.h"
#include "../GameObjects//Player.h"
#include "../GameObjects//Projectile.h"
#include "SimManager.h"

using namespace std;

class PhysicsManager {
	private:
		static PhysicsManager* physicsManager;
		PhysicsManager();

		PhysicsManager(PhysicsManager const&); // Don't Implement
        void operator=(PhysicsManager const&); // Don't implement

		// variables
		vector<GameObject*> objects;
		bool playerCollision;
		bool checkCollisionFilters(GameObject* obj, GameObject* col);

	public:
		static PhysicsManager& get();
		~PhysicsManager();

		void setPlayerCollision(bool playerCollision);
		bool getplayerCollision();

		// physics functions
		void registerPhysicsObject(GameObject*);
		vector<GameObject*> getPhysicsObjects() { return objects; }
		void move(GameObject* obj);

		void destroyObject(GameObject* obj);

		void resetPhysicsEngine();
};

#endif