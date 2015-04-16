#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#pragma warning (disable : 4244 ) // ignore "conversion from double to float"/loss of precision warnings

#include <SOIL.h>
#ifdef __APPLE__
	#include <OpenGL/OpenGL.h>
	#include <GLUT/glut.h>
#else
	#include <GL/freeglut.h>
#endif

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <map>
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Object.h"
#include "EditorStates.h"

using namespace std;

// screen constants
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

class GraphicsManager {
	private:
		coord cameraTransform;
		double fps;
		int score;

		static GraphicsManager* graphicsManager;
		GraphicsManager();

		GraphicsManager(GraphicsManager const&); // Don't Implement
        void operator=(GraphicsManager const&); // Don't implement

		vector<GLuint> loadedTextures;
		map<string, GLuint> loadedTexturesMap;

	public:
		static GraphicsManager& get();
		~GraphicsManager();

		// helper draw functions
		void drawText(string str, int x, int y);
		void drawDouble(double d, int x, int y);
		void drawInt(int in, int x, int y);
		void drawSquareAbsolute(int w, int h, int x, int y);
		void drawSquareRelative(int w, int h, int x, int y);

		// main functions
		void setOrthoView();
		void renderGameMode(vector<GameObject*>);
		void renderEditMode(vector<GameObject*>, vector<GameObject*> physicsObjects, 
							coord editSelection, InsertState state, ObjectInsertion& objToInsert);

		// draw prompts/insert states
		void drawObjectTypeSelection(ObjectInsertion& objToInsert, double r, double g, double b);
		void drawSelectTexture(ObjectInsertion& objToInsert, double r, double g, double b, double x, double y);
		void drawSelectAIPattern(ObjectInsertion& objToInsert, double r, double g, double b, double x, double y);
		void drawSelectItemType(ObjectInsertion& objToInsert, double r, double g, double b, double x, double y);
		void drawSelectionConfirm(ObjectInsertion& objToInsert, double x, double y);

		void init();
		GLuint loadImageFromTexture(const char* filename, const char* loadPath = '\0');

		void setFPS(double f) { fps = f; }
		void setScore(int s) {score = s;}
		coord getCameraTransform() { return cameraTransform; }
		void setCameraTransform(float x, float y, float z);
};

#endif