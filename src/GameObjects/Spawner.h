#ifndef __SPAWNER__
#define __SPAWNER__

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

#include "GameObject.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/PhysicsManager.h"


class Spawner : public GameObject {
    private:
		GLuint textureID;
		string texturePath;
		string enemyTexturePath;
		int enemyAIBehavior;
		int spawnTimer;
		int spawnInterval;
		bool enabled;

    public:
		Spawner(string path, int interval, string texture, int ai);
		~Spawner();
        void draw();
		void update();
		bool collide(GameObject* obj, CollisionSide side);

		string getTexturePath() { return texturePath; }
		int getSpawnInterval() { return spawnInterval; }
		string getEnemyTexturePath() { return enemyTexturePath; }
		int getEnemyAIBehaivor() { return enemyAIBehavior; }
};



#endif 