========================================================================
    CONSOLE APPLICATION : Galactic Guardian Overview
========================================================================
Theme & Objective: Galactic Guardian is a top-down space shooter. 
The player is a single spaceship who has been tasked with defending the galaxy. 
To clear each level, one must clear the galaxy crowded with dangerous objects and enemies. 
In the first level, the player must clear space of a giant asteroid field. 
In the second level, the player battles enemy alien creatures. 
In the final level, the player must eliminate an invading enemy militia. 
These enemies are a little smarter than the previous foes the player has faced, so one must be careful. 
If the player is successful in eliminating all the enemies, they have saved the galaxy and won the game!

Controls: The player can steer and thrust themselves using WASD or the left thumb stick on controller.
To fire bullets and proceed through text screens, press the SPACE key on PC or A button on controller.

Files:
•	Game.cpp: main source file
•	SceneStateMachine: simple Finite State Machine, stores game scenes, only has one scene activate at a time, transitions scenes from one to the other
•	Scene.h: parent class of all scene classes, abstract class that is not instantiated (interface)
•	SceneMainMenu: first scene of game, displays game title 
•	SceneExposition: second scene of game, gives the player the game objective and controls
•	SceneGame: scene where gameplay happens, all three levels occur in this scene 
•	SceneLostGame: scene displayed if player dies, have option to play again 
•	SceneEndScreen: scene displayed when player wins 
•	GameObject.h: parent class of game objects, abstract class that is not instantiated (interface)
•	Enemy: contains asteriods, alien creatures, and smart enemy ships
•	Bullet: bullet object the protagonist (player) fires 
•	Protagonist: the player’s character



/////////////////////////////////////////////////////////////////////////////

Below is the original ReadMe information included in the simple API. 

/////////////////////////////////////////////////////////////////////////////

AppWizard has created this GameTest application for you.

This file contains a summary of what you will find in each of the files that
make up your GameTest application.


GameTest.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

GameTest.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

GameTest.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named GameTest.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
