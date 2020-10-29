#pragma once

#include "App/app.h"
#include "SceneStateMachine.h"
#include "Protagonist.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

class SceneGame : public Scene
{
public:
    SceneGame(SceneStateMachine& sceneStateMachine);

    void OnActivate() override;
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void Draw() override; 
    void ResetGame(); 
    void SetSwitchToScene(unsigned int stateWon, unsigned int stateLost);

    void AddAsteriods(); 

    //Used to calculate bullet and enemy and enemy and player collisions
    bool IsPointInsideRange(float x1, float y1, float x2, float y2); 

    //Sets player state if enemy collision occurred 
    void CalculatePlayerState(float enemPosX, float enemPosY, std::unique_ptr<Enemy>& currEnem); 

    //Generates enemies and resets stats for levels
    void CreateLevelTwo(); 
    void CreateLevelThree(); 

    //Allows smart enemy to follow player within range
    void EnemyFollow(float enemPosX, float enemPoxY, std::unique_ptr<Enemy>& currEnem); 

    enum PlayerState {
        ALIVE, 
        HURT, 
        DEAD
    };

private:
    SceneStateMachine& sceneStateMachine;

    unsigned int activateCount; //number of times OnActivate has been called
    unsigned int switchToStateWon; //winning screen id, set in Game.cpp
    unsigned int switchToStateLost; //loosing screen id, set in Game.cpp

    float secPlayerDeath; //secs since player death, used to delay jump to next scene 
    float secEnemiesDead; //secs since enemies all destroyed, used to delay jump to next level or scene 

    Protagonist* player; //player's character
    std::vector<std::unique_ptr<Enemy>> enemies; 
    unsigned int playerState;
    unsigned int currLevel; //current level
    unsigned int numLevels; //number of game levels
};

