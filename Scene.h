#pragma once
class Scene
{
public:
    virtual void OnCreate() {}; // Called by FMS when scene initially created. Called once per scene. 
    virtual void OnDestroy() {}; // Called by FMS when scene destroyed. Called once per scene.

    virtual void OnActivate() {}; // Called whenever a scene is switched into by FMS.
    virtual void OnDeactivate() {}; // Called whenever a scene is switch out off by FMS.


    //Made pure virtual functions so subclass must instantiate
    //These functions need to be called to update and render objects to screen 
    virtual void Update(float deltaTime) = 0; 
    virtual void Draw() = 0;

};

