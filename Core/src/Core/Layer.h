#pragma once

#include "SDL2/SDL.h"

#include <memory>

namespace Core{

    class Layer{
    private:
        void queueTransition(std::unique_ptr<Layer> toLayer);
    public: 
        virtual ~Layer() = default;

        virtual void onEvent(const SDL_Event& event) {};

        virtual void onStart() {};
        virtual void onUpdate(double ts) {};
        virtual void onRender() {};
    };

}