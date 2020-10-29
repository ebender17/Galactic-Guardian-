#pragma once

#include "SceneStateMachine.h"
#include "app\app.h"
#include <cstdlib>
#include <ctime>

class SceneMainMenu: public Scene
{
public:
    SceneMainMenu(SceneStateMachine& sceneStateMachine);

    void SetSwitchToScene(unsigned int id);

    void Update(float deltaTime) override;
    void Draw() override;

private:
    SceneStateMachine& sceneStateMachine;
    unsigned int switchToState; // The state we want to transition to when desired.

    float currentSeconds; //secs since scene was created
};

