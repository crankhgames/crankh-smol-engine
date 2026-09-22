#include "EditorLayer.h"
#include "Core/App.h"
#include "UI/Text.h"
#include "UI/UiContainer.h"
#include "UI/UiManager.h"

#include <print>
#include <iostream>


namespace Variables {
    //Core::UI::Text text {"Hello world", 20, "assets/fonts/Roboto-Medium.ttf", SDL_Color {255, 0, 255, SDL_ALPHA_OPAQUE}};
    std::unique_ptr<Core::UI::UiContainer> uiContainer {Core::UI::createContainer(false)};
};


void EditorLayer::onStart(){

    Core::UI::attachUiElementToContainer<Core::UI::Text>(Variables::uiContainer.get(), 
        Core::Math::Vec2Int{50, 50},
        Core::Math::Vec2Int{300, 100},
        "Hello World",
        200,
        "assets/fonts/Roboto-Medium.ttf",
        SDL_Color {255, 0, 0, SDL_ALPHA_OPAQUE}
    );

    Core::UI::attachUiElementToContainer<Core::UI::Text>(Variables::uiContainer.get(),
        Core::Math::Vec2Int{50, 50},
        Core::Math::Vec2Int{200, 50},
        "Sorry bro",
        100,
        "assets/fonts/Roboto-Medium.ttf",
        SDL_Color {255, 0, 0, SDL_ALPHA_OPAQUE}
    );

    Core::UI::attachUiElementToContainer<Core::UI::Text>(Variables::uiContainer.get(),
        Core::Math::Vec2Int{50, 50},
        Core::Math::Vec2Int{200, 300},
        "Sorry bro",
        300,
        "assets/fonts/Roboto-Medium.ttf",
        SDL_Color {0, 0, 0, SDL_ALPHA_OPAQUE}
    );
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

    Variables::uiContainer->render();
    
}