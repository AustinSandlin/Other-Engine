#include "Item.h"

Item::Item(int w, int h, string texture, int stat, ItemType itType) {
	// tile size
	setTileSize(w, h);

	// physics properties
	physicsProperties.categoryBits = P_CAT_ITEM;
	physicsProperties.maskBits = PhysicsMask::P_MASK_ITEM;

	// object type
	objectType = ObjectType::ITEM;

	// load texture
	textureID = GraphicsManager::get().loadImageFromTexture(texture.c_str());
	texturePath = texture;

	// constructor
	statIncrease = stat;
	itemType = itType;
	charges = 1;
}

Item::~Item() {
}

void Item::update() {
}

void Item::draw() {
	// enable textures
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glColor3f(1, 1, 1);

	glPushMatrix();
	glTranslated(transform.x, transform.y, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(0, tileSize.y);
		glTexCoord2f(1, 1);
		glVertex2f(tileSize.x, tileSize.y);
		glTexCoord2f(1, 0);
		glVertex2f(tileSize.x, 0);
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);
	glEnd();
	glPopMatrix();

	// disable
	glDisable(GL_TEXTURE_2D);
}

bool Item::collide(GameObject* obj, CollisionSide side) {
	bool flag = false;

	if (charges > 0) {
		switch (itemType) {
			case ItemType::HEALTH_ITEM:
				healthItem((Player*) obj);
				break;
			case ItemType::COIN_ITEM:
				coinItem((Player*) obj);
				break;
			case ItemType::AMMO_ITEM:
				ammoItem((Player*) obj);
				break;
			default:
				break;
		}
	}
	charges--;

	return flag;
}


/*****************
* ITEM FUNCTIONS *
******************/
/* this function is called whenever an object collides with a health item */
void Item::healthItem(Player* player) {
	SoundManager::get().playHealthPickupSound();
	player->setHealth(player->getHealth() + statIncrease);

	PhysicsManager::get().destroyObject((GameObject*) this);
}

void Item::coinItem(Player* player) {
	SoundManager::get().playScorePickupSound();
	SimulationManager::get().increaseScore();

	PhysicsManager::get().destroyObject((GameObject*) this);
}

void Item::ammoItem(Player* player) {
	SoundManager::get().playAmmoPickupSound();
	SimulationManager::get().increaseAmmo();

	PhysicsManager::get().destroyObject((GameObject*) this);
}


