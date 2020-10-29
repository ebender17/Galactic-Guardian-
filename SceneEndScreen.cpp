#include "stdafx.h"
#include "SceneEndScreen.h"

SceneEndScreen::SceneEndScreen()
{

}


void SceneEndScreen::Update(float deltaTime)
{
   
}

void SceneEndScreen::Draw()
{
	static float winHeight = (APP_INIT_WINDOW_HEIGHT / 2.f);
	winHeight += 0.50f; 

	//Once last text goes off screen reset to bottom of window 
	if (winHeight > APP_INIT_WINDOW_HEIGHT + 100.f)
	{
		winHeight = 0.f; 
	}

	float r = (float)rand() / RAND_MAX;
	float g = (float)rand() / RAND_MAX;
	float b = (float)rand() / RAND_MAX;

	App::Print(APP_INIT_WINDOW_WIDTH / 2.25f , winHeight, "You won!", r, g, b, GLUT_BITMAP_9_BY_15);
	App::Print(APP_INIT_WINDOW_WIDTH / 3.00f, winHeight - 50.f, "You have saved the galaxy from evil doers.", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);
	App::Print(APP_INIT_WINDOW_WIDTH / 2.5f, winHeight - 100.f, "Thanks for playing!", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);

	App::Print(APP_INIT_WINDOW_WIDTH / 3.25f, winHeight - 150.f, "Art done by Luis Zuno, @ansimuz on Twitter", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);




}