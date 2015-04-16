#include "SimManager.h"

SimulationManager& SimulationManager::get() {
	static SimulationManager instance;

    return instance;
}

SimulationManager::SimulationManager() {
    // instantiate
    GraphicsManager::get();
    PhysicsManager::get();
    SoundManager::get();
    

    
    // testing manually placing in objects
    numObjects = 2;
    objects = new GameObject*[numObjects];
    objects[0] = new Player();
    objects[1] = new Object();
    objects[1]->setTransform(256, 0, 0);
    numCollided = 0;
    
    // register with physics
    PhysicsManager::get().registerPhysicsObject(objects[0]);
    PhysicsManager::get().registerPhysicsObject(objects[1]);
    
}

SimulationManager::~SimulationManager() {
    for (int i = 0; i < numObjects; i++) {
        delete objects[i];
    }
    delete [] objects;
}

void SimulationManager::eventLoop() {
//    float timeDelta = 1000/30; //1000ms/30fps
    
    float timeDelta = 1.0 / 30.0f;
    clock_t startTime, currentTime;
    
    
//    float timeAccumulator = 0;
    bool gameRunning = true;
//    time_t startTime;
//    time_t currentTime;
//    float timeSpentOnThisIteration = 0;

    while (gameRunning){

        // get start time and reset time elapsed
        startTime = clock();
        double elapsed_secs = 0.0;
        
        
        // update objects
        for(int i = 0; i < numObjects; i++){
            objects[i]->update();
            
        }
      
        // if player has collide play sound
        if(PhysicsManager::get().getplayerCollision()){
            if(numCollided == 0){
                SoundManager::get().playSound();
            }
            numCollided++;
            
        }
       
        // redraw
        glutPostRedisplay();
       
        
        do {
            
            // poll glut things
            glutMainLoopEvent();
             
            // second clock/get time elapsed
            currentTime = clock();
            elapsed_secs = double(currentTime - startTime) / CLOCKS_PER_SEC;
           
        } while (elapsed_secs < timeDelta);
    }

}

void SimulationManager::render() {
    GraphicsManager::get().render(objects, numObjects);
   
}

void SimulationManager::keyPressed(unsigned char key, int x, int y){
    keyStates[key] = true;
    
}

void SimulationManager::keyUp(unsigned char key, int x, int y){
    keyStates[key] = false;
 }

void SimulationManager::keyOperations(){
    // Perform Key operations
    
    
}

void SimulationManager::keyboardInput(unsigned char key, int x, int y) {
    // Could have input manager handle this?
    
    // Thought: objects that want to do input would register with
    // input manager; input manager would then poll each registered
    // object to process input
    switch (key) {
        case 'a':
            ((Player*) SimulationManager::get().objects[0])->setVelocity(2, 0, 0);
             
            break;
        case 'Q':
        case 'q':
            glutDestroyWindow(glutGetWindow());
            exit(0);
            break;
        default:
            break;
    }
}

