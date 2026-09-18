add_executable(App)



target_sources(App
PRIVATE
    src/main.cpp
    src/GameLayer.cpp
    src/GameLayer.h
    src/EditorLayer.h
    src/EditorLayer.cpp
)

target_link_libraries(App
PRIVATE
    Core
)