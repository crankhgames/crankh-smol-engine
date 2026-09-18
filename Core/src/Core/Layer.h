#pragma once

#include "SDL2/SDL.h"

#include <memory>

namespace Core{

    class Layer{
    private:
        void queueTransition(std::unique_ptr<Layer> toLayer);
    public: 
        virtual ~Layer() = default;

        virtual bool onEvent(const SDL_Event& event) = 0;

        virtual void onStart() = 0;
        virtual void onUpdate(double ts) = 0;
        virtual void onRender() = 0;
    };

}