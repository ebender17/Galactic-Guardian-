//------------------------------------------------------------------------
// Scene for main Gameplay.
//------------------------------------------------------------------------
#pragma once

#include "App/app.h"
#include "Enemy.h"
#include <vector>

class SceneStateMachine; 
class Protagonist; 
class Bullet; 

class SceneGame : public Scene
{
public:
    SceneGame(SceneStateMachine& sceneStateMachine);

    //Resets scene if scene has been activated before. 
    void OnActivate() override;
    //Deletes heap allocated objects when scene is removed from state machine. 
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void Draw() override; 
    void ResetGame(); 

    /*
   * Calculates velocity of player.
   * @param stateWon    id of scene to switch to when player wins
   * @param stateLost   id of scene to switch to when player dies 
   */
    void SetSwitchToScene(unsigned int stateWon, unsigned int stateLost);

    void AddAsteriods(); 

    //Used to calculate collisions
    bool IsPointInsideRange(float x1, float y1, float x2, float y2); 

    /*
   * Sets player state if enemy collision occurred 
   * @param enemPosX    enemy's x corrdinate
   * @param enemPosY    enemy's y coordinate
   * @param currEnem    enemy to check if it is close to player 
   */
    void CalculatePlayerState(float enemPosX, float enemPosY, std::unique_ptr<Enemy>& currEnem); 

    //Thw following generates enemies and resets stats for levels
    void CreateLevelTwo(); 
    void CreateLevelThree(); 

private:
    SceneStateMachine& sceneStateMachine;

    unsigned int activateCount; //number of times OnActivate has been called
    unsigned int switchToStateWon; //winning screen id, set in Game.cpp
    unsigned int switchToStateLost; //loosing screen id, set in Game.cpp

    float secPlayerDeath; //secs since player death, used to delay jump to next scene 
    float secEnemiesDead; //secs since enemies all destroyed, used to delay jump to next level or scene 

    Protagonist* player; //player's character
    std::vector<std::unique_ptr<Enemy>> enemies; 
    uint8_t playerState;
    uint8_t currLevel; //current level within SceneGame
    uint8_t numLevels; //number of levels within SceneGame
};

