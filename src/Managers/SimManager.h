#ifndef SIMMANAGER_H
#define SIMMANAGER_H

#pragma warning (disable : 4244 ) // ignore "conversion from double to float"/loss of precision warnings
#pragma warning (disable : 4305 )
#pragma warning (disable : 4018 )

#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <vector>
#include <algorithm>
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "EditorManager.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Object.h"
#include "../GameObjects/HealthHUD.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/EndFlag.h"
#include "../GameObjects/Items/Item.h"
#include "../tinyxml2/tinyxml2.h"


using namespace tinyxml2;
using namespace std;

class Player;

class SimulationManager {
	private:
		static SimulationManager* simManager;

		// variables
		vector<GameObject*> objects;
		HealthHUD* health;
		Player* player;
		vector<GameObject*> removeQueue;
		bool levelComplete;
		bool isGameOver;
		int level;
		int score;
		int ammo;
		//bool gameRunning;

		// helper functions
		void updateEditorSelection(int x, int y);
		void insertStateInput();
		void stateConfirmationInput();
		string getTextureFromFilePicker();

		// constructor
		SimulationManager();

		SimulationManager(SimulationManager const&); // Don't Implement
        void operator=(SimulationManager const&); // Don't implement

		// helper functions
		void cleanUpObjects();

	public:
		static SimulationManager& get();
		~SimulationManager();

		// openGL-ish things
		void eventLoop();
		void render();
		void keyboardInput(unsigned char key, int x, int y);
		void keyUp(unsigned char key, int x, int y);
		void mouseInput(int button, int state, int x, int y);

		// object manipulation
		void addObject(GameObject* obj, bool addPhysics = false);
		void removeObject(GameObject* obj);
		void spawnProjectile(string texture, int x, int y, int velocity, int direction);
		void updateHealth(int health, int max);
		void increaseScore();
		void increaseAmmo();

		// load level functions
		void gameOver();
		void levelClear();
		void loadLevel(const char* filename);
		void loadLevelCreateObject(XMLElement* child);
		void loadLevelCreatePlayer(XMLElement* child);
		void loadLevelCreateEnemy(XMLElement* child);
		void loadLevelCreateItem(XMLElement* child);
		void loadLevelCreateFlag(XMLElement* child);

		void centerCameraOnPlayer(GameObject* obj);
};

#endif