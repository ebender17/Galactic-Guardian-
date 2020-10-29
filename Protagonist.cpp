#include "stdafx.h"
#include "Protagonist.h"

Protagonist::Protagonist() : secFireBullet(0.f), currentSeconds(0.f)
{
	secObjectHurt = 2.f; //Set to 2.f to be safe bc object behaves differently after it has been 4 secs since object was hurt. Want default anim to play on instantiation. 
	health = 1000; 
	velocity = { 1.f, -1.f };
	minSpeed = { 0.001f, 0.001f };
	maxSpeed = { 50.f, 50.f };
	drag = 0.98f;

	sprite = App::CreateSprite(".\\TestData\\ship.bmp", 5, 2);
	sprite->SetPosition(APP_INIT_WINDOW_WIDTH / 2.f, APP_INIT_WINDOW_HEIGHT / 2.f);
	float speed = 2.f / 15.f;
	sprite->CreateAnimation(ANIM_FLYING, speed, { 0, 1, 2, 3, 4, 5, 6, 7});
	sprite->SetScale(3.f);

	playerHurt = App::CreateSprite(".\\TestData\\explosion.bmp", 5, 1); 
	playerHurt->CreateAnimation(ANIM_DEFAULT, speed, { 0, 1, 2, 3, 4 });
	playerHurt->SetScale(3.f);

}


void Protagonist::OnDestroy()
{
	delete sprite; 
	delete playerHurt; 

}

void Protagonist::Thrust(float deltaTime)
{
	// Acceleration changes velocity (with respect to time) 
	float a = sprite->GetAngle();
	velocity.x += -sinf(a) * 50.f * deltaTime;
	velocity.y += cosf(a) * 50.f * deltaTime;

	//Limit max velocity 
	if (std::abs(velocity.x) > maxSpeed.x)
	{
		velocity.x = maxSpeed.x * ((velocity.x < 0.f) ? -1.f : 1.f);
	}
	if (std::abs(velocity.y) > maxSpeed.y)
	{
		velocity.y = maxSpeed.y * ((velocity.y < 0.f) ? -1.f : 1.f);
	}


}

void Protagonist::Deceleration(float deltaTime)
{
	//Deceleration 
	velocity.x *= drag;
	velocity.y *= drag;

	//Limit min velocity (deceleration), allows player to come to complete stop when near 0
	if (std::abs(velocity.x) < minSpeed.x)
		velocity.x = 0.f;
	if (std::abs(velocity.y) < minSpeed.y)
		velocity.y = 0.f;

}

void Protagonist::UpdatePosition(float deltaTime)
{
	// Velocity changes position 
	float x, y;
	sprite->GetPosition(x, y);
	x += velocity.x * deltaTime;
	y += velocity.y * deltaTime;

	//Wrap player around screen
	WrapCoordinates(x, y, x, y);
	sprite->SetPosition(x, y);

}

void Protagonist::Update(float deltaTime)
{
	
	sprite->Update(deltaTime * 1000);
	playerHurt->Update(deltaTime * 1000); 

	sprite->SetAnimation(ANIM_FLYING);
	playerHurt->SetPosition(-100.f, -100.f); //Setting offscreen when player is not hurt

	secFireBullet += deltaTime;
	secObjectHurt += deltaTime;
	currentSeconds += deltaTime; 
	
	//Selecting behavior to play depending on if player was damaged or killed
	if (secObjectHurt > 0.f && secObjectHurt <= 0.5f)
	{
		float x, y;
		sprite->GetPosition(x, y); 
		playerHurt->SetPosition(x, y); 
		playerHurt->SetAnimation(ANIM_DEFAULT);

		velocity = { 0.f, 0.f };

	}
	else if (secObjectHurt > 0.5f && secObjectHurt < 1.f && health > 0)
	{
		float newX = APP_INIT_WINDOW_WIDTH / 2.f;
		float newY = 50.f;
		sprite->SetPosition(newX, newY);
		sprite->SetAngle(0.f);
	} 
	else if (secObjectHurt > 0.5f && health <= 0)
	{
		playerHurt->SetAnimation(ANIM_DEFAULT);
	}


	//Steer Right
	if (health > 0 && secObjectHurt > 1.f && App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		float a = sprite->GetAngle();
		a += 5.0f * deltaTime;
		sprite->SetAngle(a);

	}
	//Steer Left
	if (health > 0 && secObjectHurt > 1.f && App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		float a = sprite->GetAngle();
		a -= 5.0f * deltaTime;
		sprite->SetAngle(a);

	}
	//Thrust
	if (health > 0 && secObjectHurt > 1.f && App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		Thrust(deltaTime); 
	}
	//Deceleration 
	if (health > 0 && secObjectHurt > 1.f && App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		Deceleration(deltaTime);
	}
	//Bullets 
	//Only fire a bullet every second to ensure bullets do not bleed together (secFireBullet > 1.f)
	//SPACE key or A button press from previus scene does not trigger bullet to fire (deltaTime > 2.f)
	if (health > 0 && secObjectHurt > 1.f && secFireBullet > 1.f && currentSeconds > 2.f && (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)))
	{
		float angle = sprite->GetAngle();
		float x, y; 
		sprite->GetPosition(x, y); 
		x += 10.f; 
		y += 10.f; 
		bullets.push_back(std::make_unique<Bullet>(angle, x, y));

		secFireBullet = 0.f; 
	}

	UpdatePosition(deltaTime); 


	//Update bullets position 
	for (auto& b : bullets)
	{
		b->Update(deltaTime); 
	}

	// Remove bullets that have gone off screen
	if (bullets.size() > 0)
	{
		//Given iterator that does not pass return statement 
		auto i = remove_if(bullets.begin(), bullets.end(), [&](std::unique_ptr<Bullet>& bullet) 
			{ 
				float x, y;
				bullet->GetSpritePosition(x, y); 
				return ( x < 1.f || y < 1.f || x >= APP_INIT_WINDOW_WIDTH - 1.f || y >= APP_INIT_WINDOW_HEIGHT - 1.f);
			}
		);
		if (i != bullets.end())
			bullets.erase(i);
	}


}

void Protagonist::Draw()
{
	sprite->Draw(); 

	playerHurt->Draw(); 

	for (auto& b : bullets)
	{
		b->Draw();

	}
}