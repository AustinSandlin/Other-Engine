#ifndef EditorStates_H
#define EditorStates_H

#include "../GameObjects/GameObjectEnums.h"
#include <string>

using namespace std;

enum InsertState {
	READY,
	SELECT_TYPE,
	PLAYER_CONFIRM,
	OBJECT_TEXTURE,
	OBJECT_CONFIRM,
	ENEMY_TEXTURE,
	ENEMY_AI,
	ENEMY_CONFIRM,
	ITEM_TEXTURE,
	ITEM_TYPE,
	ITEM_CONFIRM,
	FLAG_TEXTURE,
	FLAG_CONFIRM
};

struct ObjectInsertion {
	ObjectType typeToInsert;
	string texture;
	AIBehaivor AIPattern;
	ItemType itemType;

	string getTypeString() {
		switch (typeToInsert) {
			case ObjectType::OBJECT:
				return "Object";
			case ObjectType::PLAYER:
				return "Player";
			case ObjectType::ENEMY:
				return "Enemy";
			case ObjectType::ITEM:
				return "Item";
			case ObjectType::FLAG:
				return "End Flag";
			default:
				return "";
		}
	}

	string getItemTypeString() {
		switch (itemType) {
			case ItemType::HEALTH_ITEM:
				return "Health";
			case ItemType::COIN_ITEM:
				return "Coin";
			case ItemType::AMMO_ITEM:
				return "Ammo";
			default:
				return "";
		}
	}

	string getAITypeString() {
		switch (AIPattern) {
			case AIBehaivor::HOOMER:
				return "Homer";
			case AIBehaivor::JUMPER:
				return "Jumper";
			case AIBehaivor::WANDER:
				return "Wander";
			default:
				return "";
		}
	}
};

#endif