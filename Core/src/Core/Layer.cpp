#include "Layer.h"
#include "App.h"

namespace Core{

    void Layer::queueTransition(std::unique_ptr<Layer> toLayer){
        for (auto& layer : Core::Application::Get().m_LayerStack){
            if (layer.get() == this){
                layer = std::move(toLayer);
                return;
            }
        }
    }

}