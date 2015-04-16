//
//  HUDObject.h
//  FrameWorks
//
//  Created by Tanner Taylor on 2/26/2015
//  Copyright (c) 2015 Tanner Taylor. All rights reserved.
//

#ifndef _HUD_OBJECT
#define _HUD_OBJECT

#include <vector>
#include "../Managers/GraphicsManager.h"
#include "GameObject.h"

class HUDObject : public GameObject {
	private:
		GLuint textureID;

	public:
		HUDObject();
		~HUDObject();

		virtual void draw();
		virtual void update();

		void loadTexture(const char* filename);
		GLuint getTextureID() { return textureID; }
};

#endif