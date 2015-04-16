//
//  Object.cpp
//  FrameWorks
//
//  Created by Caleb Sumpter on 1/28/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include "Object.h"


Object::Object(){
    tileSize.x = 32;
	tileSize.y = 32;

	objectType = OBJECT;
	physicsProperties.categoryBits = PhysicsCategory::P_CAT_OBJECT;
}

Object::Object(const char* filename, bool physics) {
	tileSize.x = 32;
	tileSize.y = 32;

	objectType = OBJECT;
	physicsProperties.categoryBits = PhysicsCategory::P_CAT_OBJECT;

	textureID = GraphicsManager::get().loadImageFromTexture(filename);

	physicsEnable = physics;

	texturePath = filename;
}

Object::Object(const char* filename, bool physics, int width, int height) {
	tileSize.x = width;
	tileSize.y = height;

	objectType = OBJECT;
	physicsProperties.categoryBits = PhysicsCategory::P_CAT_OBJECT;

	textureID = GraphicsManager::get().loadImageFromTexture(filename);

	physicsEnable = physics;

	texturePath = filename;
}

Object::~Object(){
    
}

void Object::update(){
    
}

void Object::draw(){
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

bool Object::collide(GameObject* obj, CollisionSide side) {
	switch (side) {
		case CollisionSide::RIGHT:
		case CollisionSide::LEFT:
			break;
		case CollisionSide::TOP:
		case CollisionSide::BOTTOM:
			obj->setVelocity(obj->getVelocity().x, 0, obj->getVelocity().z);
			break;
		default:
			break;
	}

	return true;
}