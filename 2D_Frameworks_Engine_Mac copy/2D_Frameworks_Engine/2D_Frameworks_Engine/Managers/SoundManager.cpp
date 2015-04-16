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
    
    engine->play2D("data/sound/smb_bump.wav", false, false, true);
}

void SoundManager::playDeathSound(){
    engine->play2D("data/sound/enemyDeath.wav", false, false, true);
}

void SoundManager::playShootingSound(){
    engine->play2D("data/sound/projectile.wav", false, false, true);
}

void SoundManager::playPlayerDeathSound(){
    engine->play2D("data/sound/MM2Death.wav", false, false, true);
}

void SoundManager::playJumpSound(){
    engine->play2D("data/sound/playerJump.wav", false, false, true);
}

void SoundManager::playHealthPickupSound(){
    engine->play2D("data/sound/healthPickup.wav", false, false, true);
}

void SoundManager::playItemPickupSound(){
    engine->play2D("data/sound/item.wav", false, false, true);
}



