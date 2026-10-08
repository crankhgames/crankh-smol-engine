#pragma once

#include "SDL2/SDL_ttf.h"
#include "SDL_Pointers.h"
#include "UiElement.h"
#include "Core/App.h"

#include <memory>
#include <string>
#include <string_view>
#include <print>
#include <unordered_map>

namespace Core::UI{

    static std::unordered_map<char, TexturePtr> characterTextures {};

    void loadCharacterTexture(TTF_Font& font, char c);
    SDL_Texture& getCharacterTexture(char c);

    class InputField : public UiElement {
    private:
        FontPtr m_Font {};
        SDL_Color m_Color {};
        std::string m_Content {};

        bool m_isSelected {false};

    public:
        InputField(Math::Vec2Int position, Math::Vec2Int scale, std::string_view content, int ptSize, std::string_view filename, SDL_Color color, std::string id="") : 
            UiElement{position, scale, id},  m_Font {TTF_OpenFont(filename.data(), ptSize)}, m_Color{color}, m_Content{content}
        {
            //SurfacePtr textSurface {
                //TTF_RenderText_Solid(m_Font.get(), m_Content.c_str(), m_Color)
            //};
            //m_FontTexture.reset({SDL_CreateTextureFromSurface(&GET_APPLICATION().getWindow().getRenderer(), textSurface.get())});

            for (auto c : content){
                loadCharacterTexture(*m_Font.get(), c);
            }
        };

        InputField(std::string_view content, int ptSize, std::string_view filename, SDL_Color color, std::string id=""):
            InputField{Math::Vec2Int{}, Math::Vec2Int{}, content, ptSize, filename, color, id}
        {
            //int textureWidth {};
            //int textureHeight {};
            //SDL_QueryTexture(m_FontTexture.get(), NULL, NULL, &textureWidth, &textureHeight);

            //m_Scale.set(textureWidth, textureHeight);
        }

        ~InputField() {};

        bool onUserClick(const SDL_Event& event) override;
        bool onUserKeyboardPress(const SDL_Event& event) override;
        bool onUserInputText(const SDL_Event& event) override;

        void render() override;

        void setColor(SDL_Color color){
            m_Color = color;
        }
        
        void setColor(int r, int g, int b, int a = SDL_ALPHA_OPAQUE){
            m_Color.r = r;
            m_Color.g = g;
            m_Color.b = b;
            m_Color.a = a;
        }

        std::string_view getContent() {return m_Content;}

        void addCharacter(std::string_view chars);
        void deleteCharacter();
    };
}