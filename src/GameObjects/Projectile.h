//
//  Projectile.h
//  FrameWorks
//
//  Created by Tanner Taylor on 3/19/15.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../GameObjects/GameObject.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/PhysicsManager.h"

using namespace std;

class Projectile : public GameObject {
	private:
		string texturePath;
		GLuint textureID;
		int timeToLive;

	public:
	   Projectile(const char* filename);

		~Projectile();

		// polymorphic functions
		void update();
		void draw();
		bool collide(GameObject* obj, CollisionSide side);

		string getTexturePath() { return texturePath; }
};

#endif