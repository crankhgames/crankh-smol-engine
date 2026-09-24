#pragma once
#include "UiElement.h"
#include "SDL2/SDL.h"

#include <functional>

namespace Core::UI {
    class Button : public UiElement{
    private:
        SDL_Color m_Color {};
        std::function<void()> m_ClickEvent{};

    public:
        Button(const Math::Vec2Int& position, const Math::Vec2Int& scale, SDL_Color color, std::function<void()> clickEvent):
            UiElement{position, scale}, m_Color{color}, m_ClickEvent {clickEvent}
        {};

        Button(const Math::Vec2Int& scale, SDL_Color color, std::function<void()> clickEvent):
            UiElement{{}, scale}, m_Color{color}, m_ClickEvent{clickEvent}
        {};

        bool onUserClick(const SDL_Event& event) override;

        void render() override;


    };
}