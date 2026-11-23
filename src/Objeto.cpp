#include "Objeto.h"

Objeto::Objeto(const std::string& nombre, const std::string& descripcion, TipoObjeto tipo, int valor)
    : nombre(nombre),
      descripcion(descripcion),
      tipo(tipo),
      valor((valor < 0) ? 0 : valor) {
}

std::string Objeto::getNombre() const {
    return this->nombre;
}

std::string Objeto::getDescripcion() const {
    return this->descripcion;
}

TipoObjeto Objeto::getTipo() const {
    return this->tipo;
}

int Objeto::getValor() const {
    return this->valor;
}
