#ifndef ORCO_H
#define ORCO_H

#include <string>

#include "Enemigo.h"

/**
 * @class Orco
 * @brief Enemigo que golpea con su maza y entra en furia si esta muy herido.
 *
 * Relaciones: HERENCIA de Enemigo (y por lo tanto de Entidad).
 * Para sustentar: "que hace distinto el ataque del orco": depende de su propia vida.
 */
class Orco : public Enemigo {
private:
    bool estaEnFuria() const;

public:
    Orco(const std::string& nombre);

    // PILAR - POLIMORFISMO: sobrescribe atacar con el comportamiento propio del orco.
    void atacar(Entidad& objetivo) override;
    std::string getTipo() const override;
};

#endif //ORCO_H
