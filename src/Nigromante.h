#ifndef NIGROMANTE_H
#define NIGROMANTE_H

#include <string>

#include "Enemigo.h"

/**
 * @class Nigromante
 * @brief Jefe final: lanza rayos oscuros y, cada segundo ataque, drena la vida del objetivo.
 *
 * Relaciones: HERENCIA de Enemigo (y por lo tanto de Entidad). Igual que cualquier
 * enemigo, Juego lo posee (COMPOSICION) y la Sala del Trono lo registra (AGREGACION).
 * Para sustentar: "como se agrega un enemigo nuevo sin tocar el combate". Se escribio
 * esta clase y Juego::contraatacar no cambio ni una linea.
 */
class Nigromante : public Enemigo {
private:
    int ataquesRealizados;   // cuenta los ataques para saber cuando toca el drenaje

public:
    Nigromante(const std::string& nombre);

    // PILAR - POLIMORFISMO: su propia version de atacar (rayo oscuro o drenaje).
    void atacar(Entidad& objetivo) override;
    std::string getTipo() const override;
};

#endif //NIGROMANTE_H
