//
//  HealthHUD.h
//  FrameWorks
//
//  Created by Tanner Taylor on 2/28/15.
//  Copyright (c) 2015 Tanner Taylor. All rights reserved.
//

#ifndef FRAMEWORKS_HEALTHHUD
#define FRAMEWORKS_HEALTHHUD

#include "HUDObject.h"

class HealthHUD : public HUDObject {
	private:
		int frame;
		float healthPercentage;
	public:
		HealthHUD();
		~HealthHUD();

		void draw();
		void update(float newPercentage);
};

#endif