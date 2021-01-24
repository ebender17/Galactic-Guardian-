//------------------------------------------------------------------------
// Game.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Finite State Machine includes
//------------------------------------------------------------------------
#include "SceneStateMachine.h"
#include "SceneMainMenu.h"
#include "SceneExposition.h"
#include "SceneGame.h"
#include "SceneLostGame.h"
#include "SceneEndScreen.h"

SceneStateMachine sceneStateMachine;

unsigned int mainMenuID; 
unsigned int expoSceneID;
unsigned int gameSceneID; 
unsigned int lostGameSceneID;
unsigned int endSceneID; 

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//Create game scenes 
	std::shared_ptr<SceneMainMenu> mainMenuScreen = std::make_shared<SceneMainMenu>(sceneStateMachine);

	std::shared_ptr<SceneExposition> expoScene = std::make_shared<SceneExposition>(sceneStateMachine);

	std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>(sceneStateMachine);

	std::shared_ptr<SceneLostGame> lostGameScene = std::make_shared<SceneLostGame>(sceneStateMachine);

	std::shared_ptr<SceneEndScreen> endScene = std::make_shared<SceneEndScreen>(); 

	//Add scenes to Scene State Machine
	mainMenuID = sceneStateMachine.Add(mainMenuScreen);
	expoSceneID = sceneStateMachine.Add(expoScene); 
	gameSceneID = sceneStateMachine.Add(gameScene);
	lostGameSceneID = sceneStateMachine.Add(lostGameScene); 
	endSceneID = sceneStateMachine.Add(endScene); 

	//Set scenes to switch to for each scene
	mainMenuScreen->SetSwitchToScene(expoSceneID);
	expoScene->SetSwitchToScene(gameSceneID);
	gameScene->SetSwitchToScene(endSceneID, lostGameSceneID); 
	lostGameScene->SetSwitchToScene(gameSceneID); 

	//After set-up, switching to main menu
	sceneStateMachine.SwitchTo(mainMenuID);

}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//Converting deltaTime to seconds to make calculations easier
	deltaTime /= 1000.f; 
	sceneStateMachine.Update(deltaTime); 
	
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	sceneStateMachine.Draw(); 

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	sceneStateMachine.Remove(mainMenuID); 
	sceneStateMachine.Remove(expoSceneID);
	sceneStateMachine.Remove(gameSceneID); 
	sceneStateMachine.Remove(lostGameSceneID);
	sceneStateMachine.Remove(endSceneID);
}