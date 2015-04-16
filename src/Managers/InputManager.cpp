#include "InputManager.h"

InputManager& InputManager::get() {
	static InputManager instance;

    return instance;
}

InputManager::~InputManager(){
	
}

InputManager::InputManager(){
	//Initialize our keyMap to default controls
	keyMap.insert(pair<char,int>('a',LEFT_MOVE_EVENT));
	keyMap.insert(pair<char,int>('d', RIGHT_MOVE_EVENT));
	keyMap.insert(pair<char,int>('s',SOUNDEVENT));
	keyMap.insert(pair<char,int>('q',QUITEVENT));
	keyMap.insert(pair<char,int>('\t', CHANGE_MODE_EVENT));
	keyMap.insert(pair<char,int>(127, DELETE_OBJECT)); // 127 is delete key
	keyMap.insert(pair<char,int>('p', EDIT_SET_PHYSICS));
	keyMap.insert(pair<char,int>('m', EDIT_SAVE_LEVEL));
	keyMap.insert(pair<char,int>('i', EDIT_INSERT_OBJECT));
	keyMap.insert(pair<char,int>(' ', JUMP_EVENT));
	keyMap.insert(pair<char,int>('f', FIRE_PROJECTILE_EVENT));
}

int InputManager::processKeyboardInput(unsigned char key){
	int event = 0;
	event = keyMap[key];
	return event;
}