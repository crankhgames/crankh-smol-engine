#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <memory>

namespace Core::Renderer{


    std::shared_ptr<SDL_Texture> getTexture(std::string_view textureName);
    std::shared_ptr<SDL_Texture> loadTexture(const char* filename);


    void loadAllTextures(std::string_view folderName);


    void draw(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest);
    void draw(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest, bool flipX, bool flipY);

}