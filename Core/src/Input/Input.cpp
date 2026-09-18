#include "Input.h"


namespace Core::Input
{
    bool getKeyPressed(SDL_Scancode scancode){
        return SDL_GetKeyboardState(NULL)[scancode];
    }

    Math::Vec2 getMousePosition(){
        int mouseX{};
        int mouseY{};
        SDL_GetMouseState(&mouseX, &mouseY);
        return Math::Vec2{static_cast<double>(mouseX), static_cast<double>(mouseY)};
    }
    
    bool getMousePressed(int mouseButton){
        return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(mouseButton);
    }

} 
