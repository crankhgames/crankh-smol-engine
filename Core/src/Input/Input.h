#pragma once

#include "SDL2/SDL.h"
#include "Math/Math.h"

namespace Core::Input {
    
    bool getKeyPressed(SDL_Scancode scancode);
    
    Math::Vec2 getMousePosition();

    bool getMousePressed(int mouseButton);

}