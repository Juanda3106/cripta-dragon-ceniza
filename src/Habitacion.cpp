#include "Habitacion.h"

#include <iostream>

#include "Enemigo.h"

Habitacion::Habitacion(const std::string& nombre, const std::string& descripcion)
    : nombre(nombre),
      descripcion(descripcion) {
}

// ASOCIACION: solo se guarda la direccion de otra habitacion que ya existe.
void Habitacion::conectar(const std::string& direccion, Habitacion* destino) {
    this->salidas[direccion] = destino;
}

const std::map<std::string, Habitacion*>& Habitacion::getSalidas() const {
    return this->salidas;
}

void Habitacion::agregarEnemigo(Enemigo* enemigo) {
    this->enemigos.push_back(enemigo);
}

void Habitacion::retirarEnemigosDerrotados() {
    // AGREGACION: los derrotados solo dejan de estar registrados aqui.
    // Siguen existiendo hasta que Juego, su dueno, los libere.
    std::vector<Enemigo*> vivos;
    for (Enemigo* enemigo : this->enemigos) {
        if (enemigo->estaVivo()) {
            vivos.push_back(enemigo);
        }
    }
    this->enemigos = vivos;
}

bool Habitacion::hayEnemigosVivos() const {
    for (Enemigo* enemigo : this->enemigos) {
        if (enemigo->estaVivo()) {
            return true;
        }
    }
    return false;
}

const std::vector<Enemigo*>& Habitacion::getEnemigos() const {
    return this->enemigos;
}

void Habitacion::agregarObjeto(const Objeto& objeto) {
    this->objetos.push_back(objeto);
}

Objeto Habitacion::retirarObjeto(int indice) {
    Objeto objeto = this->objetos[indice];
    this->objetos.erase(this->objetos.begin() + indice);
    return objeto;
}

const std::vector<Objeto>& Habitacion::getObjetos() const {
    return this->objetos;
}

std::string Habitacion::getNombre() const {
    return this->nombre;
}

void Habitacion::describir() const {
    std::cout << "=== " << this->nombre << " ===" << std::endl;
    std::cout << this->descripcion << std::endl;
    this->mostrarEnemigos();
    this->mostrarObjetos();
    this->mostrarSalidas();
}

void Habitacion::mostrarEnemigos() const {
    if (this->enemigos.empty()) {
        std::cout << "Enemigos: ninguno." << std::endl;
        return;
    }
    std::cout << "Enemigos: ";
    bool primero = true;
    for (Enemigo* enemigo : this->enemigos) {
        std::cout << (primero ? "" : ", ") << enemigo->getNombre() << " (" << enemigo->getTipo()
                  << ", vida " << enemigo->getVida() << "/" << enemigo->getVidaMaxima() << ")";
        primero = false;
    }
    std::cout << std::endl;
}

void Habitacion::mostrarObjetos() const {
    if (this->objetos.empty()) {
        std::cout << "Objetos en el suelo: ninguno." << std::endl;
        return;
    }
    std::cout << "Objetos en el suelo: ";
    bool primero = true;
    for (const Objeto& objeto : this->objetos) {
        std::cout << (primero ? "" : ", ") << objeto.getNombre();
        primero = false;
    }
    std::cout << std::endl;
}

void Habitacion::mostrarSalidas() const {
    std::cout << "Salidas: ";
    bool primero = true;
    // std::map recorre sus claves en orden alfabetico: la salida siempre es la misma.
    for (const std::pair<const std::string, Habitacion*>& salida : this->salidas) {
        std::cout << (primero ? "" : ", ") << salida.first;
        primero = false;
    }
    std::cout << std::endl;
}
