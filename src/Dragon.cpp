#include "Dragon.h"

#include <iostream>

const int VIDA_DRAGON = 80;
const int ATAQUE_DRAGON = 12;
const int BONUS_ALIENTO = 8;
const int FRECUENCIA_ALIENTO = 3;
const int RECOMPENSA_XP_DRAGON = 60;

Dragon::Dragon(const std::string& nombre)
    : Enemigo(nombre, VIDA_DRAGON, ATAQUE_DRAGON, RECOMPENSA_XP_DRAGON),
      ataquesRealizados(0) {
}

void Dragon::atacar(Entidad& objetivo) {
    this->ataquesRealizados++;

    int danio = this->ataque;
    if (this->ataquesRealizados % FRECUENCIA_ALIENTO == 0) {
        danio += BONUS_ALIENTO;
        std::cout << "!El dragon " << this->nombre << " escupe su aliento de fuego sobre "
                  << objetivo.getNombre() << " (" << danio << " de dano)!" << std::endl;
    } else {
        std::cout << "El dragon " << this->nombre << " muerde a " << objetivo.getNombre()
                  << " (" << danio << " de dano)." << std::endl;
    }
    objetivo.recibirDanio(danio);
}

std::string Dragon::getTipo() const {
    return "Dragon";
}
