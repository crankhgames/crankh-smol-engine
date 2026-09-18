#include "Renderer.h"

#include "Core/App.h"


#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <string_view>

namespace Core::Renderer{

    struct StringHash {
        using is_transparent = void;

        size_t operator()(std::string_view str) const noexcept {
            return std::hash<std::string_view>{}(str);
        }

        size_t operator()(const std::string& str) const noexcept {
            return std::hash<std::string_view>{}(str);
        }
    };

    struct StringEqual
    {
        using is_transparent = void;

        bool operator()(std::string_view a, std::string_view b) const noexcept {
            return a == b;
        }
    };

    static std::unordered_map<std::string, TexturePtr, StringHash, StringEqual> loadedTextures {};


    SDL_Texture* loadTexture(const char* filename){
        TexturePtr texture {
            IMG_LoadTexture(&Core::Application::Get().getWindow().getRenderer(), filename)
        };

        std::cout << "Loading texture from " << filename << '\n';

        if (!texture){
            std::cerr << " Failure when creating texture !\n";
            return nullptr;
        }
        
        std::string key {filename};
        loadedTextures.insert({key, std::move(texture)});
        return loadedTextures[key].get();
    }

    SDL_Texture* getTexture(std::string_view textureName){
        auto it = loadedTextures.find(textureName);
        return (it != loadedTextures.end() ? it->second.get() : nullptr);
    }



    void loadAllTextures(std::string_view folderName){
        for (const auto& entry : std::filesystem::directory_iterator(folderName)){
            loadTexture(entry.path().c_str());
        }
    }


    void draw(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& destRect){
        SDL_RenderCopy(&Application::Get().getWindow().getRenderer(), texture, &srcRect, &destRect);
    }

    void draw(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& destRect, bool flipX, bool flipY){
        SDL_RenderCopyEx(&Application::Get().getWindow().getRenderer(), texture, &srcRect, &destRect, 0.0, NULL, 
            static_cast<SDL_RendererFlip>((flipX ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE) | (flipY ? SDL_RendererFlip::SDL_FLIP_VERTICAL : SDL_RendererFlip::SDL_FLIP_NONE))
        );
    }
}