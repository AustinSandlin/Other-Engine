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
    
    engine->play2D("data/sound/sound.wav", false, false, true);
}

void SoundManager::playDeathSound(){
    engine->play2D("data/sound/death.wav", false, false, true);
}

void SoundManager::playShootingSound(){
    engine->play2D("data/sound/shooting.wav", false, false, true);
}

void SoundManager::playNoAmmoSound(){
	engine->play2D("data/sound/noammo.wav", false, false, true);
}

void SoundManager::playPlayerDeathSound(){
    engine->play2D("data/sound/playerdeath.wav", false, false, true);
}

void SoundManager::playJumpSound(){
    engine->play2D("data/sound/jump.wav", false, false, true);
}

void SoundManager::playHealthPickupSound(){
    engine->play2D("data/sound/healthpickup.wav", false, false, true);
}

void SoundManager::playScorePickupSound(){
    engine->play2D("data/sound/scorepickup.wav", false, false, true);
}

void SoundManager::playAmmoPickupSound() {
	engine->play2D("data/sound/ammopickup.wav", false, false, true);
}





