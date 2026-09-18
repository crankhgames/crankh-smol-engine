#include "EditorLayer.h"
#include "Core/App.h"

#include <print>

void EditorLayer::onStart(){
    std::println("Editor started...");
}
bool EditorLayer::onEvent(const SDL_Event& event){
    //switch (event.type){
    //case SDL_MOUSEBUTTONDOWN:
        //return true;
    //case SDL_KEYDOWN:
        //return true;
    //}

    return false;
}

void EditorLayer::onUpdate(double ts){

}

void EditorLayer::onRender(){

    SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0x50, 0x50, 0x50, SDL_ALPHA_OPAQUE);
    
    SDL_Rect rect {
        50, 50, 200, 200
    };
    SDL_Rect rect2 {
        700, 300, 200, 200
    };

    SDL_RenderFillRect(&GET_APPLICATION().getWindow().getRenderer(), &rect);
    SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0x50, 0x50, 0x50, 50);
    SDL_RenderFillRect(&GET_APPLICATION().getWindow().getRenderer(), &rect2);
    
}