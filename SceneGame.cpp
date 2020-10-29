#include "stdafx.h"
#include "SceneGame.h"

SceneGame::SceneGame(SceneStateMachine& sceneStateMachine) 
	: sceneStateMachine(sceneStateMachine), activateCount(0),currLevel(1), numLevels(3), playerState(ALIVE), secPlayerDeath(0.f), secEnemiesDead(0.f)
{
	player = new Protagonist();

	float x, y;
	player->GetSpritePosition(x, y);

	AddAsteriods(); 
} 

void SceneGame::OnActivate()
{
	//Want to reset game if scene has been activated before
	if (activateCount > 0)
	{
		ResetGame(); 
	}
	
	activateCount++; 
	
}

void SceneGame::OnDestroy()
{
	player->OnDestroy(); //deletes player sprite and player explosion CSimpleSprite ptrs
	delete player;

}

void SceneGame::SetSwitchToScene(unsigned int stateWon, unsigned int stateLost)
{
	switchToStateWon = stateWon; 
	switchToStateLost = stateLost;
}
void SceneGame::AddAsteriods()
{
	for (int i = 0; i < 6; i++)
	{
		enemies.push_back(std::make_unique<Enemy>("large asteriod", 40, 500));
		enemies.push_back(std::make_unique<Enemy>("medium asteriod", 20, 200));
	}
}


bool SceneGame::IsPointInsideRange(float x1, float y1, float x2, float y2)
{
	//If distance between points is less than 50.f, points are deemed inside each other's range 
	return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < 50.f;
}

void SceneGame::EnemyFollow(float enemPosX, float enemPosY, std::unique_ptr<Enemy>& currEnem)
{
	Vector2 playerPos; 
	player->GetSpritePosition(playerPos.x, playerPos.y); 
	
	float distanceX = playerPos.x - enemPosX; 
	float distanceY = playerPos.y - enemPosY; 
	float distance = sqrtf((distanceX * distanceX) + (distanceY * distanceY)); 

	float vx, vy;
	if (distance < 250.f && playerState == ALIVE)
	{
		//normalizing difference to receive unit vector for velocity, 50.f is the speed here
		vx = (distanceX / distance) * 50.f; 
		vy = (distanceY / distance) * 50.f; 
		currEnem->SetVelocity(vx, vy);
	}

}

void SceneGame::ResetGame()
{
		player->SetSpritePosition(APP_INIT_WINDOW_WIDTH / 2.f, APP_INIT_WINDOW_HEIGHT / 2.f); 
		player->SetHealth(1000); 
		player->SetObjectHurt(2.f); //Set to 2.f bc before 1.f player has an explosion sprite set on top
		player->SetCurrentSeconds(0.f); //Ensures Space key or A button press from previous scene does not trigger bullet fire, bullet fires after currSec > 2.0f
	
		player->ClearBullets(); 
		player->SetVelocity(0.f, 0.f);
		enemies.clear(); 

		//Know I just set position so should know position, but want as accurate as can be for placing enemies below
		float xPlayer, yPlayer;
		player->GetSpritePosition(xPlayer, yPlayer);

		AddAsteriods(); 

		playerState = ALIVE; 
		currLevel = 1; 
		secPlayerDeath = 0.f; 
		secEnemiesDead = 0.f; 

	
}

void SceneGame::CalculatePlayerState(float enemPosX, float enemPoxY, std::unique_ptr<Enemy>& currEnem)
{
	float px, py;
	player->GetSpritePosition(px, py);

	int health = player->GetHealth(); 

	if (IsPointInsideRange(enemPosX, enemPoxY, px, py))
	{
		/*if (health <= 0)
		{
			playerState = DEAD;
			return;
		}*/

		if (playerState == ALIVE)
		{
			health -= currEnem->GetDamage();
			if (health <= 0)
			{
				health = 0;
				playerState = DEAD;
				player->SetHealth(health);
				player->SetObjectHurt(0.f);
				return;
			} 

			playerState = HURT;
			player->SetObjectHurt(0.f); 
			player->SetHealth(health);
		}	

	}

}


void SceneGame::CreateLevelTwo()
{
	//Reseting player status bc beginning of round
	float xPlayer, yPlayer; 
	player->GetSpritePosition(xPlayer, yPlayer); 
	player->SetSpritePosition(APP_INIT_WINDOW_WIDTH / 2.f, APP_INIT_WINDOW_WIDTH / 2.f);
	player->SetVelocity(0.f, 0.f); 
	player->SetSpriteAngle(0.f); 

	for (int i = 0; i < 3; i++) 
	{
		enemies.push_back(std::make_unique<Enemy>("green beetle", 40, 200));
		enemies.push_back(std::make_unique<Enemy>("blue robot", 60, 400));
		enemies.push_back(std::make_unique<Enemy>("flying bug", 20, 300));
	}

	currLevel += 1; 
	player->SetHealth(1000); 
}

void SceneGame::CreateLevelThree()
{
	float xPlayer, yPlayer;
	player->GetSpritePosition(xPlayer, yPlayer);
	player->SetSpritePosition(APP_INIT_WINDOW_WIDTH / 2.f, APP_INIT_WINDOW_WIDTH / 2.f);
	player->SetVelocity(0.f, 0.f);
	player->SetSpriteAngle(0.f);

	for (int i = 0; i < 2; i++)
	{
		enemies.push_back(std::make_unique<Enemy>("small enemy", 40, 100));
		enemies.push_back(std::make_unique<Enemy>("medium enemy", 60, 200));
		enemies.push_back(std::make_unique<Enemy>("large enemy", 80, 200));
	}

	currLevel += 1;
	player->SetHealth(1000);
}



