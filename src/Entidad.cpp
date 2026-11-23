#include "Entidad.h"

#include <iostream>

// PILAR - ENCAPSULAMIENTO: el constructor impide nacer con vida o ataque negativos.
Entidad::Entidad(const std::string& nombre, int vida, int ataque)
    : nombre(nombre),
      vida((vida < 0) ? 0 : vida),
      vidaMaxima((vida < 0) ? 0 : vida),
      ataque((ataque < 0) ? 0 : ataque) {
}

Entidad::~Entidad() {
}

// PILAR - ENCAPSULAMIENTO: la vida solo cambia por aqui o por curar, y nunca baja de 0.
void Entidad::recibirDanio(int danio) {
    int danioReal = (danio < 0) ? 0 : danio;
    this->vida -= danioReal;
    this->vida = (this->vida < 0) ? 0 : this->vida;

    std::cout << this->nombre << " queda con " << this->vida << "/" << this->vidaMaxima
              << " de vida." << std::endl;
    if (!this->estaVivo()) {
        std::cout << this->nombre << " ha sido derrotado." << std::endl;
    }
}

void Entidad::curar(int cantidad) {
    int curacion = (cantidad < 0) ? 0 : cantidad;
    this->vida += curacion;
    this->vida = (this->vida > this->vidaMaxima) ? this->vidaMaxima : this->vida;
}

bool Entidad::estaVivo() const {
    return this->vida > 0;
}

std::string Entidad::getNombre() const {
    return this->nombre;
}

int Entidad::getVida() const {
    return this->vida;
}

int Entidad::getVidaMaxima() const {
    return this->vidaMaxima;
}

int Entidad::getAtaque() const {
    return this->ataque;
}
