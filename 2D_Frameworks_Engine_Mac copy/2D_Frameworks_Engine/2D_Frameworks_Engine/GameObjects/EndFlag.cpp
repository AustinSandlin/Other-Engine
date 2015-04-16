
#include "EndFlag.h"


EndFlag::EndFlag(string t){
    objectType = ObjectType::FLAG;
    
    setTileSize(64, 64);
    
    physicsProperties.categoryBits = PhysicsCategory::P_CAT_END;
    physicsProperties.maskBits = PhysicsMask::P_MASK_END;
    
    // load image
    textureID = GraphicsManager::get().loadImageFromTexture(t.c_str());
    texturePath = t;
    
    
}

EndFlag::~EndFlag(){
    
}

void EndFlag::draw(){
    
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

void EndFlag::update(){
    
}


bool EndFlag::collide(GameObject* obj, CollisionSide side){
    // player
    
    if (obj->getObjectType() == ObjectType::PLAYER
        && (side == CollisionSide::LEFT || side == CollisionSide::RIGHT)) {
        //End level
        SimulationManager::get().levelClear();
    }
    
    return false;
}