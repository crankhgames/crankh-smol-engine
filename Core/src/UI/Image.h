#pragma once

#include "UiElement.h"
#include "SDL_Pointers.h"
#include "Renderer/Renderer.h"

namespace Core::UI {
    class Image : public UiElement {
    private:
        TexturePtr m_ImageTexture{};

    public:
        Image(const Math::Vec2& position, const Math::Vec2& scale, std::string_view filename, std::string id=""):
            UiElement{position, scale, id}, m_ImageTexture{Renderer::loadTexture(filename.data())}
        {};

        Image(const Math::Vec2& scale, std::string_view filename, std::string id=""):
            UiElement{{}, scale, id}, m_ImageTexture{Renderer::loadTexture(filename.data())}
        {};

        Image(double scaleFactor, std::string_view filename, std::string id=""):
            UiElement{{}, {}, id}, m_ImageTexture{Renderer::loadTexture(filename.data())}
        {
            int width{};
            int height{};

            SDL_QueryTexture(m_ImageTexture.get(), NULL, NULL, &width, &height);

            m_Scale.set(static_cast<int>(width*scaleFactor), static_cast<int>(height*scaleFactor));
        }

        void render() override;

    };
}