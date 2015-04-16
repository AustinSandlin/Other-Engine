//
//  SoundManager.h
//  2D_Frameworks_Engine
//
//  Created by Caleb Sumpter on 2/7/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __SoundManager__
#define __SoundManager__

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif
#include <irrKlang.h>



using namespace std;
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class SoundManager {
private:
    static SoundManager* soundManager;
    SoundManager();
    
    SoundManager(SoundManager const&); // Don't Implement
    void operator=(SoundManager const&); // Don't implement
    
    // start the sound engine with default parameters
    ISoundEngine* engine;
    
public:
    static SoundManager& get();
    ~SoundManager();
    
    // sound functions
    void playSound();
    void playDeathSound();
    void playShootingSound();
    void playPlayerDeathSound();
    void playJumpSound();
    void playHealthPickupSound();
    void playItemPickupSound();
};


#endif /* defined(__SoundManager__) */
