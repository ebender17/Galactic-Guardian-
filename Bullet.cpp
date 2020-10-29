#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(float aOwner, float xOwner, float yOwner)
{
	velocity = { 10.f, -10.f };
	damage = 20; 

	sprite = App::CreateSprite(".\\TestData\\laser-bolts.bmp", 2, 2);
	float speed = 0.5f / 15.f;
	sprite->CreateAnimation(ANIM_DEFAULT, speed, { 0, 1, 2, 3, 4 });
	sprite->SetFrame(0);
	sprite->SetPosition(xOwner, yOwner);
	sprite->SetAngle(aOwner); 
	sprite->SetScale(5.f);

}

void Bullet::OnDestroy()
{
	delete sprite; 

}

void Bullet::Update(float deltaTime)
{
	sprite->Update(deltaTime * 1000); 
	sprite->SetAnimation(ANIM_DEFAULT); 

	float x, y;
	sprite->GetPosition(x, y);

	float a = sprite->GetAngle(); 
	velocity.x = 300.f * -sinf(a);
	velocity.y = 300.f * cosf(a);

	x += velocity.x * deltaTime;
	y += velocity.y * deltaTime;
	WrapCoordinates(x, y, x, y);
	sprite->SetPosition(x, y);
}

void Bullet::Draw()
{
	sprite->Draw(); 

}

