//
//  GameObject.cpp
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include "GameObject.h"


GameObject::GameObject(){
    isHUDObject = false;
    
    transform.x = 0.0;
    transform.y = 0.0;
    transform.z = 0.0;
    
    rotate.x = 0.0;
    rotate.y = 0.0;
    rotate.z = 0.0;
    
    scale.x = 0.0;
    scale.y = 0.0;
    scale.z = 0.0;
    
    frictionFactor = 1.0;
    
    jumpTrans.x = 0;
    jumpTrans.y = 7;
    jumpTrans.z = 0;
    canJumpFlag = true;
    
}

GameObject::~GameObject(){
    //Stub
}

void GameObject::setTransform(float x, float y, float z){
    transform.x = x;
    transform.y = y;
    transform.z = z;
}

void GameObject::setTransform(const coord transform) {
    this->transform = transform;
}

void GameObject::setRotate(float x, float y, float z){
    rotate.x = x;
    rotate.y = y;
    rotate.z = z;
}

void GameObject::setScale(float x, float y, float z){
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

void GameObject::setTileSize(int x, int y) {
    tileSize.x = x;
    tileSize.y = y;
}

coord GameObject::getTransform(){
    return transform;
}

coord GameObject::getRotate(){
    return rotate;
}

coord GameObject::getScale(){
    return scale;
}

void GameObject::setVelocity(float x, float y, float z) {
    velocity.x = x;
    velocity.y = y;
    velocity.z = y;
}

void GameObject::update() {
    // objects should define their own
}

void GameObject::draw() {}
bool GameObject::collide(GameObject* obj, CollisionSide side) { return true; }

void GameObject::setCanJump(bool canJump){
    canJumpFlag = canJump;
    
}


