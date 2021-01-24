//------------------------------------------------------------------------
// Interface for all game objects. 
//------------------------------------------------------------------------
#pragma once

#include "App/app.h"

class GameObject
{
protected:
	CSimpleSprite* sprite;

	//Min pos for sprite to appear more fully on screen when spawned 
	Vector2 minPos = { 50.f, 150.f }; 

	Vector2 velocity = { 0.f, 0.f };
	Vector2 maxSpeed = { 0.f, 0.f };
	Vector2 minSpeed = { 0.f, 0.f };
	float drag = 0.f;

	int health = 0; 
	int damage = 0; 

	float secObjectHurt; //seconds since object was last hurt


public: 
	virtual void OnDestroy() {};
	virtual void Update(float deltaTime) {};
	virtual void Draw() {};

	/*
   * Wraps player's coordinates around screen ensuring player never goes off screen.
   * @param x	player's current x coordinate
   * @param y	player's current y coordinate
   * @param ox	output with player's new x coordinate
   * @param oy	output with player's new y coordinate
   */
	void WrapCoordinates(float x, float y, float& ox, float& oy)
	{
		ox = x;
		oy = y;
		if (x < -10.f) ox = x + (float)APP_INIT_WINDOW_WIDTH;
		if (x >= (float)APP_INIT_WINDOW_WIDTH + 10.f) ox = x - (float)APP_INIT_WINDOW_WIDTH;
		if (y < -50.f) oy = y + (float)APP_INIT_WINDOW_HEIGHT;
		if (y >= (float)APP_INIT_WINDOW_HEIGHT + 10.f) oy = y - (float)APP_INIT_WINDOW_HEIGHT;
	};
	
	//Following are Getters and Setters for Game Object members. 
	float GetObjectHurt()
	{
		return secObjectHurt;
	}

	void SetObjectHurt(float sec)
	{
		secObjectHurt = sec;
	}

	int GetDamage()
	{
		return damage;
	};

	void SetDamage(int d)
	{
		damage = d; 
	}

	int GetHealth()
	{
		return health;
	};

	void SetHealth(int h)
	{
		health = h; 
	};

	Vector2 GetVelocity() 
	{
		return velocity; 
	};

	void SetVelocity(float nx, float ny)
	{
		velocity.x = nx;
		velocity.y = ny;
	};

	void GetSpritePosition(float& ox, float& oy)
	{
		float x, y;
		sprite->GetPosition(x, y);
		ox = x;
		oy = y;
	}

	void SetSpritePosition(float x, float y)
	{
		sprite->SetPosition(x, y);
	}

	float GetSpriteAngle()
	{
		return sprite->GetAngle(); 
	}

	void SetSpriteAngle(float a)
	{
		sprite->SetAngle(a); 
	}

};

