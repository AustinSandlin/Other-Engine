#include "HUDObject.h"

HUDObject::HUDObject() {
	isHUDObject = true;
}

HUDObject::~HUDObject() {
	/*while (textures.size() > 0) {
		textures.erase(textures.begin());
	}*/
}

void HUDObject::draw() {
}

void HUDObject::update() {
}

void HUDObject::loadTexture(const char* filename) {
	textureID = GraphicsManager::get().loadImageFromTexture(filename);
}