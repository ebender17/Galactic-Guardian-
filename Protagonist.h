#pragma once

#include "GameObject.h"
#include "Bullet.h"
#include <algorithm>
#include <memory>

class Protagonist : public GameObject
{
public: 
	Protagonist(); 

	virtual void OnDestroy() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void Thrust(float deltaTime); 
	void Deceleration(float deltaTime); 
	void UpdatePosition(float deltaTime); 

	std::vector<std::unique_ptr<Bullet>>& GetBullets()
	{
		return bullets;
	};

	void ClearBullets()
	{
		bullets.clear(); 
	}; 

	void SetCurrentSeconds(float sec)
	{
		currentSeconds = sec; 
	}

private: 
	std::vector<std::unique_ptr<Bullet>> bullets; 
	CSimpleSprite* playerHurt; //sprite placed on top of player sprite when hurt

	float secFireBullet; //secs since the player has fired a bullet
	float currentSeconds; //Seconds since object was instantiated
};