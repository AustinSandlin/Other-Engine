//
//  AIController.cpp
//  2D_Frameworks_Engine
//
//  Created by Caleb Sumpter on 3/2/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include "AIController.h"

AIController::AIController(){
    hasArrived = false;
    minWanderDistance = 0;
    maxWanderDistance = 0;
    canMove = false;
}

AIController::~AIController(){
    resetAIController();
}

AIController& AIController::get(){
    static AIController instance;
    
    return instance;
}

void AIController::registerAIControllerObject(GameObject* obj) {
    objects.push_back(obj);
}


void AIController::registerPlayer(GameObject* obj){
    player = obj;
}
void AIController::wander(GameObject*obj, int maxWanderDistance, int minWanderDistance){
    
    if (obj->getTransform().x >= maxWanderDistance) {
        obj->setVelocity(-1 * abs(obj->getVelocity().x), obj->getVelocity().y, 0);
    }
    else if (obj->getTransform().x <= minWanderDistance) {
        obj->setVelocity(abs(obj->getVelocity().x), obj->getVelocity().y, 0);
    }
    
    PhysicsManager::get().move(obj);
    
}

void AIController::jump(GameObject* obj){
    
    if ((obj->getTransform().x - player->getTransform().x) <= 200 && (obj->getTransform().x - player->
                                                                      getTransform().x) > 0) {
        ((Enemy*)obj)->setCanMove(true);
    }
    
    // If the object is able to jump then add the jump transform to the enemy's y velocity.
    if (obj->canJump()) {
        obj->setVelocity(obj->getVelocity().x + obj->getJumpTrans().x, obj->getVelocity().y + obj->getJumpTrans().y, obj->getVelocity().z + obj->getJumpTrans().z);
        obj->setCanJump(false);
    }
    // Move the enemy object
    if (((Enemy*)obj)->canMove()) {
        PhysicsManager::get().move(obj);
    }
}


//void AIController::shoot(GameObject* obj){
//    // cout << obj->getTransform().x - player->getTransform().x;
//    // If the player is within the enemies range than start shooting projectiles.
//    if((obj->getTransform().x - player->getTransform().x ) <= 100 && (obj->getTransform().x - player->getTransform().x ) > 0){
//
//
//        // Create the projectile object shoot left: (1, -6) shoot right: (-1, velocity: 6, offset: 28)
//        float direction = 1;
//        float offset = (-1) * (obj->getTile().x / 2);
//
//        // If player is on the right side of the enemy then shoot towards that side
//        /*if (player->getRotate().z == 180) {
//         direction = -1;
//         offset = 0;
//         }*/
//
//        int x = obj->getTransform().x + offset;
//        int y = obj->getTransform().y + 10;
//        int v = -6; // velocity
//
//
//
//        SimulationManager::get().spawnProjectile("data/texutres/goomba.png", x, y, v, direction);
//
//    }
//
//}

void AIController::hoomer(GameObject *obj){
    
    if((obj->getTransform().x - player->getTransform().x ) <= 200 && (obj->getTransform().x - player->getTransform().x ) > 0 && ((player->getTransform().y == obj->getTransform().y) || (player->getTransform().y > obj->getTransform().y))){
        obj->setVelocity(-.5, obj->getVelocity().y, 0);
    }else if((obj->getTransform().x - player->getTransform().x ) >= -200 && (obj->getTransform().x - player->getTransform().x ) < 0 && ((player->getTransform().y == obj->getTransform().y) || (player->getTransform().y > obj->getTransform().y))){
        obj->setVelocity(.5, obj->getVelocity().y, 0);
    }else{
        obj->setVelocity(0, 0, 0);
    }
    PhysicsManager::get().move(obj);
    
}

void AIController::setWanderMaxDistance(GameObject* obj){
    
    maxWanderDistance = obj->getTransform().x + 20;
}

void AIController::setWanderMinDistance(GameObject* obj){
    minWanderDistance = obj->getTransform().x - 100;
}
int AIController::getWanderMaxDistance(){
    return maxWanderDistance;
}

int AIController::getWanderMinDistance(){
    return minWanderDistance;
}

void AIController::resetAIController() {
    while (objects.size() > 0) {
        objects.pop_back();
    }
}




