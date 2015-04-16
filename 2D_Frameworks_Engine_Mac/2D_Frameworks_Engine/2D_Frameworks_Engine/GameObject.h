//
//  GameObject.h
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __GameObject__
#define __GameObject__

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>
#else
#include <GL/freeglut.h>
#endif



struct coord{
    float x, y, z;
};

const int TILE_SIZE = 32;

class GameObject{
    
    protected:
    coord transform;
    coord rotate;
    coord scale;
    
    public:
    GameObject();
    ~GameObject();
    virtual void update();
    virtual void draw();
    
    void setTransform(float x, float y, float z);
    
    void setRotate(float x, float y, float z);
    
    void setScale(float x, float y, float z);
    
    coord getTransform();
    coord getRotate();
    coord getScale();
    
};

#endif /* defined(__FrameWorks__GameObject__) */
