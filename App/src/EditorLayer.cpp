#include "EditorLayer.h"
#include "Core/App.h"
#include "UI/Text.h"
#include "UI/UIContainer.h"

#include <print>
#include <iostream>


namespace Variables {
    //Core::UI::Text text {"Hello world", 20, "assets/fonts/Roboto-Medium.ttf", SDL_Color {255, 0, 255, SDL_ALPHA_OPAQUE}};
    Core::UI::UIContainer uiContainer {};
};

void EditorLayer::onStart(){
    std::unique_ptr<Core::UI::Text> text1 {new Core::UI::Text{Core::Math::Vec2Int{50, 50}, Core::Math::Vec2Int{300, 100}, "Hello World", 200, "assets/fonts/Roboto-Medium.ttf", {255, 0, 0, SDL_ALPHA_OPAQUE}}};
    std::unique_ptr<Core::UI::Text> text2 {new Core::UI::Text{Core::Math::Vec2Int{50, 50}, Core::Math::Vec2Int{200, 50}, "Sorry bro", 100, "assets/fonts/Roboto-Medium.ttf", {255, 0, 0, SDL_ALPHA_OPAQUE}}};

    Variables::uiContainer.add(std::move(text1));
    Variables::uiContainer.add(std::move(text2));
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

    Variables::uiContainer.render();
    
}