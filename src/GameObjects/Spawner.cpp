#include "Spawner.h"

Spawner::Spawner(string path, int interval, string texture, int ai){
	objectType = ObjectType::SPAWNER;

	setTileSize(64, 64);

	physicsProperties.categoryBits = PhysicsCategory::P_CAT_SPAWNER;
	physicsProperties.maskBits = PhysicsMask::P_MASK_ANY;

	// load image
	textureID = GraphicsManager::get().loadImageFromTexture(path.c_str());
	texturePath = path;

	// initialize the spawn timer
	spawnTimer = 0;
	spawnInterval = interval;
	enabled = true;

	// initialize the enemy template
	enemyTexturePath = texture;
	enemyAIBehavior = ai;
}

Spawner::~Spawner(){
}

void Spawner::draw(){

	// enable textures and set texture and color
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glColor3f(1, 1, 1);

	// push current matrix and translate position
	glPushMatrix();
	glTranslated(transform.x, transform.y, 0);

	// draw flag
	float yClip = 0.5 - (getRotate().z / 360.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(0, tileSize.y);
		glTexCoord2f(1,1);
		glVertex2f(tileSize.x, tileSize.y);		
		glTexCoord2f(1,0);
		glVertex2f(tileSize.x, 0);		
		glTexCoord2f(0,0);
		glVertex2f(0, 0);
	glEnd();

	// pop matrix and disable texture
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Spawner::update(){

	// check for collision before updating
	enabled = true;
	PhysicsManager::get().move(this);

	// check if an enemy should be spawned
	if (enabled && ++spawnTimer >= spawnInterval) {

		// load the new enemy from the template
		Enemy* enemy = new Enemy(enemyTexturePath, enemyAIBehavior);
    	enemy->setTransform(transform.x, transform.y, transform.z);
		enemy->setWanderMinDistance();
		enemy->setWanderMaxDistance();
    	SimulationManager::get().addObject(enemy, true);

		// reset the spawn timer
		spawnTimer = 0;
	}
}

bool Spawner::collide(GameObject* object, CollisionSide side) {

	// disable the spawner if anything has collided with it
	enabled = false;
	return false;
}
