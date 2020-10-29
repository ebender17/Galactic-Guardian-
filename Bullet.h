#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public: 
	//Pass in owner's angle, x and y positions
	Bullet(float angleOwner, float xOwner, float yOwner); 

	virtual void OnDestroy() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

};
