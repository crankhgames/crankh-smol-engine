#pragma once

#include "Core/Layer.h"

class EditorLayer : public Core::Layer{
private:
    //void onMouseClick(const SDL_Event& event);
    //void onKeyboardPress(const SDL_Event& event);

public:
    bool onEvent(const SDL_Event& event) override;
    
    void onStart() override;
    void onUpdate(double ts) override;
    void onRender() override;

};