//------------------------------------------------------------------------
// Simple Finite State Machine
//------------------------------------------------------------------------
#pragma once
#include <memory>
#include <unordered_map>
#include "Scene.h"

class SceneStateMachine
{
public:
    SceneStateMachine();

    /*
    * Calls Update of active scene in State Machine. 
    * @param deltaTime  time passed since last frame 
    */
    void Update(float deltaTime);

    /*
    * Calls Draw of active scene in State Machine.
    */
    void Draw();

    /*
    * Adds scene to Finite State Machine.
    * @param scene Scene to add to FMS. 
    */
    unsigned int Add(std::shared_ptr<Scene> scene);

    /*
    * Switch to scence. Deactive called on current scene and active on next scene. 
    * @param id Scene id to switch to. 
    */
    void SwitchTo(unsigned int id);

    /*
    * Remove scene from Scene State Machine. 
    * @param id Scene id to remove to.
    */
    void Remove(unsigned int id);

private:
    std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> curScene;
    unsigned int insertedSceneID; //Counter for current scene ids. Incremented when scene is added.
};

