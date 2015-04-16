#ifndef __EndFlag__
#define __EndFlag__

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


class EndFlag : public GameObject{
    private:   	
		GLuint textureID;
		string texturePath;

    public:
		EndFlag(string t = "data/textures/flag.png");
		~EndFlag();
        void draw();
		void update();
		bool collide(GameObject* obj, CollisionSide side);

		string getTexturePath() { return texturePath; }    
};



#endif 