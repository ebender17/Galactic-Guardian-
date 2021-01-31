//------------------------------------------------------------------------
// Scene to displays when player wins. 
//------------------------------------------------------------------------
#pragma once
#include "SceneStateMachine.h"
#include "App/app.h"

class SceneEndScreen : public Scene
{
public:
    SceneEndScreen();

    void Update(float deltaTime) override;
    void Draw() override;

};

