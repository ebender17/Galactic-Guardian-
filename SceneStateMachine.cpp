#include "stdafx.h"
#include "SceneStateMachine.h"

SceneStateMachine::SceneStateMachine() : scenes(0), curScene(0) { }

void SceneStateMachine::Update(float deltaTime)
{
    if (curScene)
    {
        curScene->Update(deltaTime);
    }
}


void SceneStateMachine::Draw()
{
    if (curScene)
    {
        curScene->Draw();
    }
}

unsigned int SceneStateMachine::Add(std::shared_ptr<Scene> scene)
{
    auto inserted = scenes.insert(std::make_pair(insertedSceneID, scene));

    inserted.first->second->OnCreate();

    return insertedSceneID++;
}

void SceneStateMachine::Remove(unsigned int id)
{
    auto it = scenes.find(id);
    if (it != scenes.end())
    {
        if (curScene == it->second)
        {
            curScene = nullptr;
        }

        it->second->OnDestroy();

        scenes.erase(it);
    }
}

void SceneStateMachine::SwitchTo(unsigned int id)
{
    auto it = scenes.find(id);
    if (it != scenes.end())
    {
        if (curScene)
        {
            curScene->OnDeactivate();
        }

        curScene = it->second;

        curScene->OnActivate();
    }
}