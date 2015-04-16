//
//  SoundManager.cpp
//  2D_Frameworks_Engine
//
//  Created by Caleb Sumpter on 2/7/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include "SoundManager.h"

SoundManager& SoundManager::get() {
    static SoundManager instance;
    
    return instance;
}

SoundManager::SoundManager() {
    cout << "SOUND CONSTRUCTOR" << endl;
    engine = createIrrKlangDevice();
    if (!engine)
    {
        cout << "Could not startup engine\n";
        throw ("Could not startup engine");
    }
    
   
   
}

SoundManager::~SoundManager() {
    engine->drop(); // delete engine
    
   
}

void SoundManager::playSound() {
    engine->play2D("smb_bump.wav", false, false, true);
}

