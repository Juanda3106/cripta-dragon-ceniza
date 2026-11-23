#ifndef DRAGON_H
#define DRAGON_H

#include <string>

#include "Enemigo.h"

/**
 * @class Dragon
 * @brief Jefe intermedio: muerde y, cada tercer ataque, escupe su aliento de fuego.
 *
 * Relaciones: HERENCIA de Enemigo (y por lo tanto de Entidad).
 * Para sustentar: "que hace distinto el ataque del dragon": recuerda cuantas veces
 * ha atacado, por eso atacar no puede ser const.
 */
class Dragon : public Enemigo {
private:
    int ataquesRealizados;   // por este contador atacar no puede ser const

public:
    Dragon(const std::string& nombre);

    // PILAR - POLIMORFISMO: sobrescribe atacar con el comportamiento propio del dragon.
    void atacar(Entidad& objetivo) override;
    std::string getTipo() const override;
};

#endif //DRAGON_H
