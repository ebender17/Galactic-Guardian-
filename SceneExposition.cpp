#include "stdafx.h"
#include "SceneExposition.h"

SceneExposition::SceneExposition(SceneStateMachine& sceneStateMachine)
    : sceneStateMachine(sceneStateMachine), continueSeconds(0.f), dialogueCounter(1), dialogueIndex(0)
{
	openingDialogue.push_back("Hero, the galaxy is in need of your help! "); 
	openingDialogue.push_back("Enemy ships and creatures are wrecking havoc in space."); 
	openingDialogue.push_back("Before facing the enemies however, you must destroy all the asteriods."); 
	openingDialogue.push_back("Navigate your ship by accelerating or deccelerating and steering right or left.");
	openingDialogue.push_back("Destroy enemies by firing your bullets with the SPACE key or A button on controller.");
	openingDialogue.push_back("Do not give up if the foe puts up a strong fight. Most enemies do not go down with a single bullet.");
	openingDialogue.push_back("Good luck, the galaxy is counting on you!");

}


void SceneExposition::OnActivate()
{
    continueSeconds = 0.f;
}


void SceneExposition::SetSwitchToScene(unsigned int id)
{
    switchToState = id;
}

void SceneExposition::Update(float deltaTime)
{
    continueSeconds += deltaTime;

	//If the opening dialogue has all been read, the time since the last read was 1 sec 
	//and the continue button has been pressed, we switch to next scene. 
    if ( (static_cast<float>(dialogueCounter) == openingDialogue.size()) && continueSeconds > 1.f && (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)))
    {
        sceneStateMachine.SwitchTo(switchToState);
    }
}

void SceneExposition::Draw()
{	
	App::Print(20.f, APP_INIT_WINDOW_HEIGHT / 1.5f, openingDialogue.at(dialogueIndex), 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);

	//Keeping track of time since last key was pressed ensures dialgoue is only progressed 
	//one line at a time. 
	if (continueSeconds > 1.f && (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))) 
	{
		//Protecting counter and index from being incremented past correct number
		if (dialogueIndex < openingDialogue.size())
		{
			dialogueIndex++;
			dialogueCounter++;
		}
		
		continueSeconds = 0.f; 
	}

	App::Print(20.f, 150.f, "Continue with Space on Keyboard and A on Controller", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);

}