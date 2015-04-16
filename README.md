# README #

### Demo Functionality ###

Controls (in-game mode)
```
a - move player left
d - move player right
s - play sound
space bar - jump
tab - change to edit mode
f - fire projectile
```

If an object has physics enabled, the player should not be able to pass through the object. The player also has gravity, so if the player does not have a physics object below it, then the player will fall.

#### File Structure ####

In the root folder (where the executable is) there should the following folder structure
```
-- root
    -- data
        -- levels
        -- textures
        -- sounds
```

Texture should contain the textures necessary to load a level. The game by default loads "test_level_1.xml" (located in the levels folder). A template for the level is below
```
<data>
    <objects>
    </objects>
    <hud>
    </hud>
</data>
```
It will then load "test_level_2.xml" and "test_level_3.xml" when the preceding level is completed. Upon completion of level 3, the game starts back over at level 1.

### Edit Mode ###

While in game mode, the user can press the tab key to enter edit mode. There are separate controls for edit mode:
```
tab - return to game mode
a - move camera left
d - move camera right
p - toggle physics of object (only for objects -- not player)
i - set the object to be inserted
f - change options on insert menu
space - accept/confirm option on insert menu
delete (fn+delete on Mac) - delete the selected object
m - save map
left click - select a tile
right click - insert current object at empty tile
```

Note that while developing using the source code, new classes of objects should go in the GameObjects folder, while new manager modules should go in the Managers folder.

### Setting Up Libraries ###

Currently we are using

* OpenGL (freeglut)
* irrKlang (1.5.0)
* SOIL (Simple OpenGL Image Library)

#### For Visual Studio 2012 ####

The project is setup to where it should be able to be compiled out-of-the-box. Inside the 2D_Frameworks_Engine folder is a folder called "development" that contains all the necessary files to compile with the 3rd party libraries.
```
development/<library name from repo>
```

#### Other ####

Download/compile the libraries above. Include the "include" and "lib" folders in your project's build settings. The linker settings are as follows (without quotations)

* freeglut ("OpenGL32.lib", "freeglut.lib")
* irrKlang ("irrKlang.lib")
* SOIL ("SOIL.lib")


### File Hierarchy ###

There are two "project/solution" folders; one for VS2012 and one for Mac. The "src" folder contains all the .cpp and .h files necessary. When developing, add your files to this folder, and then "include" it in your respective project file.