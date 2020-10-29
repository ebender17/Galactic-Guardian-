#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const char* enemType, int enemHealth, int enemDamage) 
{
	SpriteData large_asteriod = { ".\\TestData\\asteroid-01.bmp", 1, 1, 0, 3.f };
	SpriteData medium_asteriod = { ".\\TestData\\asteroid-02.bmp", 1, 1, 1, 3.f };
	SpriteData green_beetle = { ".\\TestData\\enemy-01.bmp", 5, 1, 0, 4.f, { 0, 1, 2, 3, 4  } };
	SpriteData blue_robot = { ".\\TestData\\enemy-02.bmp", 4, 1, 0, 4.f, { 0, 1, 2, 3  } };
	SpriteData flying_bug = { ".\\TestData\\enemy-03.bmp", 4, 1, 0, 4.f, { 0, 1, 2, 3  } };
	SpriteData large_enemy = { ".\\TestData\\enemy-big.bmp", 2, 1, 0, 4.f, { 0, 1 }, true };
	SpriteData medium_enemy = { ".\\TestData\\enemy-medium.bmp", 2, 1, 0, 4.f, { 0, 1 }, true};
	SpriteData small_enemy = { ".\\TestData\\enemy-small.bmp", 2, 1, 0, 5.f, { 0, 1 }, true };

	spriteMap = {
		{"large asteriod", large_asteriod},
		{"medium asteriod", medium_asteriod},
		{"green beetle", green_beetle},
		{"blue robot", blue_robot},
		{"flying bug", flying_bug},
		{"large enemy", large_enemy},
		{"medium enemy", medium_enemy},
		{"small enemy", small_enemy}
	}; 

	if (spriteMap.find(enemType) != spriteMap.end()) 
	{
		// Use random_device to generate a seed for Mersenne twister engine.
		// Use Mersenne twister engine to generate pseudo-random numbers.
		static thread_local std::mt19937_64 engine(std::random_device{}());
		minSpeed = { 30.f, 30.f }; 
		maxSpeed = { 40.f, 40.f }; 

		std::uniform_real_distribution<float> velocityRange(-30.f, 30.f);
		velocity = { velocityRange(engine), velocityRange(engine) };

		health = enemHealth;
		damage = enemDamage;
		secObjectHurt = 1.0f; 

		// "Filter" MT engine's output to generate pseudo-random double values,
		// **uniformly distributed** on the below closed intervals
		//Spawning enemies towards edges of screen 
		std::uniform_real_distribution<float> xDistribution(minPos.x, APP_INIT_WINDOW_WIDTH);
		std::uniform_real_distribution<float> yDistribution(-50.f, 150.f); 
		float x = xDistribution(engine); 
		float y = yDistribution(engine); 

		spriteEnemy = spriteMap.at(enemType);
		sprite = App::CreateSprite(spriteEnemy.filePath, spriteEnemy.nCols, spriteEnemy.nRows);
		sprite->SetPosition(x, y);
		sprite->SetFrame(spriteEnemy.staticFrame);
		sprite->SetScale(spriteEnemy.scale);

		if (!spriteEnemy.frames.empty())
		{
			sprite->CreateAnimation(ANIM_FLYING, 2.f/15.f, spriteEnemy.frames);
		}

		if (enemType == "large asteriod" || enemType == "medium asteriod")
		{
			enemyRotation = true; 
		}

		//Creating enemy explosion 
		enemyDeath = App::CreateSprite(".\\TestData\\enemy-explosion.bmp", 7, 1);
		enemyDeath->CreateAnimation(ANIM_DEFAULT, 2.f/15.f, { 0, 1, 2, 3, 4, 5, 6 });
		enemyDeath->SetScale(3.f);

	}

}

void Enemy::OnDestroy()
{
	delete sprite;
	delete enemyDeath; 
}

void Enemy::Update(float deltaTime)
{
	secObjectHurt += deltaTime;

	sprite->Update(deltaTime * 1000);
	sprite->SetAnimation(ANIM_FLYING);

	enemyDeath->Update(deltaTime * 1000);
	enemyDeath->SetPosition(-100.f, -100.f); //setting explosion sprite off screen while enemy is alive

	//Selecting behavior to play depending on if player was damaged or killed
	if (health == 0 && secObjectHurt < 0.5f)
	{
		float x, y;
		sprite->GetPosition(x, y);
		enemyDeath->SetPosition(x, y);
 		enemyDeath->SetAnimation(ANIM_DEFAULT);
		velocity = { 0.f, 0.f };

	}
	else if (health == 0 && secObjectHurt >= 0.5f)
	{
		//Enemy is placed off screen
		sprite->SetPosition(-100.f, -100.f); 
	}

	if (health > 0)
	{

		float x, y;
		sprite->GetPosition(x, y);
		
		if (std::abs(velocity.x) < minSpeed.x) velocity.x = minSpeed.x;
		if (std::abs(velocity.y) < minSpeed.x) velocity.y = minSpeed.y; 
		x += velocity.x * deltaTime;
		y += velocity.y * deltaTime;
		WrapCoordinates(x, y, x, y);
		sprite->SetPosition(x, y);

	}

	if (enemyRotation)
	{
		float a = sprite->GetAngle();
		a += 1.0f * deltaTime;
		sprite->SetAngle(a);

	}

}

void Enemy::Draw()
{
	sprite->Draw(); 
	enemyDeath->Draw(); 
}


