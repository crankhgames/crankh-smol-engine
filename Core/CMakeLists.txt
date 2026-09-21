add_library(Core)


target_sources(Core
PRIVATE
    src/Core/App.cpp
    src/Core/Window.cpp
    src/Core/Layer.cpp
    src/Math/Math.cpp
    src/Input/Input.cpp
    src/Renderer/Renderer.cpp
    src/ECS/Scene.cpp
    src/Physics/CollisionDetection.cpp
    src/UI/Text.cpp
    src/UI/UIContainer.cpp

PUBLIC
    FILE_SET HEADERS
    FILES
        src/Core/App.h
        src/Core/Window.h
        src/Core/Layer.h
        src/Random/Random.h
        src/Math/Math.h
        src/Input/Input.h
        src/Renderer/Renderer.h
        src/ECS/Components.h
        src/ECS/Scene.h
        src/ECS/Entity.h
        src/Animation/Interpolation.h
        src/Animation/Animation.h
        src/Physics/CollisionDetection.h
        src/SDL_Pointers.h
        src/UI/Text.h
        src/UI/UIContainer.h
        src/UI/UIElement.h
)

target_include_directories(Core
PUBLIC
    src
)