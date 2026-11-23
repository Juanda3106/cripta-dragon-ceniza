cmake_minimum_required(VERSION 3.20)
project(AventuraTextual)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AventuraTextual
        src/main.cpp
        src/Entidad.h src/Entidad.cpp
        src/Jugador.h src/Jugador.cpp
        src/Enemigo.h src/Enemigo.cpp
        src/Orco.h src/Orco.cpp
        src/Dragon.h src/Dragon.cpp
        src/Nigromante.h src/Nigromante.cpp
        src/Objeto.h src/Objeto.cpp
        src/Habitacion.h src/Habitacion.cpp
        src/Juego.h src/Juego.cpp
        src/Entrada.h src/Entrada.cpp)

# Avisos del compilador activados: el proyecto debe compilar con cero avisos.
if(MSVC)
    target_compile_options(AventuraTextual PRIVATE /W4)
else()
    target_compile_options(AventuraTextual PRIVATE -Wall -Wextra -pedantic)
endif()
