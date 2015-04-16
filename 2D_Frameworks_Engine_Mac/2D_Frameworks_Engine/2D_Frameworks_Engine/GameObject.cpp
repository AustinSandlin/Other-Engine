//
//  GameObject.cpp
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include "GameObject.h"


GameObject::GameObject(){
    
    transform.x = 0.0;
    transform.y = 0.0;
    transform.z = 0.0;
    
    rotate.x = 0.0;
    rotate.y = 0.0;
    rotate.z = 0.0;
    
    scale.x = 0.0;
    scale.y = 0.0;
    scale.z = 0.0;
    
}

GameObject::~GameObject(){
    //Stub
}

void GameObject::setTransform(float x, float y, float z){
    transform.x = x;
    transform.y = y;
    transform.z = y;
}

void GameObject::setRotate(float x, float y, float z){
    rotate.x = x;
    rotate.y = y;
    rotate.z = y;
}

void GameObject::setScale(float x, float y, float z){
    scale.x = x;
    scale.y = y;
    scale.z = y;
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

void GameObject::update() {
    // objects should define their own
}

void GameObject::draw() {}


