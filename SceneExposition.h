#pragma once

#include "SceneStateMachine.h"
#include "app\app.h"
#include <vector>

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

    float continueSeconds; //Seconds since key was pressed to continue dialogue 
    std::vector<const char*> openingDialogue; //stores c strings for scene's dialogue
    int dialogueIndex; 
    int dialogueCounter; 
};

