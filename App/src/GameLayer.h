#pragma once

#include "Core/Layer.h"
#include "ECS/Scene.h"

class GameLayer : public Core::Layer{
private:

    Core::ECS::Scene gameScene{};

    void onMouseClick(const SDL_Event& event);
    void onKeyboardPress(const SDL_Event& event);

public:
    bool onEvent(const SDL_Event& event) override;
    
    void onStart() override;
    void onUpdate(double ts) override;
    void onRender() override;

    Core::ECS::Scene& getScene() {return gameScene;}

};