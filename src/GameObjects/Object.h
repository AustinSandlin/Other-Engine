//
//  Object.h
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#ifndef __FrameWorks__Object__
#define __FrameWorks__Object__

#include <string>
#include <stdlib.h>

#include <stdio.h>
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
	   Object(const char* filename, bool physics, int width, int height);

		~Object();
		void update();
		void draw();

		bool isPhysicsEnabled() { return physicsEnable; }
		void setPhysicsEnabled(bool enable) { physicsEnable = enable; }
		string getTexturePath() { return texturePath; }
		bool collide(GameObject* obj, CollisionSide side);
};

#endif /* defined(__FrameWorks__Object__) */
