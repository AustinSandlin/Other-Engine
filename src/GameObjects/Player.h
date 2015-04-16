//
//  Player.h
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __FrameWorks__Player__
#define __FrameWorks__Player__

#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include "GameObject.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/PhysicsManager.h"

enum PlayerState {
	STANDING,
	CROUCHING,
	WALL_CLIMBING
};



class Player: public GameObject{
private:
	// texture things
	int imageH, imageW;
	GLuint textureID;

	// flags
	bool gravity;
	bool canJumpFlag;
	
	// character state
	// TODO

	// health
	int maxHealth, health;

	// animation
	double animationFrame;

	// jumping
	coord jumpTrans;

	// Motion variables
	float xVel;
	bool accelLeft;
	bool accelRight;
    
	float MAXVELRIGHT;
    float MAXVELLEFT;
public:
    Player();
    ~Player();
    void update();
    void draw();
	bool collide(GameObject* obj, CollisionSide side);

	void jump();

	int getHealth() { return health; }
	void setHealth(int h);
	int getMaxHealth() { return maxHealth; }
	void setMaxHealth(int h) { if (h > 0) maxHealth = h; }
	bool canJump() { return canJumpFlag; }
	void setAccelLeft(bool accel){accelLeft = accel;}
	void setAccelRight(bool accel){accelRight = accel;}

	void incrementAnimationFrame();
};

#endif /* defined(__FrameWorks__Player__) */
