#include "stdafx.h"
#include "SceneMainMenu.h"

SceneMainMenu::SceneMainMenu(SceneStateMachine& sceneStateMachine)
    : sceneStateMachine(sceneStateMachine), currentSeconds(0.f)
{

}

void SceneMainMenu::SetSwitchToScene(unsigned int id)
{
    switchToState = id;
}

void SceneMainMenu::Update(float deltaTime)
{
    currentSeconds += deltaTime; 

    //Making sure screen does not transition right away if continue key is accidently hit (first conditional)
    if (currentSeconds > 3.f && (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)))
    {
        sceneStateMachine.SwitchTo(switchToState);
    }
}

void SceneMainMenu::Draw()
{

	App::Print(APP_INIT_WINDOW_WIDTH / 2.5f, APP_INIT_WINDOW_HEIGHT / 1.5f, "Welcome to Galactic Guardian", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);

	App::Print(APP_INIT_WINDOW_WIDTH / 2.5f, APP_INIT_WINDOW_HEIGHT / 2.f, "Press Space or A to start", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);

}