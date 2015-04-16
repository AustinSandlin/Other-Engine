#include "PhysicsManager.h"

PhysicsManager& PhysicsManager::get() {
	static PhysicsManager instance;

    return instance;
}

PhysicsManager::PhysicsManager() {
	cout << "CONSTRUCTOR" << endl;
    playerCollision = false;
}

PhysicsManager::~PhysicsManager() {
    while (objects.size() > 0) {
        objects.pop_back();
    }
}

void PhysicsManager::registerPhysicsObject(GameObject* obj) {
    objects.push_back(obj);
}

coord PhysicsManager::requestMove(GameObject* obj) {
    coord newTransform;
    newTransform.x = obj->getTransform().x + ((Player*) obj)->getVelocity().x;
    newTransform.y = obj->getTransform().y + ((Player*) obj)->getVelocity().y;
    
    for (unsigned int i = 0; i < objects.size(); i++) {
        if (obj != objects[i]) {
            // right side
            if (newTransform.x + TILE_SIZE > objects[i]->getTransform().x
                && newTransform.x < objects[i]->getTransform().x + TILE_SIZE) {
                // collision -- prevent movement
                ((Player*) obj)->setVelocity(0, 0, 0);
               
                setPlayerCollision(true);
                return obj->getTransform();
            }
            //setPlayerCollision(false);
        }
    }
    
    return newTransform;
}

void PhysicsManager::setPlayerCollision(bool playerCol){
    playerCollision = playerCol;
}

bool PhysicsManager::getplayerCollision(){
    return playerCollision;
}