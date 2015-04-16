#include "EditorManager.h"

EditorManager& EditorManager::get() {
	static EditorManager instance;

    return instance;
}

EditorManager::EditorManager() {
	setEditMode(false);

	// set default selection things to null
	setSelectedObject(-1);
	setEditSelection(-32, -32, 0);

	// set default insertion
	objectToInsert.typeToInsert = ObjectType::OBJECT;
	objectToInsert.itemType = ItemType::HEALTH_ITEM;
	objectToInsert.AIPattern = AIBehaivor::WANDER;
	objectToInsert.texture = "data/textures/tile_block.png";

	// state
	insertState = InsertState::READY;
}

EditorManager::~EditorManager(){
	
}

// helper function
XMLElement* EditorManager::createLocationElement(GameObject* obj, XMLElement* objElement, XMLDocument& doc) {
	XMLElement* location = doc.NewElement("location");
	XMLElement* x = doc.NewElement("x");
	XMLElement* y = doc.NewElement("y");
	XMLElement* z = doc.NewElement("z");

	// get location values
	string xValue = to_string((int) obj->getTransform().x);
	string yValue = to_string((int) obj->getTransform().y);
	string zValue = to_string((int) obj->getTransform().z);

	// set location values
	x->LinkEndChild(doc.NewText(xValue.c_str()));
	y->LinkEndChild(doc.NewText(yValue.c_str()));
	z->LinkEndChild(doc.NewText(zValue.c_str()));

	// link values to location
	location->LinkEndChild(x);
	location->LinkEndChild(y);
	location->LinkEndChild(z);

	return location;
}

XMLElement* EditorManager::createTileSizeElement(GameObject* obj, XMLElement* objElement, XMLDocument& doc) {
	XMLElement* size = doc.NewElement("size");
	XMLElement* width = doc.NewElement("w");
	XMLElement* height = doc.NewElement("h");

	// get string values of tile width/height
	string tileSizeW = to_string((int) obj->getTile().x);
	string tileSizeH = to_string((int) obj->getTile().y);

	// create and set values
	width->LinkEndChild(doc.NewText(tileSizeW.c_str()));
	height->LinkEndChild(doc.NewText(tileSizeH.c_str()));

	// link size values
	size->LinkEndChild(width);
	size->LinkEndChild(height);

	return size;
}

// render editor menus
void EditorManager::renderEditor() {
	// draw edit square
	glColor4f(0.3, 0.3, 0.3, 0.7);
	GraphicsManager::get().drawSquareRelative(512, 128, 10, 10);

	// draw object text
	glColor3f(0.0, 1.0, 0.0);
	GraphicsManager::get().drawText("Object: tile_block.png", 15, 120);
}

// save functions
void EditorManager::saveLevel(const char* filename, vector<GameObject*> objects) {
	// create document
	XMLDocument doc;

	// setup initial elements
	XMLElement* data = doc.NewElement("data");
	XMLElement* objectsElements = doc.NewElement("objects");
	XMLElement* hudElements = doc.NewElement("hud");

	// loop through objects
	for (unsigned int i = 0; i < objects.size(); i++) {
		XMLElement* tempObject = doc.NewElement("object");

		switch (objects[i]->getObjectType()) {
			case OBJECT:
				saveGameObject(objects[i], tempObject, doc);
				saveObject(objects[i], tempObject, doc);
				objectsElements->LinkEndChild(tempObject);
				break;
			case PLAYER:
				saveGameObject(objects[i], tempObject, doc);
				savePlayer(objects[i], tempObject, doc);
				objectsElements->LinkEndChild(tempObject);
				break;
            case ENEMY:
                saveGameObject(objects[i], tempObject, doc);
                saveEnemy(objects[i], tempObject, doc);
                objectsElements->LinkEndChild(tempObject);
                break;
			case ITEM:
				saveGameObject(objects[i], tempObject, doc);
				saveItem(objects[i], tempObject, doc);
				objectsElements->LinkEndChild(tempObject);
				break;
			case ObjectType::FLAG:
				saveGameObject(objects[i], tempObject, doc);
				saveEndFlag(objects[i], tempObject, doc);
				objectsElements->LinkEndChild(tempObject);
				break;
			case HEALTH_HUD:
				saveHealthHUD(objects[i], tempObject, doc);
				hudElements->LinkEndChild(tempObject);
				break;
			default:
				break;
		}
	}

	// link data and document
	data->LinkEndChild(objectsElements);
	data->LinkEndChild(hudElements);
	doc.LinkEndChild(data);

	// save
	doc.SaveFile(filename);
}

