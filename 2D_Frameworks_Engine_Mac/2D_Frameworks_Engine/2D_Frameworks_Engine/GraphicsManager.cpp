//#include "GraphicsManager.h"
//
//GraphicsManager& GraphicsManager::get() {
//	static GraphicsManager instance;
//
//    return instance;
//}
//
//GraphicsManager::GraphicsManager() {
//	cout << "GRAPHICS CONSTRUCTOR" << endl;
//
//    tempX = 0;
//    
//    // init display
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
//    
//    glutCreateWindow("OpenGL Template");
//    init();
//}
//
//GraphicsManager::~GraphicsManager() {
//}
//
//void GraphicsManager::setOrthoView() {
//	// set projection matrix
//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void GraphicsManager::render(GameObject** objects, int numObjs) {
//    // clear buffers
//    glClear(GL_COLOR_BUFFER_BIT);
//
//	// set pers
//	setOrthoView();
//
//	// set matrix mode
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    
//    // draw objects
//    for (int i = 0; i < numObjs; i++) {
//        objects[i]->draw();
//    }
//    
//    // update screen
//    glutSwapBuffers();
//}
//
//void GraphicsManager::init() {
//    // init
//    glClearColor(0.6, 0.6, 0.6, 1.0);
//    
//    // init projection
//    setOrthoView();
//    
//    // reset matrix mode
//    glMatrixMode(GL_MODELVIEW);
//    
//    // image things
//    glEnable(GL_TEXTURE_2D);
//    
//    // What to do when we run out of texture at the edge.
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//    
//    // How to map the discrete texels to the frame buffer.
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    
//    // Tell opengl to multiply texture by the shade.
//    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    
//    // Load an image to use as the texture
//    //int width, height;
//    //GLubyte *image = readImage("data/textures/texture.bmp", width, height);
//    
//    // Register the texture with opengl.
//    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//}
//
///**
// Utility function to read in a raw 4-byte integer.
// This assumes the host byteorder is LSB first.
// */
//static unsigned int rawLong( ifstream &stream ) {
//    unsigned int val = 1;
//    
//    // Get a pointer into val.
//    char *p = (char *)&val;
//    
//    // Test the byte order (stupid to do this every time)
//    if ( *p == 1 ) {
//        // Read each of the bytes of val.
//        stream.get( p[ 0 ] );
//        stream.get( p[ 1 ] );
//        stream.get( p[ 2 ] );
//        stream.get( p[ 3 ] );
//    } else {
//        stream.get( p[ 3 ] );
//        stream.get( p[ 2 ] );
//        stream.get( p[ 1 ] );
//        stream.get( p[ 0 ] );
//    }
//    
//    // Return the result.
//    return val;
//}
//
///**
// Utility function to read in a raw 2-byte integer.
// */
//static unsigned int rawShort( ifstream &stream ) {
//    unsigned short val = 1;
//    
//    // Get a pointer into val.
//    char *p = (char *)&val;
//    
//    // Test the byte order (stupid to do this every time)
//    if ( *p == 1 ) {
//        // Read each of the bytes of val (in lsb-first order).
//        stream.get( p[ 0 ] );
//        stream.get( p[ 1 ] );
//    } else {
//        // Read each of the bytes of val (in msb-first order).
//        stream.get( p[ 1 ] );
//        stream.get( p[ 0 ] );
//    }
//    
//    // Return the result.
//    return val;
//}
//
//GLubyte *GraphicsManager::readImage( const char *filename, int &width, int &height) {
//    // Open the output file for writing.
//    ifstream input( filename, ios::binary );
//    if( !input ) {
//        cerr << "Can't open bitmap file" << endl;
//        return 0;
//    }
//    
//    // Check the magic number.
//    if ( rawShort( input ) != 0x4d42 ) {
//        cerr << "Bad bitmap magic number" << endl;
//        return 0;
//    }
//    
//    // Read the size field.
//    rawLong( input );
//    
//    // Eat the next two fields.
//    rawShort( input );
//    rawShort( input );
//    
//    // Make sure we have the right header size.
//    if ( rawLong( input ) != 54 ) {
//        cerr << "Bad bitmap header size" << endl;
//        return 0;
//    }
//    
//    if ( rawLong( input ) != 40 ) {
//        cerr << "Bad bitmap header size" << endl;
//        return 0;
//    }
//    
//    width = rawLong( input );
//    height = rawLong( input );
//    
//    if ( rawShort( input ) != 1 ) {
//        cerr << "Don't know how to read this bitmap type" << endl;
//        return 0;
//    }
//    
//    if ( rawShort( input ) != 24 ) {
//        cerr << "Bitmap must be 24 bits." << endl;
//        return 0;
//    }
//    
//    // Eat a bunch of fields.
//    rawLong( input );
//    int ewidth = rawLong( input ) / width / 3;
//    ewidth = width;
//    rawLong( input );
//    rawLong( input );
//    rawLong( input );
//    rawLong( input );
//    
//    // Allocate space for the image.
//    char *image = new char [ width * height * 3 ];
//    
//    // Write out the raw contents of the framebuffer (bmp starts at the bottom
//    // line of the image.
//    for( int y = 0; y < height; y++ ){
//        int x;
//        for( x = 0; x < width; x++ ){
//            int index = ( x + y * width ) * 3;
//            
//            // Read the pixel at position x, y
//            input.get( image[ index + 2 ] );
//            input.get( image[ index + 1 ] );
//            input.get( image[ index + 0 ] );
//        }
//        
//        // Pad with zeros up to a 4-byte boundary
//        while ( x < ewidth ) {
//            char dummy;
//            input.get( dummy );
//            input.get( dummy );
//            input.get( dummy );
//            x++;
//        }
//    }
//    
//    return (GLubyte *) image;
//}
#include "GraphicsManager.h"

