//
//  Projectile.cpp
//  FrameWorks
//
//  Created by Tanner Taylor on 3/19/15.
//

#include "Projectile.h"

// constructor
Projectile::Projectile(const char* filename) {
	velocity.x = 6;
	velocity.y = 0;
	velocity.z = 0;

	// set time to live
	timeToLive = 4 * 30;

	// set type
	objectType = ObjectType::PROJECTILE;

	// set tile
	setTileSize(16, 16);

	// set physics
	physicsProperties.categoryBits = PhysicsCategory::P_CAT_PROJECTILE;
	physicsProperties.maskBits = PhysicsMask::P_MASK_PROJECTILE;

	// load texture
	textureID = GraphicsManager::get().loadImageFromTexture(filename);
}

// destructor
Projectile::~Projectile() {
}

// polymorphic functions
void Projectile::update() {
	timeToLive--;
	if (timeToLive <= 0) {
		PhysicsManager::get().destroyObject((GameObject*) this);
	}
	else {
		PhysicsManager::get().move(this);
	}
}

void Projectile::draw() {
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

bool Projectile::collide(GameObject* obj, CollisionSide side) {
	if (obj->getObjectType() == ObjectType::ENEMY) {
		// turn enemy red
		// injure enemy
		Enemy* enemyObj = ((Enemy*) obj);
		enemyObj->setHealth(enemyObj->getHealth() - 1);
	}

	PhysicsManager::get().destroyObject((GameObject*) this);
	return false;
}