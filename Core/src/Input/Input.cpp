#include "Input.h"
#include "Core/App.h"


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

    Math::Vec2 getUVMousePosition(){
        int mouseX{};
        int mouseY{};
        SDL_GetMouseState(&mouseX, &mouseY);
        Math::Vec2 windowSize {GET_APPLICATION().getWindow().getWindowSize()};
        return Math::Vec2{mouseX / windowSize.getX(), mouseY / windowSize.getY()} - Math::Vec2{.5, .5};
    }
    
    bool getMousePressed(int mouseButton){
        return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(mouseButton);
    }

} 
