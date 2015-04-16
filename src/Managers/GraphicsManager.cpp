#include "GraphicsManager.h"

GraphicsManager& GraphicsManager::get() {
	static GraphicsManager instance;

    return instance;
}

GraphicsManager::GraphicsManager() {
	// init display
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	glutCreateWindow("Game");
	init();

	fps = 0.0;
	score = 0;
	ammo = 20;
}

GraphicsManager::~GraphicsManager() {
	while (loadedTextures.size() > 0) {
		glDeleteTextures(1, &(loadedTextures[0]));
		loadedTextures.erase(loadedTextures.begin());
	}

	typedef map<string, GLuint>::iterator it_type;
	for(it_type iterator = loadedTexturesMap.begin(); iterator != loadedTexturesMap.end(); iterator++) {
		glDeleteTextures(1, &(iterator->second));
	}
}

void GraphicsManager::setOrthoView() {
	// set projection matrix
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

// helper drawing functions
void GraphicsManager::drawText(string str, int x, int y) {
	// draw some text
	glLoadIdentity();

	glRasterPos2i(x, y);
	for (string::iterator i = str.begin(); i != str.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
	}
}

void GraphicsManager::drawDouble(double d, int x, int y) {
	// setup fps string
	glLoadIdentity();
	ostringstream strStream;
	strStream << "" << setprecision(2) << fixed << d;
	string doubleStr = strStream.str();

	glRasterPos2i(x, y);
	for (string::iterator i = doubleStr.begin(); i != doubleStr.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
	}
}

void GraphicsManager::drawInt(int in, int x, int y){
	// setup score string
	glLoadIdentity();
	ostringstream strStream;
	strStream << "" << in;
	string intStr = strStream.str();

	glRasterPos2i(x, y);
	for (string::iterator i = intStr.begin(); i != intStr.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
	}
}

/* absolute world position space */
void GraphicsManager::drawSquareAbsolute(int w, int h, int x, int y) {
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslated(x, y, 0);
	glBegin(GL_QUADS);
		glVertex2f(0, h);
		glVertex2f(w, h);
		glVertex2f(w, 0);
		glVertex2f(0, 0);
	glEnd();
	glPopMatrix();
}

/* relative to current camera position */
void GraphicsManager::drawSquareRelative(int w, int h, int x, int y) {
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(x, y, 0);
	glBegin(GL_QUADS);
		glVertex2f(0, h);
		glVertex2f(w, h);
		glVertex2f(w, 0);
		glVertex2f(0, 0);
	glEnd();
	glPopMatrix();
}

// render functions
void GraphicsManager::renderGameMode(vector<GameObject*> objects) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT);

	// set pers
	setOrthoView();

	// set matrix mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// camera translation
	glTranslatef(cameraTransform.x, cameraTransform.y, cameraTransform.z);

	// draw objects
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}

	glColor3f(1.0, 0.0, 0.0); // Red
	drawDouble(fps, SCREEN_WIDTH - 54, SCREEN_HEIGHT - 15);
	drawText("Score: ", 27, SCREEN_HEIGHT - 15);
	drawInt(score, 90, SCREEN_HEIGHT - 15);
	drawText("Ammo: ", 140, SCREEN_HEIGHT - 15);
	drawInt(ammo, 200, SCREEN_HEIGHT - 15);

    // update screen
    glutSwapBuffers();
}

