cmake_minimum_required(VERSION 3.10)
project(hormiga_game)

set(CMAKE_CXX_STANDARD 14)

# Buscar SFML 2.5
find_package(SFML 2.5.1 COMPONENTS graphics window system)

if(NOT SFML_FOUND)
    # Descargar SFML 2.5.1 si no está instalado
    include(FetchContent)
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.5.1
    )
    # Configurar opciones de compilación de SFML
    set(SFML_BUILD_GRAPHICS ON CACHE BOOL "Build SFML graphics module" FORCE)
    set(SFML_BUILD_WINDOW ON CACHE BOOL "Build SFML window module" FORCE)
    set(SFML_BUILD_SYSTEM ON CACHE BOOL "Build SFML system module" FORCE)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "Disable audio module" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "Disable network module" FORCE)

    FetchContent_MakeAvailable(SFML)
endif()

add_executable(hormiga_game
        main.cpp
        AnimatedSprite.cpp
        Player.cpp
)

target_link_libraries(hormiga_game
        sfml-graphics
        sfml-window
        sfml-system
)