//
//  Object.h
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __Object__
#define __Object__

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif


#include <stdio.h>
#include <string>
#include "GameObject.h"
#include "../Managers/GraphicsManager.h"

using namespace std;

class Object: public GameObject{
private:
    bool physicsEnable;
    string texturePath;
    GLuint textureID;
    
public:
	   Object();
	   Object(const char* filename, bool physics);
	   Object(const char* filename, bool physics, const char* loadTexturePath);
    
    ~Object();
    void update();
    void draw();
    
    bool isPhysicsEnabled() { return physicsEnable; }
    void setPhysicsEnabled(bool enable) { physicsEnable = enable; }
    string getTexturePath() { return texturePath; }
    bool collide(GameObject* obj, CollisionSide side);
};

#endif /* defined(__FrameWorks__Object__) */
