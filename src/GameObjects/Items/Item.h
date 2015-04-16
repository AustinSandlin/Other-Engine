//
//  Item.h
//  FrameWorks
//
//  Created by Tanner Taylor on 3/21/15.
//

#ifndef ITEM_H
#define ITEM_H

using namespace std;

#include "../GameObject.h"
#include "../Player.h"
#include "../../Managers/GraphicsManager.h"
#include "../GameObjectEnums.h"

class Player;

class Item : public GameObject {
	private:
		// texture things
		int imageH, imageW;
		GLuint textureID;
		string texturePath;
		ItemType itemType;
		int charges; // how many times the item can be used

		// stats
		int statIncrease;

		// item functions
		void healthItem(Player* player);
		void coinItem(Player* player);

	public:
		// constructor/deconstructor
		Item(int w, int h, string texture, int stat, ItemType itType);
		~Item();

		// overridden gameobject functions
		void update();
		void draw();
		bool collide(GameObject* obj, CollisionSide side);

		// getter/setters
		ItemType getItemType() { return itemType; }
		void setItemType(ItemType it) { itemType = it; }
		int getStatIncrease() { return statIncrease; }
		string getTexturePath() { return texturePath; }
};

#endif