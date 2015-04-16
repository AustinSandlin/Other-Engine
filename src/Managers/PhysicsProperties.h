enum CollisionSide {
	TOP = 1,
	BOTTOM = -1,
	LEFT = 2, 
	RIGHT = -2
};

/* collision filter stuff */
enum PhysicsCategory {
	P_CAT_ANY        = 0x0001,
	P_CAT_PLAYER     = 0x0002,
	P_CAT_OBJECT     = 0x0004,
	P_CAT_ENEMY      = 0x0008,
	P_CAT_ITEM       = 0x0010,
	P_CAT_PROJECTILE = 0x0020,
	P_CAT_END        = 0x0040,
	P_CAT_SPAWNER    = 0x0080
};

enum PhysicsMask {
	P_MASK_ANY = 0xFFFF,
	P_MASK_NONE = 0x0000,
	P_MASK_PLAYER = PhysicsCategory::P_CAT_OBJECT | PhysicsCategory::P_CAT_ENEMY 
					| PhysicsCategory::P_CAT_ITEM | P_CAT_END | P_CAT_SPAWNER,
	P_MASK_ENEMY = PhysicsCategory::P_CAT_PLAYER | PhysicsCategory::P_CAT_OBJECT 
					| PhysicsCategory::P_CAT_PROJECTILE,
	P_MASK_PROJECTILE = PhysicsCategory::P_CAT_OBJECT | PhysicsCategory::P_CAT_ENEMY,
	P_MASK_ITEM = PhysicsCategory::P_CAT_PLAYER,
	P_MASK_END = PhysicsCategory::P_CAT_PLAYER
};

struct PhysicsProperties {
	PhysicsCategory categoryBits;
	int maskBits;

	PhysicsProperties() {
		categoryBits = PhysicsCategory::P_CAT_ANY;
		maskBits = PhysicsMask::P_MASK_ANY;
	}
};