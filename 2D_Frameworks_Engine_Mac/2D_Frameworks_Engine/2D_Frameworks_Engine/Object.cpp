//
//  Object.cpp
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include "Object.h"


Object::Object(){
    
}

Object::~Object(){
    
}

void Object::update(){
    
}

void Object::draw(){
    glDisable(GL_TEXTURE_2D);
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(transform.x + 0, transform.y + TILE_SIZE);
    glVertex2f(transform.x + TILE_SIZE, transform.y + TILE_SIZE);
    glVertex2f(transform.x + TILE_SIZE, transform.y + 0);
    glVertex2f(transform.x + 0, transform.y + 0);
    glEnd();
}