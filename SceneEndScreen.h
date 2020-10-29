#pragma once
#include "SceneStateMachine.h"
#include "App/app.h"
#include <cstdlib>
#include <ctime>

class SceneEndScreen : public Scene
{
public:
    SceneEndScreen();

    void Update(float deltaTime) override;
    void Draw() override;

};

