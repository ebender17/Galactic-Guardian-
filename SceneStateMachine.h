#pragma once
#include <memory>
#include <unordered_map>
#include "Scene.h"

//Simple Finite State Machine
class SceneStateMachine
{
public:
    SceneStateMachine();

    //Calls Update() of current scene 
    void Update(float deltaTime);

    //Calls Draw() of current scene 
    void Draw();

    //Add scene to FMS
    unsigned int Add(std::shared_ptr<Scene> scene);

    //Switch to scene, deactivate called on currScene and activate on next scene 
    void SwitchTo(unsigned int id);
    void Remove(unsigned int id);

private:
    std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> curScene;
    unsigned int insertedSceneID; //keeps track of scene ids, incremented when scene is added
};

