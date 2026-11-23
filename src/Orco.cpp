#include "Orco.h"

#include <iostream>

const int VIDA_ORCO = 36;
const int ATAQUE_ORCO = 7;
const int BONUS_FURIA = 3;
const int RECOMPENSA_XP_ORCO = 20;

// PILAR - HERENCIA: Orco -> Enemigo -> Entidad; cada constructor llama al de su base.
Orco::Orco(const std::string& nombre)
    : Enemigo(nombre, VIDA_ORCO, ATAQUE_ORCO, RECOMPENSA_XP_ORCO) {
}

// Furia: herido a menos de la mitad. Se multiplica por 2 para evitar dividir enteros.
bool Orco::estaEnFuria() const {
    return this->vida * 2 < this->vidaMaxima;
}

void Orco::atacar(Entidad& objetivo) {
    int danio = this->ataque;
    if (this->estaEnFuria()) {
        danio += BONUS_FURIA;
        std::cout << "El orco " << this->nombre << " entra en furia y golpea a "
                  << objetivo.getNombre() << " (" << danio << " de dano)." << std::endl;
    } else {
        std::cout << "El orco " << this->nombre << " golpea con su maza a "
                  << objetivo.getNombre() << " (" << danio << " de dano)." << std::endl;
    }
    objetivo.recibirDanio(danio);
}

std::string Orco::getTipo() const {
    return "Orco";
}
