//#ifndef GRAPHICSMANAGER_H
//#define GRAPHICSMANAGER_H

#ifndef __GraphicsManager__
#define __GraphicsManager__


#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

#include "GameObject.h"
#include <fstream>
using namespace std;

// screen constants
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

class GraphicsManager {
	private:
		static GraphicsManager* physicsManager;
		GraphicsManager();

		GraphicsManager(GraphicsManager const&); // Don't Implement
        void operator=(GraphicsManager const&); // Don't implement
    
        float tempX;

	public:
		static GraphicsManager& get();
		~GraphicsManager();

		// main functions
		void setOrthoView();
		void render(GameObject**, int);
		void init();
    
        GLubyte *readImage( const char *filename, int &width, int &height);
};

#endif