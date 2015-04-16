//
//  Enemy.h
//  2D_Frameworks_Engine
//
//  Created by Caleb Sumpter on 2/27/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __Enemy__
#define __Enemy__

#include <iostream>
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

#include "GameObject.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/PhysicsManager.h"
#include "AIController.h"


class Enemy: public GameObject{
private:
    int imageH, imageW;
    GLubyte *image;
    
    bool gravity;
    GLuint textureID;
    string texturePath;
    
    // health for enemy
    int maxHealth, health;
    
    double animationFrame;
    
    int aiBehaivor;
    int minWanderDistance, maxWanderDistance;
    bool canMoveFlag;
    
public:
    Enemy(string texture = "data/textures/zombie.png", int ai = 2);
    ~Enemy();
    
    void update();
    void draw();
    bool collide(GameObject* obj, CollisionSide side);
    
    void incrementAnimationFrame();
    coord getVelocity(){ return velocity;}
    void setVelocity(coord temp) { velocity = temp; }
    void setVelocity(float x, float y, float z);
    string getTexturePath() { return texturePath; }
    void setAIBehaivor(int aiType) { aiBehaivor = aiType;}
    int getAIBehaivor(){ return aiBehaivor;}
    
    int getHealth();
    void setHealth(int h);
    int getMaxHealth() { return maxHealth; }
    void setMaxHealth(int h) { if (h > 0) maxHealth = h; }
    
    void setWanderMaxDistance();
    void setWanderMinDistance();
    int getWanderMaxDistance();
    int getWanderMinDistance();
    bool canMove() {return canMoveFlag;}
    void setCanMove(bool move) { canMoveFlag = move;}
    
    
};



#endif