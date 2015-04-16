#include "HealthHUD.h"

HealthHUD::HealthHUD() {
    frame = 0;
    healthPercentage = 1.0;
    
    tileSize.x = 148;
    tileSize.y = 48;
    
    objectType = HEALTH_HUD;
    
    transform.y = (float) SCREEN_HEIGHT - tileSize.y - 5;
    transform.x = 5;
    
    loadTexture("data/textures/Healthbar.png");
}

HealthHUD::~HealthHUD() {
}

void HealthHUD::draw() {
    // enable textures
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTextureID());
    glColor3f(1, 1, 1);
    
    // push matrix and update
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslated(transform.x, transform.y, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(0, tileSize.y);
    glTexCoord2f(1, 1);
    glVertex2f(tileSize.x*healthPercentage, tileSize.y);
    glTexCoord2f(1, 0);
    glVertex2f(tileSize.x*healthPercentage, 0);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glEnd();
    glPopMatrix();
    
    // disable
    glDisable(GL_TEXTURE_2D);
}

void HealthHUD::update(float newPercentage) {
    healthPercentage = newPercentage;
    
    if(healthPercentage > 1.0){
        healthPercentage = 1.0;
    }
    if(healthPercentage < 0.0){
        healthPercentage = 0.0;
    }
}