void SceneGame::Update(float deltaTime)
{
	player->Update(deltaTime);
	std::vector<std::unique_ptr<Bullet>>& bullets = player->GetBullets();

	//Lost Game
	if (playerState == DEAD)
	{
		secPlayerDeath += deltaTime; 
		if(secPlayerDeath > 1.f) sceneStateMachine.SwitchTo(switchToStateLost);
	}

	//2nd round of enemies, this time ships!
	if (enemies.empty() && currLevel == numLevels - 2 ) 
	{
		secEnemiesDead += deltaTime; 
		if (secEnemiesDead > 4.f) {
			secEnemiesDead = 0.f; 
			CreateLevelTwo();
		}
	} 

	//3rd round, smart enemies
	if (enemies.empty() && currLevel == numLevels - 1)
	{
		secEnemiesDead += deltaTime;
		if (secEnemiesDead > 3.f) {
			secEnemiesDead = 0.f;
			CreateLevelThree();
		}

	}

	//Won game 
	if (enemies.empty() &&currLevel == numLevels) {
		secEnemiesDead += deltaTime; 
		if(secEnemiesDead > 3.f) sceneStateMachine.SwitchTo(switchToStateWon);
	}

	if (player->GetObjectHurt() > 3.f) playerState = ALIVE; 

	//Update and draw enemies
	for (auto& e : enemies)
	{
		e->Update(deltaTime);

		//Grab enemies position
		float ex, ey;
		e->GetSpritePosition(ex, ey);

		//Check for bullet and enemy collision
		for (auto& b : bullets) 
		{
			//Grab bullets position
			float bx, by; 
			b->GetSpritePosition(bx, by);

			if (IsPointInsideRange(bx, by, ex, ey))
			{
				if (e->GetObjectHurt() > 1.f)
				{
					int health = e->GetHealth(); 
					health -= b->GetDamage(); 
					e->SetHealth(health);
					//sec since enemy was last hurt set to 0
					e->SetObjectHurt(0.f); 
				}
				//Force bullet offscreen to be collected by remove_if lambda in protagonist.cpp
				b->SetSpritePosition(2000.f, 2000.f);
			}

		}

		if (e->GetSmartEnemy()) EnemyFollow(ex, ey, e); //if smart enemy, allow enemy to follow player inside range


		//Check for enemy collisons with player
		CalculatePlayerState(ex, ey, e); 

	}

	//Remove enemies that have gone off screen
	//In enemy.cpp, enemies are forced off screen if health == 0
	if (enemies.size() > 0)
	{
		//remove_if from c algorithm library 
		//Returns iterator 
		//Sorts vector that anything that fails criteria is at end of vector 
		auto i = remove_if(enemies.begin(), enemies.end(), [&](std::unique_ptr<Enemy>& enemy)
			{
				float x, y;
				enemy->GetSpritePosition(x, y);
				return (x < -10.f);
			}
		);
		if (i != enemies.end())
			//delete unique ptr will be called automatically once vector no longer owns it  
			enemies.erase(i);
	}
	
}

void SceneGame::Draw()
{
	//Health display
	int health = player->GetHealth(); 
	std::string playerHealth = "Player health: " + std::to_string(health); 
	const char* cPlayerHealth = playerHealth.c_str(); 

	float r = 0.f, b = 0.f, g = 1.f; 
	if (health <= 500)
	{
		r = 0.5f;
		g = 0.5f;
	}
	if (health <= 200)
	{
		r = 1.f; 
		g = 0.f; 
	}

	App::Print( 50.f, APP_INIT_WINDOW_HEIGHT - 50.f, cPlayerHealth, r, g, b, GLUT_BITMAP_9_BY_15);

	//Display text after level 1 is complete
	if (enemies.empty() && currLevel == numLevels - 2 && secEnemiesDead < 4.f)
	{
		App::Print(APP_INIT_WINDOW_WIDTH / 2.5f, APP_INIT_WINDOW_HEIGHT / 1.5f, "Level 1: Complete", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);
		App::Print(APP_INIT_WINDOW_WIDTH / 2.75f, APP_INIT_WINDOW_HEIGHT / 2.f, "Level 2: Alien Creatures", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);
	}

	//Display text after level 2 is complete
	if (enemies.empty() && currLevel == numLevels - 1 && secEnemiesDead < 4.f)
	{
		App::Print(APP_INIT_WINDOW_WIDTH / 2.5f, APP_INIT_WINDOW_HEIGHT / 1.5f, "Level 2: Complete", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);
		App::Print(APP_INIT_WINDOW_WIDTH / 2.75f, APP_INIT_WINDOW_HEIGHT / 2.f, "Level 3: Invading Enemy Ships", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);

	}

	//Display text after level 3 is complete
	if (enemies.empty() && currLevel == numLevels && secEnemiesDead < 3.f && playerState != DEAD) 
	{
		App::Print(APP_INIT_WINDOW_WIDTH / 2.5f, APP_INIT_WINDOW_HEIGHT / 1.5f, "Level 3: Complete", 0.2f, 0.5f, 0.75f, GLUT_BITMAP_9_BY_15);
	}
	

	//Drawing game objects
	player->Draw(); 

	for (auto& e : enemies) 
	{
		e->Draw(); 

	}
}