void EditorManager::saveGameObject(GameObject* obj, XMLElement* objElement, XMLDocument& doc) {
	// object elements
	XMLElement* type = doc.NewElement("type");
	XMLElement* location = createLocationElement(obj, objElement, doc);

	// add type
	type->SetText(obj->getObjectType());
	objElement->LinkEndChild(type);

	// link location
	objElement->LinkEndChild(location);
}

void EditorManager::saveObject(GameObject* obj, XMLElement* objElement, XMLDocument& doc) {
	XMLElement* texture = doc.NewElement("texture");
	XMLElement* physics = doc.NewElement("physics");

	// physics value
	string physicsValue = "0";
	if (((Object*) obj)->isPhysicsEnabled()) {
		physicsValue = "1";
	}

	// create and set values
	texture->LinkEndChild(doc.NewText(((Object*) obj)->getTexturePath().c_str()));
	physics->LinkEndChild(doc.NewText(physicsValue.c_str()));

	// link new elements
	objElement->LinkEndChild(texture);
	objElement->LinkEndChild(physics);
}

void EditorManager::savePlayer(GameObject* obj, XMLElement* objElement, XMLDocument& doc) {
}

void EditorManager::saveEnemy(GameObject* obj, XMLElement* objElement, XMLDocument& doc){
	XMLElement* texture = doc.NewElement("texture");
	XMLElement* ai = doc.NewElement("ai");

	string aiStr = to_string((int) ((Enemy*) obj)->getAIBehaivor());

	// create and set values
	texture->LinkEndChild(doc.NewText(((Enemy*) obj)->getTexturePath().c_str()));
	ai->LinkEndChild(doc.NewText(aiStr.c_str()));

	objElement->LinkEndChild(texture);
	objElement->LinkEndChild(ai);
}

void EditorManager::saveItem(GameObject* obj, XMLElement* objElement, XMLDocument& doc) {
	XMLElement* texture = doc.NewElement("texture");

	XMLElement* size = createTileSizeElement(obj, objElement, doc);

	XMLElement* item = doc.NewElement("item");
	XMLElement* itemType = doc.NewElement("type");
	XMLElement* itemStat = doc.NewElement("stat");

	// get string values of item type/stats
	string itemTypeStr = to_string((int) ((Item*) obj)->getItemType());
	string itemStatStr = to_string((int) ((Item*) obj)->getStatIncrease());

	// create and set values
	texture->LinkEndChild(doc.NewText(((Item*) obj)->getTexturePath().c_str()));
	itemType->LinkEndChild(doc.NewText(itemTypeStr.c_str()));
	itemStat->LinkEndChild(doc.NewText(itemStatStr.c_str()));

	// link item values
	item->LinkEndChild(itemType);
	item->LinkEndChild(itemStat);

	// link new elements
	objElement->LinkEndChild(texture);
	objElement->LinkEndChild(item);
	objElement->LinkEndChild(size);
}

void EditorManager::saveEndFlag(GameObject* obj, XMLElement* objElement, XMLDocument& doc){
	XMLElement* texture = doc.NewElement("texture");

	// create and set values
	texture->LinkEndChild(doc.NewText(((EndFlag*) obj)->getTexturePath().c_str()));

	objElement->LinkEndChild(texture);
}

void EditorManager::saveHealthHUD(GameObject* obj, XMLElement* objElement, XMLDocument& doc) {
	// object elements
	XMLElement* type = doc.NewElement("type");

	// add type
	type->SetText(obj->getObjectType());
	objElement->LinkEndChild(type);
}

// insert object
void EditorManager::insertGameObject() {
	if (getEditSelection().x != -32 && getEditSelection().y != -32) {
		GameObject* tempObj;

		switch (objectToInsert.typeToInsert) {
			case ObjectType::OBJECT:
				tempObj = new Object(objectToInsert.texture.c_str(), true);
				break;
			case ObjectType::PLAYER:
				tempObj = new Player();
				break;
			case ObjectType::ENEMY:
				tempObj = new Enemy(objectToInsert.texture.c_str(), objectToInsert.AIPattern);
				break;
			case ObjectType::ITEM:
				tempObj = new Item(24, 24, objectToInsert.texture.c_str(), 1, objectToInsert.itemType);
				break;
			case ObjectType::FLAG:
				tempObj = new EndFlag(objectToInsert.texture.c_str());
				break;
			default: 
				return;
		}

		tempObj->setTransform(getEditSelection());

		SimulationManager::get().addObject(tempObj, true);
	}
}