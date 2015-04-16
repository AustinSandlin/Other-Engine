//
//  Player.h
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __FrameWorks__Player__
#define __FrameWorks__Player__

#include <Iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

#include "GameObject.h"
#include "GraphicsManager.h"
#include "PhysicsManager.h"


class Player: public GameObject{
private:
    //float velocity;
    coord velocity;
   	
    int imageH, imageW;
    GLubyte *image;
    
   double animationFrame;
    
public:
     Player();
    ~Player();
    
    void jump();
    void update();
    void draw();
    
    coord getVelocity() { return velocity; }
    void setVelocity(coord temp) { velocity = temp; }
    void setVelocity(float x, float y, float z);
    
    void incrementAnimationFrame();
        
};

#endif /* defined(__FrameWorks__Player__) */
