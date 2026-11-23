#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <vector>

#include "Objeto.h"

// Forward declarations: Juego solo guarda punteros; los includes van en el .cpp.
class Enemigo;
class Habitacion;
class Jugador;

/**
 * @class Juego
 * @brief Orquesta la partida (mundo, menus y combate) y es el unico dueno de la memoria dinamica.
 *
 * Relaciones: COMPOSICION con Jugador, Habitacion y Enemigo (los crea con new y los
 * libera con delete). ASOCIACION con Habitacion (habitacionFinal: solo apunta).
 * Para sustentar: "quien hace new y delete de cada cosa" y "en que linea esta el
 * polimorfismo" (Juego::contraatacar).
 */
class Juego {
private:
    Jugador* jugador;                       // COMPOSICION: puntero propio
    std::vector<Habitacion*> habitaciones;  // COMPOSICION: punteros propios
    std::vector<Enemigo*> enemigos;         // COMPOSICION: Juego es el dueno de los enemigos
    Habitacion* habitacionFinal;            // ASOCIACION: solo apunta a la Sala del Trono

    // Preparacion de la partida
    void mostrarIntroduccion() const;
    std::string pedirNombre() const;
    void construirMundo();
    void crearHabitaciones();
    void crearHabitacion(const std::string& nombre, const std::string& descripcion);
    void conectarHabitaciones();
    void conectarIdaYVuelta(int origen, const std::string& ida, int destino, const std::string& vuelta);
    void colocarEnemigos();
    void colocarEnemigo(int indiceHabitacion, Enemigo* enemigo);
    void colocarObjetos();

    // Exploracion
    void menuExploracion();
    void mostrarMenuExploracion() const;
    bool ejecutarOpcionExploracion(int opcion);   // false si la partida termina
    bool moverse();                               // false si la partida termina
    Habitacion* elegirDestino() const;            // nullptr si se cancela
    void recogerObjeto();
    bool gestionarInventario();                   // true si se uso un objeto
    void mostrarEstadoJugador() const;
    void mostrarObjetosNumerados(const std::vector<Objeto>& objetos) const;
    bool comprobarVictoria() const;

    // Combate
    bool combatir();                              // true si el jugador gano el combate
    bool atacarEnemigo();                         // true si el ataque se hizo (gasta el turno)
    void contraatacar();
    Enemigo* elegirObjetivo() const;              // nullptr si se agoto la entrada
    void mostrarEnemigosNumerados() const;
    void mostrarMenuCombate() const;

public:
    Juego();
    ~Juego();

    void iniciar();
};

#endif //JUEGO_H
