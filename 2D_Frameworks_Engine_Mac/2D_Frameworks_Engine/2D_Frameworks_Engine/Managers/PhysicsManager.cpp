#include "PhysicsManager.h"

PhysicsManager& PhysicsManager::get() {
    static PhysicsManager instance;
    
    return instance;
}

PhysicsManager::PhysicsManager() {
    playerCollision = false;
}

PhysicsManager::~PhysicsManager() {
    resetPhysicsEngine();
}

void PhysicsManager::registerPhysicsObject(GameObject* obj) {
    objects.push_back(obj);
}

bool PhysicsManager::checkCollisionFilters(GameObject* obj, GameObject* col) {
    return (obj->getPhysicsProperties().maskBits & col->getPhysicsProperties().categoryBits
            && obj->getPhysicsProperties().categoryBits & col->getPhysicsProperties().maskBits);
}

void PhysicsManager::move(GameObject* obj) {
    Tile objTile = obj->getTile();
    coord newTransform = obj->getTransform();
    
    // test X
    newTransform.x = obj->getTransform().x + obj->getVelocity().x;
    for (unsigned int i = 0; i < objects.size(); i++) {
        // make sure object hasn't been removed from game
        if (!objects[i]) {
            objects.erase(objects.begin() + i);
            i--;
        }
        else if (obj != objects[i]) {
            if (checkCollisionFilters(obj, objects[i])
                && newTransform.x + objTile.x > objects[i]->getTransform().x && newTransform.x < objects[i]->getTransform().x + objects[i]->getTile().x
                && newTransform.y + objTile.y > objects[i]->getTransform().y && newTransform.y < objects[i]->getTransform().y + objects[i]->getTile().y) {
                
                // set collision side
                CollisionSide sideA = CollisionSide::LEFT;
                CollisionSide sideB = CollisionSide::RIGHT;
                if (obj->getVelocity().x < 0) {
                    sideA = CollisionSide::RIGHT;
                    sideB = CollisionSide::LEFT;
                }
                
                if (objects[i]->collide(obj, sideA) &&
                    obj->collide(objects[i], sideB)) {
                    // don't allow object to move
                    newTransform.x = (int) obj->getTransform().x;
                }
                
                //setPlayerCollision(true);
            }
        }
    }
    
    // test Y
    newTransform.y = obj->getTransform().y + obj->getVelocity().y;
    for (unsigned int i = 0; i < objects.size(); i++) {
        // make sure object hasn't been removed from game
        if (!objects[i]) {
            objects.erase(objects.begin() + i);
            i--;
        }
        
        if (obj != objects[i]) {
            if (checkCollisionFilters(obj, objects[i])
                && newTransform.x + objTile.x > objects[i]->getTransform().x && newTransform.x < objects[i]->getTransform().x + objects[i]->getTile().x
                && newTransform.y + objTile.y > objects[i]->getTransform().y && newTransform.y < objects[i]->getTransform().y + objects[i]->getTile().y) {
                
                CollisionSide sideA = CollisionSide::TOP;
                CollisionSide sideB = CollisionSide::BOTTOM;
                if (obj->getVelocity().y > 0) {
                    sideA = CollisionSide::BOTTOM;
                    sideB = CollisionSide::TOP;
                }
                
                // don't allow object to move
                newTransform.y = (int) obj->getTransform().y;
                
                if (objects[i]->collide(obj, sideA)) {
                    //SimulationManager::get().removeObject(objects[i]);
                }
                if (obj->collide(objects[i], sideB)) {
                    //SimulationManager::get().removeObject(objects[i]);
                }
            }
        }
    }
    
    obj->setTransform(newTransform);
    
    // if player object, update camera
    if (typeid(*obj) == typeid(Player)) {
        SimulationManager::get().centerCameraOnPlayer(obj);
    }
}

void PhysicsManager::destroyObject(GameObject* obj) {
    SimulationManager::get().removeObject(obj);
}

void PhysicsManager::setPlayerCollision(bool playerCol){
    playerCollision = playerCol;
}

bool PhysicsManager::getplayerCollision(){
    return playerCollision;
}

void PhysicsManager::resetPhysicsEngine() {
    while (objects.size() > 0) {
        objects.pop_back();
    }
}