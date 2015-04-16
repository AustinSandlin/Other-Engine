#include "SimManager.h"

SimulationManager& SimulationManager::get() {
	static SimulationManager instance;

    return instance;
}

SimulationManager::SimulationManager() {
	// instantiate
	GraphicsManager::get();
	PhysicsManager::get();
	InputManager::get();
	SoundManager::get();
	EditorManager::get();

	// level things
	levelComplete = false;
	isGameOver = false;
	level = 1;
	score = 0;

	// load first level
	loadLevel("data/levels/test_level_1.xml");
}

SimulationManager::~SimulationManager() {
	cleanUpObjects();
}

void SimulationManager::cleanUpObjects() {
	while (objects.size() > 0) {
		if (objects[0] != NULL) {
			delete objects[0];
		}
		objects.erase(objects.begin());
	}
}

void SimulationManager::eventLoop() {
	float timeDelta = 1.0 / 30.0f;
	clock_t startTime, currentTime, fpsClock;
	bool gameRunning = true;

	fpsClock = clock();
	int framesCount = 0;

	while (gameRunning) {
		if (!isGameOver && !levelComplete) {
			// get start time and reset time elapsed
			startTime = clock();
			double elapsed_secs = 0.0;

			// remove objects from remove queue
			while (removeQueue.size() > 0) {
				// find in objects list
				for (unsigned int i = 0; i < objects.size(); i++) {
					if (objects[i] == removeQueue[0]) {
						objects.erase(objects.begin() + i);
					}
				}

				// delete from queue
				delete removeQueue[0];
				removeQueue.erase(removeQueue.begin());
			}

			// update objects
			if (!EditorManager::get().isEditMode()) {
				for (unsigned int i = 0; i < objects.size(); i++) {
					objects[i]->update();
				}
			}

			// redraw
			glutPostRedisplay();

			// fps counter
			framesCount++;
			double fps = (double) framesCount / (double(clock() - fpsClock) / CLOCKS_PER_SEC);
			if (fps >= 1.0) {
				framesCount = 0;
				fpsClock = clock();

				// update fps in graphics manager
				GraphicsManager::get().setFPS(fps);
			}

			do {
				// poll glut things
				glutMainLoopEvent();

				// second clock/get time elapsed
				currentTime = clock();
				elapsed_secs = double(currentTime - startTime) / CLOCKS_PER_SEC;

			} while (elapsed_secs < timeDelta);
		}
		else if (isGameOver) {
			score = 0;
			GraphicsManager::get().setScore(score);
			switch (level) {
				case 1:
					loadLevel("data/levels/test_level_1.xml");
					break;
				case 2:
					loadLevel("data/levels/test_level_2.xml");
					break;
				case 3:
					loadLevel("data/levels/test_level_3.xml");
					break;
				default:
					break;
			}
		}
		else if (levelComplete) {
			score = 0;
			GraphicsManager::get().setScore(score);
			level++;
			switch (level) {
				case 1:
					loadLevel("data/levels/test_level_1.xml");
					break;
				case 2:
					loadLevel("data/levels/test_level_2.xml");
					break;
				case 3:
					loadLevel("data/levels/test_level_3.xml");
					break;
				default:
					level = 1;
					loadLevel("data/levels/test_level_1.xml");
					break;
			}
		}
	}
}

void SimulationManager::render() {
	if (EditorManager::get().isEditMode()) {
		GraphicsManager::get().renderEditMode(objects, PhysicsManager::get().getPhysicsObjects(), 
				EditorManager::get().getEditSelection(), EditorManager::get().getInsertState(),
				EditorManager::get().getObjectToInsert());
	}
	else {
		GraphicsManager::get().renderGameMode(objects);
	}
}

