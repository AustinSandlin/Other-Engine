//
//  Player.cpp
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include "Player.h"

Player::Player(){
    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
    
    jumpTrans.x = 0;
    jumpTrans.y = 0;
    jumpTrans.z = 0;
    
    objectType = ObjectType::PLAYER;
    
    setTileSize(32, 64);
    
    animationFrame = 0;
    
    physicsProperties.categoryBits = PhysicsCategory::P_CAT_PLAYER;
    physicsProperties.maskBits = PhysicsMask::P_MASK_PLAYER;
    
    gravity = true;
    canJumpFlag = false;
    
    // load image
    textureID = GraphicsManager::get().loadImageFromTexture("data/textures/ss2_gohan_dir.png");
    
    // default health
    maxHealth = 12;
    health = maxHealth;
    
    MAXVELLEFT = -3.5;
    MAXVELRIGHT = 3.5;
    xVel = 0;
    accelLeft  = false;
    accelRight = false;
}

Player::~Player(){
    
}

void Player::draw(){
    // activate player's texture
    
    /*
     - Instead of tempX, use player's X/Y
     - Coordinates will need to be changed; right now renders the
     top left quarter of the texture */
    
    // enable textures and set texture and color
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1, 1, 1);
    
    // push current matrix and translate position
    glPushMatrix();
    glTranslated(transform.x, transform.y, 0);
    
    // draw player
    float yClip = 0.5 - (getRotate().z / 360.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0 + (0.25 * (int) animationFrame), yClip + 0.5);
    glVertex2f(0, tileSize.y);
    glTexCoord2f(0.25 + (0.25 * (int) animationFrame), yClip + 0.5);
    glVertex2f(tileSize.x, tileSize.y);
    glTexCoord2f(0.25 + (0.25 * (int) animationFrame), yClip);
    glVertex2f(tileSize.x, 0);
    glTexCoord2f(0 + (0.25 * (int) animationFrame), yClip);
    glVertex2f(0, 0);
    glEnd();
    
    // pop matrix and disable texture
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Player::update() {
    canJumpFlag = false;
    if (gravity && velocity.y > -3) {
        velocity.y -= 0.2 * frictionFactor;
    }
    
    if(accelLeft && xVel > MAXVELLEFT){
        xVel -= 0.4;
    }
    else if(accelRight && xVel < MAXVELRIGHT){
        cout << "right" << endl;
        xVel += 0.4;
    }
    
    if(!accelLeft && !accelRight){
        if(xVel > 0){
            if(xVel > 0.5){
                xVel -= 0.5;
            }
            else{
                xVel = 0;
            }
        }
        if(xVel < 0){
            if(xVel < -0.5){
                xVel += 0.5;
            }
            else{
                xVel = 0;
            }
        }
    }
    
    if(xVel < MAXVELLEFT){
        xVel = MAXVELLEFT;
    }
    if(xVel > MAXVELRIGHT){
        xVel = MAXVELRIGHT;
    }
    
    velocity.x = xVel;
  
    
    PhysicsManager::get().move(this);
    
    if (velocity.x != 0) {
        incrementAnimationFrame();
    }
    
    if (getTransform().y < -100) {
        SoundManager::get().playDeathSound();
        SimulationManager::get().gameOver();
    }
}

void Player::incrementAnimationFrame() {
    animationFrame += 0.25;
    
    if (animationFrame >= 4.0) {
        animationFrame = 0.0;
    }
}

bool Player::collide(GameObject* obj, CollisionSide side) {
    // enemy
    if (obj->getObjectType() == ObjectType::ENEMY
        && (side == CollisionSide::LEFT || side == CollisionSide::RIGHT)) {
        setHealth(getHealth() - 1);
        
        //Also need to notify HUD of change in health.
        SoundManager::get().playSound();
        if (getHealth() <= 0) {
            SimulationManager::get().gameOver();
        }
    }
    
    // object
    if (obj->getObjectType() == ObjectType::OBJECT) {
        switch (side) {
            case CollisionSide::RIGHT:
            case CollisionSide::LEFT:
                if (getVelocity().y < 0) {
                    xVel = 0;
                    //velocity.x = xVel;
                    setVelocity(0, -2.4, getVelocity().z);
                    canJumpFlag = true;
                    
                    // set jump transform
                    jumpTrans.x = MAXVELRIGHT;
                    jumpTrans.y = 6.5;
                    
                    if (side == CollisionSide::RIGHT) {
                        jumpTrans.x = MAXVELLEFT;
                    }
                }
                break;
            case CollisionSide::TOP:
                SoundManager::get().playSound();
                break;
            case CollisionSide::BOTTOM:
                canJumpFlag = true;
                jumpTrans.x = 0;
                jumpTrans.y = 7;
                jumpTrans.z = 0;
            default:
                break;
        }
    }
    
    return true;
}

// jump function
void Player::jump() {
    if (canJump()) {
        SoundManager::get().playJumpSound();
        setVelocity(getVelocity().x + jumpTrans.x, getVelocity().y + jumpTrans.y, getVelocity().z + jumpTrans.z);
        canJumpFlag = false;
    }
}

void Player::setHealth(int h) { 
    if (h >= 0 && h <= maxHealth) { 
        health = h; 
        SimulationManager::get().updateHealth(getHealth(), getMaxHealth()); 
    }
}