#ifndef EditorManager_H
#define EditorManager_H

#include <vector>
#include <string>

#include "../GameObjects/GameObject.h"
#include "../tinyxml2/tinyxml2.h"
#include "../GameObjects/Object.h"
#include "../GameObjects/Items/Item.h"
#include "EditorStates.h"

using namespace std;
using namespace tinyxml2;

class EditorManager {
	private:
		// variables
		bool editMode;
		coord editSelection;
		int selectedObject;
		ObjectInsertion objectToInsert;
		InsertState insertState;

		// singleton
		EditorManager();

		EditorManager(EditorManager const&); // Don't Implement
        void operator=(EditorManager const&); // Don't implement

		// render editor menus
		void renderObject();

		// helper functions
		XMLElement* createLocationElement(GameObject* obj, XMLElement* objElement, XMLDocument& doc);
		XMLElement* createTileSizeElement(GameObject* obj, XMLElement* objElement, XMLDocument& doc);

	public:
		static EditorManager& get();
		~EditorManager();

		// render editor menus
		void renderEditor();

		// level functions
		void saveLevel(const char* filename, vector<GameObject*> objects);
		void saveGameObject(GameObject* obj, XMLElement* objElement, XMLDocument& doc);
		void saveObject(GameObject* obj, XMLElement* objElement, XMLDocument& doc);
		void savePlayer(GameObject* obj, XMLElement* objElement, XMLDocument& doc);
		void saveEnemy(GameObject* obj, XMLElement* objElement, XMLDocument& doc);
		void saveItem(GameObject* obj, XMLElement* objElement, XMLDocument& doc);
		void saveEndFlag(GameObject* obj, XMLElement* objElement, XMLDocument& doc);
		void saveSpawner(GameObject* obj, XMLElement* objElement, XMLDocument& doc);
		void saveHealthHUD(GameObject* obj, XMLElement* objElement, XMLDocument& doc);

		// insert object
		void insertGameObject();

		// getter and setters
		bool isEditMode() { return editMode; }
		void setEditMode(bool edit) { editMode = edit; }
		int getSelectedObject() { return selectedObject; }
		void setSelectedObject(int select) { selectedObject = select; }
		coord getEditSelection() { return editSelection; }
		void setEditSelection(coord select) { editSelection = select; }
		void setEditSelection(float x, float y, float z) { editSelection.x = x; editSelection.y = y; editSelection.z = z; }
		ObjectInsertion& getObjectToInsert() { return objectToInsert; }
		InsertState getInsertState() { return insertState; }
		void setInsertState(InsertState state) { insertState = state; }
};

#endif