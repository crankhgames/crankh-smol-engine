#include "InputField.h"
#include "Renderer/Renderer.h"


namespace Core::UI {

    void loadCharacterTexture(TTF_Font& font, char c){
        std::string charString {c};
        SurfacePtr textSurface {
            TTF_RenderText_Solid(&font, charString.c_str(), SDL_Color{0, 0, 0, 255})
        };

        characterTextures.insert({c, TexturePtr(SDL_CreateTextureFromSurface(&GET_APPLICATION().getWindow().getRenderer(), textSurface.get()))});
    }

    SDL_Texture& getCharacterTexture(char c){
        return *characterTextures[c].get();
    }

    void InputField::render()
    {
        SDL_Rect destRect{m_GlobalPosition.getX(), m_GlobalPosition.getY(), m_Scale.getX(), m_Scale.getY()};
        SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0, 0, 0, 255);
        SDL_RenderDrawRect(&GET_APPLICATION().getWindow().getRenderer(), &destRect);

        for (char c : m_Content){
            auto charTexture {&getCharacterTexture(c)};

            SDL_QueryTexture(charTexture, NULL, NULL, &destRect.w, &destRect.h);
            Renderer::draw(charTexture, destRect);


            destRect.x += destRect.w+1;
        }

        UiElement::render();
    }

    void InputField::addCharacter(std::string_view chars){
        m_Content += chars;

        for (char c : chars){
            if (characterTextures.find(c) == characterTextures.end()){
                loadCharacterTexture(*m_Font.get(), c);
            }
        }

    }

    void InputField::deleteCharacter(){
        if (m_Content.size() > 0){
            m_Content.pop_back();
        }
    }

    bool InputField::onUserClick(const SDL_Event& event){
        if ((event.button.x < m_Position.getX() + m_Scale.getX() && event.button.x > m_Position.getX())
            && (event.button.y < m_Position.getY() + m_Scale.getY() && event.button.y > m_Position.getY())){

            m_isSelected = true;
            std::println("Selected...");
            return true;
        }

        m_isSelected = false;
        std::println("Unselected...");
        return false;
    }

    bool InputField::onUserKeyboardPress(const SDL_Event& event){
        if (m_isSelected){
            if (event.key.keysym.sym == SDLK_BACKSPACE){
                deleteCharacter();
                return true;
            }
        }

        return false;
    }

    bool InputField::onUserInputText(const SDL_Event& event){
        if (m_isSelected) {
            addCharacter(event.text.text);
            std::println("Input content: {}", m_Content);
            return true;
        }

        return false;
    }
}