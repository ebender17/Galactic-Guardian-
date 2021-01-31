//------------------------------------------------------------------------
// Enemy Character 
//------------------------------------------------------------------------
#pragma once
#include "GameObject.h"

class Protagonist;

class Enemy : public GameObject
{
public:
	//Generates different sprites based on enemy type (enemType) 
	Enemy(const char* enemType, int enemHealth, int enemDamage);

	virtual void OnDestroy() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	
	//Returns true if enemy is smart (allows one to implement more advanced behavior if wanted)
	bool GetSmartEnemy()
	{
		return spriteEnemy.smartEnemy; 
	}

	void EnemyFollow(Protagonist* player, uint8_t playerState);

private: 
	bool enemyRotation = false; //Sets to true if enemy should rotate 

	struct SpriteData {
		const char* filePath;
		int nCols;
		int nRows;
		int staticFrame;
		float scale;
		std::vector<int> frames;
		bool smartEnemy = false;
	};

	SpriteData spriteEnemy;

	//Collection of sprite names and sprite data 
	std::unordered_map<const char*, SpriteData> spriteMap;

	//Enemy explosion sprite
	CSimpleSprite* enemyDeath; 
	
};

