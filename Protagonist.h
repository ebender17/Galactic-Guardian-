//------------------------------------------------------------------------
// Player character 
//------------------------------------------------------------------------
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

	/*
   * Calculates velocity of player.  
   * @param deltaTime  time passed since last frame
   */
	void Thrust(float deltaTime); 

	/*
   * Slows player movement. 
   * @param deltaTime  time passed since last frame
   */
	void Deceleration(float deltaTime); 

	/*
   * Updates player's position based on calculated velocity in Thrust. 
   * @param deltaTime  time passed since last frame
   */
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
	CSimpleSprite* playerHurt; //sprite placed on top of player sprite when player is damaged

	float secFireBullet; //secs since the player has fired a bullet
	float currentSeconds; //seconds since object was instantiated
};