//
//  Player.cpp
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include "Player.h"


//Player::Player(){
//    velocity = 0.0;
//    
//    image = GraphicsManager::get().readImage("player.bmp", imageW, imageH);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageW, imageH, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//}
Player::Player(){
    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
    
    animationFrame = 0;
    
    image = GraphicsManager::get().readImage("mario.bmp", imageW, imageH);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageW, imageH, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
}

Player::~Player(){
    
}

//void Player::draw(){
//    // activate player's texture
//    
//    /*
//     - Instead of tempX, use player's X/Y
//     - Coordinates will need to be changed; right now renders the
//     top left quarter of the texture */
//    glEnable(GL_TEXTURE_2D);
//    int testTileSize = 32; // we can make this a constant
//    glBegin(GL_QUADS);
//    glTexCoord2f(0, 1);
//    glVertex2f(transform.x + 0, transform.y + testTileSize);
//    glTexCoord2f(1, 1);
//    glVertex2f(transform.x + testTileSize, transform.y + testTileSize);
//    glTexCoord2f(1, 0);
//    glVertex2f(transform.x + testTileSize, transform.y + 0);
//    glTexCoord2f(0, 0);
//    glVertex2f(transform.x + 0, transform.y + 0);
//    glEnd();
//    glDisable(GL_TEXTURE_2D);
//}
//
//void Player::update(){
//    // stub
//}

void Player::draw(){
    // activate player's texture
    
    /*
     - Instead of tempX, use player's X/Y
     - Coordinates will need to be changed; right now renders the
     top left quarter of the texture */
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0 + (0.25 * (int) animationFrame), 1);
    glVertex2f(transform.x + 0, transform.y + TILE_SIZE);
    glTexCoord2f(0.25 + (0.25 * (int) animationFrame), 1);
    glVertex2f(transform.x + TILE_SIZE, transform.y + TILE_SIZE);
    glTexCoord2f(0.25 + (0.25 * (int) animationFrame), 0);
    glVertex2f(transform.x + TILE_SIZE, transform.y + 0);
    glTexCoord2f(0 + (0.25 * (int) animationFrame), 0);
    glVertex2f(transform.x + 0, transform.y + 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Player::update() {

    coord temp = PhysicsManager::get().requestMove(this);
    setTransform(temp.x, temp.y, temp.z);
    
    if (velocity.x > 0) {
        incrementAnimationFrame();
    }
}

void Player::setVelocity(float x, float y, float z) {

    velocity.x = x;
    velocity.y = y;
    velocity.z = y;
}

void Player::incrementAnimationFrame() {
    animationFrame += 0.25;
    
    if (animationFrame >= 4.0) {
        animationFrame = 0.0;
    }
}
