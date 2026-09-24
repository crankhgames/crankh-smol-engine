#include "EditorLayer.h"
#include "Core/App.h"
#include "UI/Text.h"
#include "UI/UiContainer.h"
#include "UI/UiManager.h"
#include "UI/Button.h"

#include <print>
#include <functional>


namespace Variables {
    //Core::UI::Text text {"Hello world", 20, "assets/fonts/Roboto-Medium.ttf", SDL_Color {255, 0, 255, SDL_ALPHA_OPAQUE}};
    std::unique_ptr<Core::UI::UiContainer> uiContainer {Core::UI::createContainer(true, 50)};
};


void EditorLayer::onStart(){

    Variables::uiContainer->setPosition({50, 50});


    Core::UI::attachUiElementToContainer<Core::UI::Text>(Variables::uiContainer.get(), 
        "Main Container",
        75,
        "assets/fonts/Roboto-Medium.ttf"
    );

    Core::UI::attachUiElementToContainer<Core::UI::Text>(Variables::uiContainer.get(),
        "Section 1",
        50,
        "assets/fonts/Roboto-Medium.ttf"
    );

    std::unique_ptr<Core::UI::UiContainer> settingsContainer {Core::UI::createContainer(false, 10)};

    Core::UI::attachUiElementToContainer<Core::UI::Button>(settingsContainer.get(),
        Core::Math::Vec2Int{75, 50},
        SDL_Color {0, 150, 150, SDL_ALPHA_OPAQUE},
        [](){
            std::println("Button 1 clicked!");
        }
    );

    Core::UI::attachUiElementToContainer<Core::UI::Button>(settingsContainer.get(),
        Core::Math::Vec2Int{75, 50},
        SDL_Color {150, 0, 150, SDL_ALPHA_OPAQUE},
        [](){
            std::println("Button 2 clicked!");
        }
    );

    Core::UI::attachUiElementToContainer<Core::UI::Button>(settingsContainer.get(),
        Core::Math::Vec2Int{75, 50},
        SDL_Color {150, 150, 0, SDL_ALPHA_OPAQUE},
        [](){
            std::println("Button 3 clicked!");
        }
    );

    Core::UI::attachUiElementToContainer<Core::UI::UiContainer>(Variables::uiContainer.get(), std::move(settingsContainer));

    std::println("Editor started...");
}
bool EditorLayer::onEvent(const SDL_Event& event){
    //switch (event.type){
    //case SDL_MOUSEBUTTONDOWN:
        //return true;
    //case SDL_KEYDOWN:
        //return true;
    //}

    return Variables::uiContainer->onEvent(event);
}

void EditorLayer::onUpdate(double ts){

}

void EditorLayer::onRender(){

    //SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0x50, 0x50, 0x50, SDL_ALPHA_OPAQUE);
    
    //SDL_Rect rect {
        //50, 50, 200, 200
    //};
    //SDL_Rect rect2 {
        //700, 300, 200, 200
    //};

    //SDL_RenderFillRect(&GET_APPLICATION().getWindow().getRenderer(), &rect);
    //SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0x50, 0x50, 0x50, 50);
    //SDL_RenderFillRect(&GET_APPLICATION().getWindow().getRenderer(), &rect2);

    Variables::uiContainer->render();
    
}