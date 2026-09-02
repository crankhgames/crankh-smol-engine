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

    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>, StringHash, StringEqual> loadedTextures {};


    std::shared_ptr<SDL_Texture> loadTexture(const char* filename){
        std::shared_ptr<SDL_Texture> texture {
            IMG_LoadTexture(Core::Application::Get().getWindow()->getRenderer(), filename), SDL_DestroyTexture
        };

        std::cout << "Loading texture from " << filename << '\n';

        if (!texture){
            std::cerr << " Failure when creating texture !\n";
            return nullptr;
        }
        
        loadedTextures.insert({filename, texture});
        return texture;
    }

    std::shared_ptr<SDL_Texture> getTexture(std::string_view textureName){
        auto it = loadedTextures.find(textureName);
        return (it != loadedTextures.end() ? it->second : nullptr);
    }



    void loadAllTextures(std::string_view folderName){
        for (const auto& entry : std::filesystem::directory_iterator(folderName)){
            loadTexture(entry.path().c_str());
        }
    }


    void draw(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& destRect){
        SDL_RenderCopy(Application::Get().getWindow()->getRenderer(), texture, &srcRect, &destRect);
    }
}