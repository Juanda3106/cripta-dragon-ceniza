#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <string>

#include "Entidad.h"

/**
 * @class Enemigo
 * @brief Clase abstracta intermedia: todo lo que pelea contra el jugador.
 *
 * Relaciones: HERENCIA de Entidad; es la base de Orco, Dragon y Nigromante.
 * Juego lo posee (COMPOSICION) y Habitacion solo lo registra (AGREGACION).
 * Para sustentar: "para que sirve una clase abstracta intermedia" y "quien hace
 * delete de los enemigos".
 *
 * Existe para que Habitacion y Juego guarden punteros a "Enemigo" sin importar el
 * tipo real. Sigue siendo abstracta: hereda atacar sin implementarlo y agrega getTipo.
 */
class Enemigo : public Entidad {
private:
    int recompensaXp;   // experiencia que gana el jugador al derrotarlo

public:
    Enemigo(const std::string& nombre, int vida, int ataque, int recompensaXp);
    virtual ~Enemigo();

    // Devuelve "Orco", "Dragon" o "Nigromante": cada derivada dice lo que es.
    virtual std::string getTipo() const = 0;

    int getRecompensaXp() const;
};

#endif //ENEMIGO_H
