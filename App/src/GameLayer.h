#pragma once

#include "Core/Layer.h"
#include "ECS/Scene.h"

class GameLayer : public Core::Layer{
private:

    Core::ECS::Scene gameScene{};

    void onMouseClick(const SDL_Event& event);
    void onKeyboardPress(const SDL_Event& event);

public:
    virtual void onEvent(const SDL_Event& event);
    
    virtual void onStart() override;
    virtual void onUpdate(double ts) override;
    virtual void onRender() override;

};