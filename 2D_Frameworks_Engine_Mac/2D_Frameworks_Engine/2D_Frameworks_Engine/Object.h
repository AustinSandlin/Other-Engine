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



#include "GameObject.h"


class Object: public GameObject{
private:
     bool physicsEnable;
public:
    Object();
    ~Object();
    void update();
    void draw();
    
};
#endif /* defined(__FrameWorks__Object__) */
