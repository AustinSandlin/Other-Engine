//
//  AIController.h
//  2D_Frameworks_Engine
//
//  Created by Caleb Sumpter on 3/2/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __AIController__
#define __AIController__

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#endif
#include <GL/freeglut.h>

#include "GameObject.h"
#include "Enemy.h"
#include "GameObjectEnums.h"

using namespace std;

class  AIController{
    
private:
    AIController();
    static AIController* aiController;
    
    AIController(AIController const&);
    void operator=(AIController const&);
    
    vector<GameObject*> objects;
    int minWanderDistance;
    int maxWanderDistance;
    AIBehaivor aiBehaivor;
    GameObject* player;
    bool canMove;
    
public:
    void wander(GameObject* obj, int maxWanderDistance, int minWanderDistance);
    void jump(GameObject* obj);
    //void shoot(GameObject* obj);
    void hoomer(GameObject* obj);
    void setWanderMaxDistance(GameObject* obj);
    void setWanderMinDistance(GameObject* obj);
    int getWanderMaxDistance();
    int getWanderMinDistance();
    static AIController& get();
    void registerAIControllerObject();
    void resetAIController();
    void registerAIControllerObject(GameObject* obj);
    void registerPlayer(GameObject* obj);
    ~AIController();
    bool hasArrived;
    AIBehaivor getAIType() { return aiBehaivor; }
    
    
};


#endif
