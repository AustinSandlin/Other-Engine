//
//  main.cpp
//  2D_Frameworks_Engine
//
//  Created by Caleb Sumpter on 2/1/15.
//  Copyright (c) 2015 Caleb Sumpter. All rights reserved.
//

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>

#else
#include <GL/glut.h>
#endif
#include <fstream>
#include <string>

#include "PhysicsManager.h"
#include "GraphicsManager.h"
#include "SimManager.h"

#include <irrKlang.h>

using namespace std;
using namespace irrklang;

void loadConfig() {
    ifstream in;
    in.open("data/config.txt");
    
    string stuff;
    while (in >> stuff) {
        cout << stuff << endl;
    }
}

void render() {
    SimulationManager::get().render();
}


void keyboard_wrapper(unsigned char key, int x, int y){
    SimulationManager::get().keyboardInput(key, x, y);
}
int main(int argc, char* args[]) {
    // Init glut and make a window.
    glutInit(&argc, args);

    
    
    // load config
    loadConfig();
    
    // instantiate managers
    SimulationManager::get();

    
    // callback functions and init
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard_wrapper);
    
    // loop
    //glutMainLoop();
    // loop
    SimulationManager::get().eventLoop();
    
    return 0;
}