void SimulationManager::keyboardInput(unsigned char key, int x, int y) {
	//We pass the key that was pressed to the input manager - the manager then
	//informs us which event that keypress is associated with.
	int event = InputManager::get().processKeyboardInput(key);
	switch (event) {
		case SOUNDEVENT:
			SoundManager::get().playSound();
			break;
		case LEFT_MOVE_EVENT:
			if (!EditorManager::get().isEditMode()) {
				player->setAccelLeft(true);
				player->setRotate(0, 0, 180);
			}
			else {
				GraphicsManager::get().setCameraTransform(GraphicsManager::get().getCameraTransform().x + 32, 0, 0);
			}
			break;
		case RIGHT_MOVE_EVENT:
			if (!EditorManager::get().isEditMode()) {
				player->setAccelRight(true);
				player->setRotate(0, 0, 0);
			}
			else {
				GraphicsManager::get().setCameraTransform(GraphicsManager::get().getCameraTransform().x - 32, 0, 0);
			}
			break;
		case JUMP_EVENT:
			if (!EditorManager::get().isEditMode()) {
				player->jump();
			}
			else {
				stateConfirmationInput();
			}
			break;
		case QUITEVENT:
			glutDestroyWindow(glutGetWindow());
			exit(0);
			break;
		case CHANGE_MODE_EVENT: {
				if (EditorManager::get().isEditMode() && EditorManager::get().getInsertState() != InsertState::READY) {
					return;
				}

				score = 0;
				GraphicsManager::get().setScore(score);

				string editLevelStr = "data/levels/test_level_";
				editLevelStr += to_string(level);
				editLevelStr += ".xml";
				cout << "edit level: " << editLevelStr << endl;

				loadLevel(editLevelStr.c_str());

				// camera
				GraphicsManager::get().setCameraTransform(0, 0, 0);

				// editor manager things
				EditorManager::get().setEditSelection(-32, -32, 0);
				EditorManager::get().setSelectedObject(-1);
				EditorManager::get().setEditMode(!EditorManager::get().isEditMode());
			}
			break;
		case DELETE_OBJECT:
			if (EditorManager::get().isEditMode() && EditorManager::get().getSelectedObject() >= 0 && EditorManager::get().getSelectedObject() < objects.size()) {
				objects.erase(objects.begin() + EditorManager::get().getSelectedObject());
				EditorManager::get().setSelectedObject(-1);
			}
			break;
		case EDIT_SET_PHYSICS:
			if (EditorManager::get().isEditMode() && EditorManager::get().getSelectedObject() != -1) {
				GameObject* obj = objects[EditorManager::get().getSelectedObject()];
				if (obj->getObjectType() == OBJECT) {
					((Object*) obj)->setPhysicsEnabled(!((Object*) obj)->isPhysicsEnabled());
				}
			}
			break;
		case EDIT_SAVE_LEVEL:
			if (EditorManager::get().isEditMode()) {
				string editLevelStr = "data/levels/test_level_";
				editLevelStr += to_string(level);
				editLevelStr += ".xml";

				EditorManager::get().saveLevel(editLevelStr.c_str(), objects);
			}
			break;
		case EDIT_INSERT_OBJECT:
			if (EditorManager::get().isEditMode() && EditorManager::get().getSelectedObject() == -1
									&& EditorManager::get().getInsertState() == InsertState::READY) {
				EditorManager::get().setInsertState(InsertState::SELECT_TYPE);
			}
			break;
		case FIRE_PROJECTILE_EVENT: {
			if (!EditorManager::get().isEditMode()) {
				float direction = 1;
				float offset = (player->getTile().x / 2);
				if (player->getRotate().z == 180) {
					direction = -1;
					offset = 0;
				}

				int x = player->getTransform().x + offset;
				int y = player->getTransform().y + 16;
				int v = 6; // velocity

				SoundManager::get().playShootingSound();
				spawnProjectile("data/textures/goomba.png", x, y, v, direction);
			} else {
				if (EditorManager::get().getInsertState() != InsertState::READY) {
					insertStateInput();
				}
			}
			break;
		}
		default:
			break;
	}
}

/*
	Takes a mouse (x, y) coordinate and uses it to find the selected object and
	set it as the "selected object" for the editor manager
*/
void SimulationManager::updateEditorSelection(int x, int y) {
	EditorManager::get().setSelectedObject(-1);
	// divide by 32 (default tile size), multiply by new tile size?
	float selectX = ((x / 32) * 32) - GraphicsManager::get().getCameraTransform().x;
	float selectY = ((SCREEN_HEIGHT - y) / 32) * 32;
	EditorManager::get().setEditSelection(selectX, selectY, 0);
	EditorManager::get().setSelectedObject(-1);
				
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->getTransform().x == selectX 
				&& objects[i]->getTransform().y == selectY) {

			EditorManager::get().setSelectedObject(i);
		}
	}
}

