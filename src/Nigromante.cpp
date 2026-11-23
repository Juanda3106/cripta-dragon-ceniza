#include "Nigromante.h"

#include <iostream>

const int VIDA_NIGROMANTE = 90;
const int ATAQUE_NIGROMANTE = 10;
// El jefe final no da experiencia: al derrotarlo termina la partida.
const int RECOMPENSA_XP_NIGROMANTE = 0;
const int INTERVALO_DRENAJE = 2;

Nigromante::Nigromante(const std::string& nombre)
    : Enemigo(nombre, VIDA_NIGROMANTE, ATAQUE_NIGROMANTE, RECOMPENSA_XP_NIGROMANTE),
      ataquesRealizados(0) {
}

void Nigromante::atacar(Entidad& objetivo) {
    this->ataquesRealizados++;
    int danio = this->ataque;

    if (this->ataquesRealizados % INTERVALO_DRENAJE == 0) {
        // Drenaje: se cura lo mismo que hace de dano. curar respeta el tope de vida,
        // por eso se mide lo que de verdad recupero (puede ser menos que el dano).
        int vidaAntes = this->vida;
        this->curar(danio);
        int vidaRecuperada = this->vida - vidaAntes;
        std::cout << "El nigromante " << this->nombre << " drena la vida de "
                  << objetivo.getNombre() << " (" << danio << " de dano) y recupera "
                  << vidaRecuperada << " de vida." << std::endl;
    } else {
        std::cout << "El nigromante " << this->nombre << " lanza un rayo oscuro a "
                  << objetivo.getNombre() << " (" << danio << " de dano)." << std::endl;
    }
    objetivo.recibirDanio(danio);
}

std::string Nigromante::getTipo() const {
    return "Nigromante";
}
