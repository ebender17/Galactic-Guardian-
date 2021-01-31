//------------------------------------------------------------------------
// Scene for explaining game exposition. 
//------------------------------------------------------------------------
#pragma once

#include "SceneStateMachine.h"
#include "app\app.h"

class SceneExposition : public Scene 
{
public: 
    SceneExposition(SceneStateMachine& sceneStateMachine);

    void OnActivate() override;

    void SetSwitchToScene(unsigned int id);

    void Update(float deltaTime) override;
    void Draw() override;

private:
    SceneStateMachine& sceneStateMachine;
    unsigned int switchToState; 

    float continueSeconds; //Seconds since key was pressed. Used to advance dialogue at readable pace.  
    std::vector<const char*> openingDialogue; //Stores text for scene's dialogue. 
    int dialogueIndex; 
    int dialogueCounter; 
};

