#include "stdafx.h"
#include "SceneLostGame.h"
SceneLostGame::SceneLostGame(SceneStateMachine& sceneStateMachine)
	: sceneStateMachine(sceneStateMachine), currentSeconds(0.f)
{

}

void SceneLostGame::SetSwitchToScene(unsigned int id)
{
	switchToState = id;
}

void SceneLostGame::Update(float deltaTime)
{
	currentSeconds += deltaTime; 

	if (currentSeconds > 2.f && (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)))
	{
		sceneStateMachine.SwitchTo(switchToState); 
	}
}

void SceneLostGame::Draw()
{
	App::Print(APP_INIT_WINDOW_WIDTH / 2.5f, APP_INIT_WINDOW_HEIGHT / 1.5f, "You have failed your misson.", 1.f, 0.f, 0.f, GLUT_BITMAP_9_BY_15);
	App::Print(APP_INIT_WINDOW_WIDTH / 2.75f, APP_INIT_WINDOW_HEIGHT / 2.f, "Press A or the SPACE key to play again!", 1.f, 0.f, 0.f, GLUT_BITMAP_9_BY_15);
}
