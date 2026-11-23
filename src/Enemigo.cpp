#include "Enemigo.h"

Enemigo::Enemigo(const std::string& nombre, int vida, int ataque, int recompensaXp)
    : Entidad(nombre, vida, ataque),
      recompensaXp((recompensaXp < 0) ? 0 : recompensaXp) {
}

Enemigo::~Enemigo() {
}

int Enemigo::getRecompensaXp() const {
    return this->recompensaXp;
}