void SimulationManager::insertStateInput() {
	switch (EditorManager::get().getInsertState()) {
		case InsertState::SELECT_TYPE:
			switch (EditorManager::get().getObjectToInsert().typeToInsert) {
				case ObjectType::OBJECT:
					EditorManager::get().getObjectToInsert().typeToInsert = ObjectType::PLAYER;
					break;
				case ObjectType::PLAYER:
					EditorManager::get().getObjectToInsert().typeToInsert = ObjectType::ENEMY;
					break;
				case ObjectType::ENEMY:
					EditorManager::get().getObjectToInsert().typeToInsert = ObjectType::ITEM;
					break;
				case ObjectType::ITEM:
					EditorManager::get().getObjectToInsert().typeToInsert = ObjectType::FLAG;
					break;
				case ObjectType::FLAG:
					EditorManager::get().getObjectToInsert().typeToInsert = ObjectType::OBJECT;
					break;
				case ObjectType::SPAWNER:
					EditorManager::get().getObjectToInsert().typeToInsert = ObjectType::SPAWNER;
					break;
				default:
					break;
			}
			break;
		case InsertState::ENEMY_AI:
			switch (EditorManager::get().getObjectToInsert().AIPattern) {
				case AIBehaivor::HOOMER:
					EditorManager::get().getObjectToInsert().AIPattern = AIBehaivor::JUMPER;
					break;
				case AIBehaivor::JUMPER:
					EditorManager::get().getObjectToInsert().AIPattern = AIBehaivor::WANDER;
					break;
				case AIBehaivor::WANDER:
					EditorManager::get().getObjectToInsert().AIPattern = AIBehaivor::HOOMER;
					break;
				default:
					break;
			}
			break;
		case InsertState::ITEM_TYPE:
			switch (EditorManager::get().getObjectToInsert().itemType) {
				case ItemType::HEALTH_ITEM:
					EditorManager::get().getObjectToInsert().itemType = ItemType::COIN_ITEM;
					break;
				case ItemType::COIN_ITEM:
					EditorManager::get().getObjectToInsert().itemType = ItemType::HEALTH_ITEM;
					break;
				default:
					EditorManager::get().getObjectToInsert().itemType = ItemType::HEALTH_ITEM;
					break;
			}
			break;
		case InsertState::SPAWNER_ENEMY_AI:
			switch (EditorManager::get().getObjectToInsert().AIPattern) {
				case AIBehaivor::HOOMER:
					EditorManager::get().getObjectToInsert().AIPattern = AIBehaivor::JUMPER;
					break;
				case AIBehaivor::JUMPER:
					EditorManager::get().getObjectToInsert().AIPattern = AIBehaivor::WANDER;
					break;
				case AIBehaivor::WANDER:
					EditorManager::get().getObjectToInsert().AIPattern = AIBehaivor::HOOMER;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

/* Insert state "machine" -- 
	when confirming on a certain state (the switch), then progress to
	the next state */
void SimulationManager::stateConfirmationInput() {
	InsertState state = EditorManager::get().getInsertState();
	switch (state) {
		case InsertState::SELECT_TYPE:
			switch (EditorManager::get().getObjectToInsert().typeToInsert) {
				case ObjectType::PLAYER:
					EditorManager::get().setInsertState(InsertState::PLAYER_CONFIRM);
					break;
				case ObjectType::OBJECT: {
						// set next state
						EditorManager::get().setInsertState(InsertState::OBJECT_TEXTURE);

						// prompt for texture and set texture
						string texturePath = getTextureFromFilePicker();
						EditorManager::get().getObjectToInsert().texture = texturePath;

						break;
					}
				case ObjectType::ENEMY: {
						EditorManager::get().setInsertState(InsertState::ENEMY_TEXTURE);
					
						// prompt for texture and set texture
						string texturePath = getTextureFromFilePicker();
						EditorManager::get().getObjectToInsert().texture = texturePath;
					}
					break;
				case ObjectType::ITEM: {
						EditorManager::get().setInsertState(InsertState::ITEM_TEXTURE);

						// prompt for texture and set texture
						string texturePath = getTextureFromFilePicker();
						EditorManager::get().getObjectToInsert().texture = texturePath;
					}
					break;
				case ObjectType::FLAG: {
						// set next state
						EditorManager::get().setInsertState(InsertState::FLAG_TEXTURE);

						// prompt for texture and set texture
						string texturePath = getTextureFromFilePicker();
						EditorManager::get().getObjectToInsert().texture = texturePath;

						break;
					}
				case ObjectType::SPAWNER: {
						// set next state
						EditorManager::get().setInsertState(InsertState::SPAWNER_TEXTURE);

						// prompt for texture and set texture
						string texturePath = getTextureFromFilePicker();
						EditorManager::get().getObjectToInsert().texture = texturePath;

						break;
					}
				default:
					break;
			}
			break;
		case InsertState::OBJECT_TEXTURE:
			EditorManager::get().setInsertState(InsertState::OBJECT_CONFIRM);
			break;
		case InsertState::ENEMY_TEXTURE:
			EditorManager::get().setInsertState(InsertState::ENEMY_AI);
			break;
		case InsertState::ENEMY_AI:
			EditorManager::get().setInsertState(InsertState::ENEMY_CONFIRM);
			break;
		case InsertState::ITEM_TEXTURE:
			EditorManager::get().setInsertState(InsertState::ITEM_TYPE);
			break;
		case InsertState::ITEM_TYPE:
			EditorManager::get().setInsertState(InsertState::ITEM_CONFIRM);
			break;
		case InsertState::FLAG_TEXTURE:
			EditorManager::get().setInsertState(InsertState::FLAG_CONFIRM);
			break;
		case InsertState::SPAWNER_TEXTURE:
			EditorManager::get().setInsertState(InsertState::SPAWNER_INTERVAL);
			break;
		case InsertState::SPAWNER_INTERVAL:
			EditorManager::get().setInsertState(InsertState::SPAWNER_ENEMY_TEXTURE);

			// prompt for interval and set interval
			int interval = getIntervalFromConsole();
			EditorManager::get().getObjectToInsert().spawnInterval = interval;

			break;
		case InsertState::SPAWNER_ENEMY_TEXTURE:
			EditorManager::get().setInsertState(InsertState::SPAWNER_ENEMY_AI);

			// prompt for texture and set texture
			string enemyTexturePath = getTextureFromFilePicker();
			EditorManager::get().getObjectToInsert().enemyTexture = enemyTexturePath;

			break;
		case InsertState::SPAWNER_ENEMY_AI:
			EditorManager::get().setInsertState(InsertState::SPAWNER_CONFIRM);
			break;
		case InsertState::PLAYER_CONFIRM:
		case InsertState::OBJECT_CONFIRM:
		case InsertState::ENEMY_CONFIRM:
		case InsertState::ITEM_CONFIRM:
		case InsertState::FLAG_CONFIRM:
		case InsertState::SPAWNER_CONFIRM:
			EditorManager::get().setInsertState(InsertState::READY);
			break;
		default:
			break;
	}
}

string SimulationManager::getTextureFromFilePicker() {
	string texture;
	
	printf("Enter texture path (relative): ");
	cin >> texture;

	return texture;
}

int SimulationManager::getIntervalFromConsole() {
	int interval;
	
	printf("Enter spawner interval: ");
	cin >> interval;

	return interval;
}

void SimulationManager::mouseInput(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (EditorManager::get().isEditMode() && state == GLUT_UP) {
				updateEditorSelection(x, y);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (EditorManager::get().isEditMode() && EditorManager::get().getInsertState() == InsertState::READY 
						&& state == GLUT_UP) {
				updateEditorSelection(x, y);

				if (EditorManager::get().getSelectedObject() == -1) {
					EditorManager::get().insertGameObject();
				}
			}
			break;
		default:
			break;
	}
}

void SimulationManager::keyUp(unsigned char key, int x, int y){
	int event = InputManager::get().processKeyboardInput(key);
	switch (event) {
		case LEFT_MOVE_EVENT:
			player->setAccelLeft(false);
			break;
		case RIGHT_MOVE_EVENT:
			player->setAccelRight(false);
			break;
		default:
			break;

	}
}

/* object manipulation functions */
void SimulationManager::addObject(GameObject* obj, bool addPhysics) {
	objects.push_back(obj);

	if (addPhysics) {
		PhysicsManager::get().registerPhysicsObject(obj);
	}
}

void SimulationManager::removeObject(GameObject* obj) {
	for (unsigned int i = 0; i < removeQueue.size(); i++) {
		if (obj == removeQueue[i]) {
			return;
		}
	}
	removeQueue.push_back(obj);
}

void SimulationManager::spawnProjectile(string texture, int x, int y, int velocity, int direction) {
	GameObject* proj = new Projectile(texture.c_str());

	proj->setTransform(x, y, 0);
	proj->setVelocity(velocity * direction, 0, 0);
	addObject(proj, true);
}

void SimulationManager::updateHealth(int currHealth, int max){
	float healthPercent = (float) currHealth / (float) max;

	health->update(healthPercent);
}

void SimulationManager::gameOver(){
	isGameOver = true;
}

void SimulationManager::levelClear(){
	levelComplete = true;
}

void SimulationManager::increaseScore(){
	score += 50;
	GraphicsManager::get().setScore(score);
}

// level loading
void SimulationManager::loadLevel(const char* filename) {
	// clear old level
	PhysicsManager::get().resetPhysicsEngine();
	cleanUpObjects();

	XMLDocument doc;
	doc.LoadFile(filename);
	XMLElement* data = doc.FirstChildElement("data");

	// create objects
	XMLElement* gameObjects = data->FirstChildElement("objects");

	// print actual objects
	int i = 0;
	for (XMLElement* child = gameObjects ->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		switch (atoi(child->FirstChildElement("type")->GetText())) {
			case OBJECT:
				loadLevelCreateObject(child);
				break;
			case PLAYER:
				loadLevelCreatePlayer(child);
				break;
			case ENEMY:
				loadLevelCreateEnemy(child);
				break;
			case ITEM:
				loadLevelCreateItem(child);
				break;
			case ObjectType::FLAG:
				loadLevelCreateFlag(child);
				break;
			case ObjectType::SPAWNER:
				loadLevelCreateSpawner(child);
				break;
			default:
				break;
		}
	}

	// create hud objects
	XMLElement* hudObjects = data->FirstChildElement("hud");
	if (hudObjects != NULL) {
		for (XMLElement* obj = hudObjects->FirstChildElement(); obj != NULL; obj = obj->NextSiblingElement()) {
			switch (atoi(obj->FirstChildElement("type")->GetText())) {
			case HEALTH_HUD:
				SimulationManager::health = new HealthHUD();
				addObject(SimulationManager::health);
				break;
			default:
				break;
			}
		}
	}

	isGameOver = false; 
	levelComplete = false; 
}

void SimulationManager::loadLevelCreatePlayer(XMLElement* player) {
	// create player object
	XMLElement* playerLocation = player->FirstChildElement("location");
	int x = atoi(playerLocation->FirstChildElement("x")->GetText());
	int y = atoi(playerLocation->FirstChildElement("y")->GetText());
	int z = atoi(playerLocation->FirstChildElement("z")->GetText());

	// create object and add to objects list
	GameObject* playerObj = new Player();
	playerObj->setTransform(x, y, z);
	addObject(playerObj, true);
	SimulationManager::player = (Player*) playerObj;

	// add player to AI player list
	AIController::get().registerPlayer(playerObj);
}

void SimulationManager::loadLevelCreateObject(XMLElement* child) {
	// vars
	XMLElement *type, *location, *texture;
	int x, y, z;
	bool physics;

	// getting values
	type = child->FirstChildElement("type");
	location = child->FirstChildElement("location");
	x = atoi(location->FirstChildElement("x")->GetText());
	y = atoi(location->FirstChildElement("y")->GetText());
	z = atoi(location->FirstChildElement("z")->GetText());
	texture = child->FirstChildElement("texture");
	physics = atoi(child->FirstChildElement("physics")->GetText());

	// create object, set values, and add to objects
	Object* tempObj = new Object(texture->GetText(), physics);
	tempObj->setTransform(x, y, z);

	addObject(tempObj, physics);
}

void SimulationManager::loadLevelCreateEnemy(XMLElement* enemy){
    //create enemy object
    XMLElement* enemyLocation = enemy->FirstChildElement("location");
    int x = atoi(enemyLocation->FirstChildElement("x")->GetText());
    int y = atoi(enemyLocation->FirstChildElement("y")->GetText());
    int z = atoi(enemyLocation->FirstChildElement("z")->GetText());

	XMLElement* texture = enemy->FirstChildElement("texture");
	XMLElement* ai = enemy->FirstChildElement("ai");
	int aiPattern = atoi(ai->GetText());
    
    // create object and add to objects list
	GameObject* enemyObj = new Enemy(texture->GetText(), aiPattern);
    
    enemyObj->setTransform(x, y, z);
	((Enemy*)enemyObj)->setWanderMinDistance();
	((Enemy*)enemyObj)->setWanderMaxDistance();
    
    addObject(enemyObj, true);
    
}

void SimulationManager::loadLevelCreateItem(XMLElement* item) {
	// get location
    XMLElement* itemLocation = item->FirstChildElement("location");
    int x = atoi(itemLocation->FirstChildElement("x")->GetText());
    int y = atoi(itemLocation->FirstChildElement("y")->GetText());
    int z = atoi(itemLocation->FirstChildElement("z")->GetText());

	// texture
	string textureStr = item->FirstChildElement("texture")->GetText();

	// item size
	XMLElement* size = item->FirstChildElement("size");
	int w = atoi(size->FirstChildElement("w")->GetText());
	int h = atoi(size->FirstChildElement("h")->GetText());

	// item type/stat
	XMLElement* itemProps = item->FirstChildElement("item");
	ItemType itemType = static_cast<ItemType>(atoi(itemProps->FirstChildElement("type")->GetText()));
	int itemStat = atoi(itemProps->FirstChildElement("stat")->GetText());

	// create item, add to objects, and register physics
	GameObject* itemObj = new Item(w, h, textureStr.c_str(), itemStat, itemType);
	itemObj->setTransform(x, y, z);
	addObject(itemObj, true);
}

void SimulationManager::loadLevelCreateFlag(XMLElement* item) {
	// get location
    XMLElement* itemLocation = item->FirstChildElement("location");
    int x = atoi(itemLocation->FirstChildElement("x")->GetText());
    int y = atoi(itemLocation->FirstChildElement("y")->GetText());
    int z = atoi(itemLocation->FirstChildElement("z")->GetText());

	// texture
	string textureStr = item->FirstChildElement("texture")->GetText();

	// create item, add to objects, and register physics
	GameObject* flagObj = new EndFlag(textureStr);
	flagObj->setTransform(x, y, z);
	addObject(flagObj, true);
}

void SimulationManager::loadLevelCreateSpawner(XMLElement* spawner){

    XMLElement* location = spawner->FirstChildElement("location");
    int x = atoi(location->FirstChildElement("x")->GetText());
    int y = atoi(location->FirstChildElement("y")->GetText());
    int z = atoi(location->FirstChildElement("z")->GetText());
    string texture = enemy->FirstChildElement("texture")->getText();
	int interval = atoi(enemy->FirstChildElement("interval")->getText());
	string enemyTexture = enemy->FirstChildElement("enemy-texture")->getText();
	int enemyAI = atoi(enemy->FirstChildElement("enemy-ai")->GetText());
    
	Spawner* spawnerObj = new Spawner(texture, interval, enemyTexture, enemyAI);
    spawnerObj->setTransform(x, y, z);
    
    addObject(spawnerObj, true);
}

void SimulationManager::centerCameraOnPlayer(GameObject* obj) {
	coord objTransform = obj->getTransform();
	// calculate player to be center of screen
	float x = (-1 * objTransform.x) + (SCREEN_WIDTH / 2.0) - (obj->getTile().x / 2.0);
		
	// don't allow camera to show off screen (negative positional areas)
	if (x > 0) {
		x = 0;
	}

	// update camera transform in graphics manager
	GraphicsManager::get().setCameraTransform(x, 0, 0);
}