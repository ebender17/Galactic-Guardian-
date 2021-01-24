//------------------------------------------------------------------------
// Interface for game scenes. 
//------------------------------------------------------------------------
#pragma once
class Scene
{
public:
    // Called by FMS when scene initially created. Called once per scene. 
    virtual void OnCreate() {}; 
    // Called by FMS when scene destroyed. Called once per scene.
    virtual void OnDestroy() {}; 

    // Called whenever a scene is switched into by FMS.
    virtual void OnActivate() {}; 
    // Called whenever a scene is switch out off by FMS.
    virtual void OnDeactivate() {}; 

    /*
    * Update and Draw made pure virtual functions to ensure every scene implements. 
    * These functions need to be called to update and render objects to screen.
    */
    virtual void Update(float deltaTime) = 0; 
    virtual void Draw() = 0;

};

