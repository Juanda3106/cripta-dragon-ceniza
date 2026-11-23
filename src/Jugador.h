#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>

#include "Entidad.h"
#include "Objeto.h"

// Experiencia que hace falta para subir un nivel. Esta en el .h porque Juego la muestra.
const int XP_POR_NIVEL = 50;

// Forward declaration: Jugador solo guarda un puntero a Habitacion, no necesita conocerla.
class Habitacion;

/**
 * @class Jugador
 * @brief Personaje que controla la persona que juega: ataca, usa objetos y sube de nivel.
 *
 * Relaciones: HERENCIA de Entidad. COMPOSICION con Objeto (inventario por valor).
 * ASOCIACION con Habitacion (ubicacion: solo la conoce). Juego lo posee (COMPOSICION).
 * Para sustentar: "como se usa un objeto", "por que se usan indices del inventario" y
 * "como funciona la subida de nivel".
 */
class Jugador : public Entidad {
private:
    std::vector<Objeto> inventario;   // COMPOSICION: los objetos viven dentro del jugador
    int bonusAtaque;                  // lo da el arma equipada
    Habitacion* ubicacion;            // ASOCIACION: solo apunta, no la libera
    int nivel;                        // empieza en 1
    int experiencia;                  // XP acumulada dentro del nivel actual

    bool beberPocion(const Objeto& pocion);
    void equiparArma(const Objeto& arma);
    // PILAR - ENCAPSULAMIENTO: es privado; solo ganarExperiencia puede subir el nivel.
    void subirNivel();

public:
    Jugador(const std::string& nombre);

    // PILAR - POLIMORFISMO: version del jugador de atacar (ataque base + arma).
    void atacar(Entidad& objetivo) override;

    void agregarObjeto(const Objeto& objeto);
    // Devuelve true si el objeto se uso (y entonces sale del inventario).
    bool usarObjeto(int indice);

    void ganarExperiencia(int xp);

    const std::vector<Objeto>& getInventario() const;
    int getBonusAtaque() const;
    int getNivel() const;
    int getExperiencia() const;

    void setUbicacion(Habitacion* habitacion);
    Habitacion* getUbicacion() const;
};

#endif //JUGADOR_H