void GraphicsManager::renderEditMode(vector<GameObject*> objects, vector<GameObject*> physicsObjects, 
									 coord editSelection, InsertState state, ObjectInsertion& objToInsert) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT);

	// set pers
	setOrthoView();

	// set matrix mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// camera translation
	glTranslatef(cameraTransform.x, cameraTransform.y, cameraTransform.z);

	// draw objects
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (!objects[i]->isHUD()) {
			objects[i]->draw();

			// draw physics highlight
			if (typeid(*objects[i]) == typeid(Object) && ((Object*) objects[i])->isPhysicsEnabled()) {
				glDisable(GL_TEXTURE_2D);
				glColor4f(0, 1, 0, 0.4);
				glPushMatrix();
				glTranslated(objects[i]->getTransform().x, objects[i]->getTransform().y, 0);

				glBegin(GL_QUADS);
					glVertex2f(0, 32);
					glVertex2f(32, 32);
					glVertex2f(32, 0);
					glVertex2f(0, 0);
				glEnd();
				glPopMatrix();
			}
		}
	}

	// draw selection square
	glColor4f(1, 0, 0, 0.4);
	drawSquareAbsolute(32, 32, editSelection.x, editSelection.y);

	// draw lines
	glColor3f(0, 0, 0);
	glLineWidth(1); 
	glPushMatrix();
	glLoadIdentity();
	for (int i = 0; i < 21; i++) {
		glBegin(GL_LINES);
			glVertex2f(0, 0);
			glVertex2f(0, SCREEN_HEIGHT);
		glEnd();
		glTranslatef(32, 0, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	for (int i = 0; i < 16; i++) {
		glBegin(GL_LINES);
			glVertex2f(0, 0);
			glVertex2f(SCREEN_WIDTH, 0);
		glEnd();
		glTranslatef(0, 32, 0);
	}
	glPopMatrix();

	// draw insertion states
	if (state != InsertState::READY) {
		// draw edit square
		glColor4f(0.3, 0.3, 0.3, 0.75);
		drawSquareRelative(SCREEN_WIDTH - 20, 111, 10, 10);
	}

	switch (state) {
		case InsertState::READY:
			break;
		case InsertState::SELECT_TYPE:
			drawObjectTypeSelection(objToInsert, 1.0, 0.0, 0.0);
			break;
		case InsertState::PLAYER_CONFIRM:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectionConfirm(objToInsert, 15, 86);
			break;
		case InsertState::OBJECT_TEXTURE:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 1.0, 0.0, 0.0, 15, 86);
			break;
		case InsertState::OBJECT_CONFIRM:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 0.0, 1.0, 0.0, 15, 86);
			drawSelectionConfirm(objToInsert, 15, 69);
			break;
		case InsertState::ENEMY_TEXTURE:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 1.0, 0.0, 0.0, 15, 86);
			break;
		case InsertState::ENEMY_AI:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 0.0, 1.0, 0.0, 15, 86);
			drawSelectAIPattern(objToInsert, 1.0, 0.0, 0.0, 15, 69);
			break;
		case InsertState::ENEMY_CONFIRM:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 0.0, 1.0, 0.0, 15, 86);
			drawSelectAIPattern(objToInsert, 0.0, 1.0, 0.0, 15, 69);
			drawSelectionConfirm(objToInsert, 15, 52);
			break;
		case InsertState::ITEM_TEXTURE:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 1.0, 0.0, 0.0, 15, 86);
			break;
		case InsertState::ITEM_TYPE:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 0.0, 1.0, 0.0, 15, 86);
			drawSelectItemType(objToInsert, 1.0, 0.0, 0.0, 15, 69);
			break;
		case InsertState::ITEM_CONFIRM:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 0.0, 1.0, 0.0, 15, 86);
			drawSelectItemType(objToInsert, 0.0, 1.0, 0.0, 15, 69);
			drawSelectionConfirm(objToInsert, 15, 52);
			break;
		case InsertState::FLAG_TEXTURE:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 1.0, 0.0, 0.0, 15, 86);
			break;
		case InsertState::FLAG_CONFIRM:
			drawObjectTypeSelection(objToInsert, 0.0, 1.0, 0.0);
			drawSelectTexture(objToInsert, 0.0, 1.0, 0.0, 15, 86);
			drawSelectionConfirm(objToInsert, 15, 69);
			break;
		default:
			break;
	}

    // update screen
    glutSwapBuffers();
}

void GraphicsManager::drawObjectTypeSelection(ObjectInsertion& objToInsert, double r, double g, double b) {
	// DRAW OBJECT TEXT
	glColor3f(0.0, 1.0, 0.0);
	drawText("Object Type: ", 15, 103);
	glColor3f(r, g, b);
	drawText(objToInsert.getTypeString(), 130, 103);
}

void GraphicsManager::drawSelectTexture(ObjectInsertion& objToInsert, double r, double g, double b, double x, double y) {
	glColor3f(0.0, 1.0, 0.0);
	drawText("Select texture: ", x, y);

	glColor3f(r, g, b);
	drawText(objToInsert.texture, x + 140, y);
}

void GraphicsManager::drawSelectAIPattern(ObjectInsertion& objToInsert, double r, double g, double b, double x, double y) {
	glColor3f(0.0, 1.0, 0.0);
	drawText("Select AI pattern: ", x, y);

	glColor3f(r, g, b);
	drawText(objToInsert.getAITypeString(), x + 169, y);
}

void GraphicsManager::drawSelectItemType(ObjectInsertion& objToInsert, double r, double g, double b, double x, double y) {
	glColor3f(0.0, 1.0, 0.0);
	drawText("Select item type: ", x, y);

	glColor3f(r, g, b);
	drawText(objToInsert.getItemTypeString(), x + 160, y);
}

void GraphicsManager::drawSelectionConfirm(ObjectInsertion& objToInsert, double x, double y) {
	glColor3f(0.0, 1.0, 0.0);
	drawText("Confirm insert selection? (Jump key to confirm)", x, y);
}

void GraphicsManager::init() {
	// init
	glClearColor(0.4, 0.4, 0.4, 1.0);

	// init projection
	setOrthoView();
	glMatrixMode(GL_MODELVIEW);

	// image things
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // What to do when we run out of texture at the edge.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      
    // How to map the discrete texels to the frame buffer.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Tell opengl to multiply texture by the shade.
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

GLuint GraphicsManager::loadImageFromTexture(const char* filename, const char* loadPath) {
	if (loadPath == '\0') {
		loadPath = filename;
	}

	// if not found, load and return it
	if (loadedTexturesMap.find(filename) == loadedTexturesMap.end()) {
		printf("LOADING TEXTURE: %s\n", loadPath);
		// create opengl texture
		GLuint textureID = SOIL_load_OGL_texture(loadPath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

		if (textureID == 0) {
			cout << "Error loading " << filename << endl;
			return -1;
		}

		//glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// push texture to loaded textures map
		loadedTexturesMap[filename] = textureID;
	}

	return loadedTexturesMap[filename];
}

void GraphicsManager::setCameraTransform(float x, float y, float z) {
	if (x <= 0) {
		cameraTransform.x = x;
	}

	cameraTransform.y = y;
	cameraTransform.z = z;
}