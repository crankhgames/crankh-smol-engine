#include "Core/App.h"
#include <print>

#include "GameLayer.h"
#include "EditorLayer.h"


int main(){
    
    Core::ApplicationSpecification applicationSpecification{
        "Basic Application",

        Core::WindowSpecification{
            "Video Game",
            1920,
            1080,
            false
        }
    };

    Core::Application application {applicationSpecification};
    application.pushLayer<GameLayer>();
    application.pushLayer<EditorLayer>();
    application.run();


}
