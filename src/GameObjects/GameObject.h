//
//  GameObject.h
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __FrameWorks__GameObject__
#define __FrameWorks__GameObject__

#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <iostream>
#include "../Managers/PhysicsProperties.h"
#include "GameObjectEnums.h"

struct coord{
    float x, y, z;
};

struct Tile {
	int x, y;
};

class GameObject{
    
    protected:
        coord transform;
        coord rotate;
        coord scale;
        Tile tileSize;
        bool isHUDObject;
        ObjectType objectType;
        coord velocity;
        PhysicsProperties physicsProperties;
        float frictionFactor;
        bool canJumpFlag;
        coord jumpTrans;
    
    public:
        GameObject();
        ~GameObject();
        virtual void update();
        virtual void draw();
        virtual bool collide(GameObject* obj, CollisionSide side);
    
        void setTransform(float x, float y, float z);
        void setTransform(const coord transform);
    
        void setRotate(float x, float y, float z);
    
        void setScale(float x, float y, float z);
    
        void setTileSize(int x, int y);
    
        PhysicsProperties getPhysicsProperties() { return physicsProperties; }
    
        coord getVelocity() { return velocity; }
        void setVelocity(coord temp) { velocity = temp; }
        void setVelocity(float x, float y, float z);
    
        void setFrictionFactor(float f) { frictionFactor = f; }
        float getFrictionFactor() { return frictionFactor; }
    
        coord getTransform();
        coord getRotate();
        coord getScale();
        Tile getTile() { return tileSize; }
        bool isHUD() { return isHUDObject; }
        ObjectType getObjectType() { return objectType; }
        void setCanJump(bool canJump);
        coord getJumpTrans(){return jumpTrans;}
        bool canJump() { return canJumpFlag; }
    
};

#endif /* defined(__FrameWorks__GameObject__) */
