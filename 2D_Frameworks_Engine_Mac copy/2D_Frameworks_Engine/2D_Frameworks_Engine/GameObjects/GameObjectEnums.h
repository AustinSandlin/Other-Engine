#ifndef GAME_OBJECT_ENUMS
#define GAME_OBJECT_ENUMS

enum ObjectType {
    NONE = -1, OBJECT, PLAYER, HEALTH_HUD, ENEMY, PROJECTILE,
    ITEM, FLAG
};

enum ItemType {
    HEALTH_ITEM, COIN_ITEM
};

enum AIBehaivor{
    WANDER = 1, JUMPER = 2, HOOMER = 3
};

#endif