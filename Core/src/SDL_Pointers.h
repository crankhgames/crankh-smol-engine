#pragma once

#include "SDL2/SDL.h"
#include <memory>
#include "SDL2/SDL_ttf.h"

struct SDL_Deleter {

    void operator()(SDL_Window* window) const {SDL_DestroyWindow(window);}
    void operator()(SDL_Renderer* renderer) const {SDL_DestroyRenderer(renderer);}
    void operator()(SDL_Texture* texture) const {SDL_DestroyTexture(texture);}
    void operator()(SDL_Surface* surface) const {SDL_FreeSurface(surface);}
    void operator()(TTF_Font* font) const {TTF_CloseFont(font);}

};

using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
using SurfacePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
using FontPtr = std::unique_ptr<TTF_Font, SDL_Deleter>;
