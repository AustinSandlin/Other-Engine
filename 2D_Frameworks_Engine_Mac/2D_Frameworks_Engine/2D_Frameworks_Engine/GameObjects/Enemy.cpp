//
//  Enemy.cpp
//  2D_Frameworks_Engine
//


#include "Enemy.h"


Enemy::Enemy(string texture, int ai){
    
    velocity.x = -2;
    velocity.y = 0;
    velocity.z = 0;
    
    setTileSize(32, 64);
    animationFrame = 0;
    
    //load image
    textureID = GraphicsManager::get().loadImageFromTexture(texture.c_str());
    texturePath = texture;
    
    objectType = ENEMY;
    physicsProperties.categoryBits = PhysicsCategory::P_CAT_ENEMY;
    physicsProperties.maskBits = PhysicsMask::P_MASK_ENEMY;
    
    // default health
    maxHealth = 2;
    health = maxHealth;
    gravity = true;
    
    aiBehaivor = ai;
    
    this->maxWanderDistance = 100;
    this->minWanderDistance = 20;
    
    this->canMoveFlag = false;
}

Enemy::~Enemy(){
    
}

int Enemy::getHealth(){
    return health;
}

void Enemy::update(){
    
    if (getHealth() <= 0) {
        SoundManager::get().playDeathSound();
        SimulationManager::get().increaseScore();
        PhysicsManager::get().destroyObject((GameObject*) this);
        return;
    }
    
    
    if (gravity && velocity.y > -3) {
        
        velocity.y -= 0.25;
    }
    
    switch (getAIBehaivor()) {
        case  1:
            AIController::get().wander(this, getWanderMaxDistance(), getWanderMinDistance());
            break;
        case 2:
            AIController::get().jump(this);
            break;
        case 3:
            AIController::get().hoomer(this);
            break;
            
        default:
            break;
    }
    
    
    if (velocity.x > 0 || velocity.x < 0) {
        incrementAnimationFrame();
    }
}

void Enemy::draw(){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1, 1, 1);
    
    glPushMatrix();
    glTranslated(transform.x, transform.y, 0);
    
    float yClip = 0.5 - (getRotate().z / 360.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, yClip + 0.5);
    glVertex2f(0, tileSize.y);
    glTexCoord2f(1, yClip + 0.5);
    glVertex2f(tileSize.x, tileSize.y);
    glTexCoord2f(1, yClip);
    glVertex2f(tileSize.x, 0);
    glTexCoord2f(0, yClip);
    glVertex2f(0, 0);
    glEnd();
    
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}

void Enemy::incrementAnimationFrame(){
    animationFrame += 0.25;
    
    if (animationFrame >= 4.0) {
        animationFrame = 0.0;
    }
}

void Enemy::setWanderMaxDistance(){
    
    maxWanderDistance = getTransform().x + 20;
}

void Enemy::setWanderMinDistance(){
    minWanderDistance = getTransform().x - 100;
}
int Enemy::getWanderMaxDistance(){
    return maxWanderDistance;
}

int Enemy::getWanderMinDistance(){
    return minWanderDistance;
}

void Enemy::setVelocity(float x, float y, float z) {
    
    velocity.x = x;
    velocity.y = y;
    velocity.z = y;
}

void Enemy::setHealth(int h){
    if (h >= 0 && h <= maxHealth){
        health = h;
    }
}
bool Enemy::collide(GameObject* obj, CollisionSide side) {

    // Player
    if (obj->getObjectType() == ObjectType::PLAYER) {
        if (side == CollisionSide::LEFT) {
            velocity.x = abs(velocity.x);
        }
        else {
            if (side == CollisionSide::RIGHT) {
                velocity.x = -1 * abs(velocity.x);
            }
        }
    }
    
    // Object
    if (obj->getObjectType() == ObjectType::OBJECT){
        switch (side) {
            case CollisionSide::BOTTOM:
                this->canJumpFlag = true;
                jumpTrans.x = 0;
                jumpTrans.y = 7;
                jumpTrans.z = 0;
            default:
                break;
        }
    }
    
    return true;
}