GraphicsManager& GraphicsManager::get() {
    static GraphicsManager instance;
    
    return instance;
}

GraphicsManager::GraphicsManager() {
    cout << "GRAPHICS CONSTRUCTOR" << endl;
    
    tempX = 0;
    
    // init display
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    glutCreateWindow("OpenGL Template");
    init();
}

GraphicsManager::~GraphicsManager() {
}

void GraphicsManager::setOrthoView() {
    // set projection matrix
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void GraphicsManager::render(GameObject** objects, int numObjs) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT);
    
    // set pers
    setOrthoView();
    
    // set matrix mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // draw objects
    for (int i = 0; i < numObjs; i++) {
        objects[i]->draw();
    }
    
    // update screen
    glutSwapBuffers();
}

void GraphicsManager::init() {
    // init
    glClearColor(0.6, 0.6, 0.6, 1.0);
    
    // init projection
    setOrthoView();
    
    // reset matrix mode
    glMatrixMode(GL_MODELVIEW);
    
    // image things
    glEnable(GL_TEXTURE_2D);
    
    // What to do when we run out of texture at the edge.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    // How to map the discrete texels to the frame buffer.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Tell opengl to multiply texture by the shade.
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Load an image to use as the texture
    //int width, height;
    //GLubyte *image = readImage("data/textures/texture.bmp", width, height);
    
    // Register the texture with opengl.
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
}

/**
 Utility function to read in a raw 4-byte integer.
 This assumes the host byteorder is LSB first.
 */
static unsigned int rawLong( ifstream &stream ) {
    unsigned int val = 1;
    
    // Get a pointer into val.
    char *p = (char *)&val;
    
    // Test the byte order (stupid to do this every time)
    if ( *p == 1 ) {
        // Read each of the bytes of val.
        stream.get( p[ 0 ] );
        stream.get( p[ 1 ] );
        stream.get( p[ 2 ] );
        stream.get( p[ 3 ] );
    } else {
        stream.get( p[ 3 ] );
        stream.get( p[ 2 ] );
        stream.get( p[ 1 ] );
        stream.get( p[ 0 ] );
    }
    
    // Return the result.
    return val;
}

/**
 Utility function to read in a raw 2-byte integer.
 */
static unsigned int rawShort( ifstream &stream ) {
    unsigned short val = 1;
    
    // Get a pointer into val.
    char *p = (char *)&val;
    
    // Test the byte order (stupid to do this every time)
    if ( *p == 1 ) {
        // Read each of the bytes of val (in lsb-first order).
        stream.get( p[ 0 ] );
        stream.get( p[ 1 ] );
    } else {
        // Read each of the bytes of val (in msb-first order).
        stream.get( p[ 1 ] );
        stream.get( p[ 0 ] );
    }
    
    // Return the result.
    return val;
}

GLubyte *GraphicsManager::readImage( const char *filename, int &width, int &height) {
    // Open the output file for writing.
    ifstream input( filename, ios::binary );
    if( !input ) {
        cerr << "Can't open bitmap file" << endl;
        return 0;
    }
    
    // Check the magic number.
    if ( rawShort( input ) != 0x4d42 ) {
        cerr << "Bad bitmap magic number" << endl;
        return 0;
    }
    
    // Read the size field.
    rawLong( input );
    
    // Eat the next two fields.
    rawShort( input );
    rawShort( input );
    
    // Make sure we have the right header size.
    if ( rawLong( input ) != 54 ) {
        cerr << "Bad bitmap header size" << endl;
        return 0;
    }
    
    if ( rawLong( input ) != 40 ) {
        cerr << "Bad bitmap header size" << endl;
        return 0;
    }
    
    width = rawLong( input );
    height = rawLong( input );
    
    if ( rawShort( input ) != 1 ) {
        cerr << "Don't know how to read this bitmap type" << endl;
        return 0;
    }
    
    if ( rawShort( input ) != 24 ) {
        cerr << "Bitmap must be 24 bits." << endl;
        return 0;
    }
    
    // Eat a bunch of fields.
    rawLong( input );
    int ewidth = rawLong( input ) / width / 3;
    ewidth = width;
    rawLong( input );
    rawLong( input );
    rawLong( input );
    rawLong( input );
    
    // Allocate space for the image.
    char *image = new char [ width * height * 3 ];
    
    // Write out the raw contents of the framebuffer (bmp starts at the bottom
    // line of the image.
    for( int y = 0; y < height; y++ ){
        int x;
        for( x = 0; x < width; x++ ){
            int index = ( x + y * width ) * 3;
            
            // Read the pixel at position x, y
            input.get( image[ index + 2 ] );
            input.get( image[ index + 1 ] );
            input.get( image[ index + 0 ] );
        }
        
        // Pad with zeros up to a 4-byte boundary
        while ( x < ewidth ) {
            char dummy;
            input.get( dummy );
            input.get( dummy );
            input.get( dummy );
            x++;
        }
    }
    
    return (GLubyte *) image;
}
