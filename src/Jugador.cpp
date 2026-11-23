#include "Jugador.h"

#include <iostream>

const int VIDA_JUGADOR = 120;
const int ATAQUE_JUGADOR = 12;
const int NIVEL_INICIAL = 1;
const int BONO_VIDA_NIVEL = 20;
const int BONO_ATAQUE_NIVEL = 3;

// PILAR - HERENCIA: el constructor de la base se invoca en la lista de inicializacion.
Jugador::Jugador(const std::string& nombre)
    : Entidad(nombre, VIDA_JUGADOR, ATAQUE_JUGADOR),
      bonusAtaque(0),
      ubicacion(nullptr),
      nivel(NIVEL_INICIAL),
      experiencia(0) {
}

void Jugador::atacar(Entidad& objetivo) {
    int danio = this->ataque + this->bonusAtaque;
    std::cout << this->nombre << " ataca a " << objetivo.getNombre() << " con " << danio
              << " de dano." << std::endl;
    objetivo.recibirDanio(danio);
}

void Jugador::agregarObjeto(const Objeto& objeto) {
    this->inventario.push_back(objeto);
}

// Se trabaja con un indice y no con un puntero: al borrar o agregar elementos el vector
// mueve sus objetos de lugar en memoria y un puntero a ellos quedaria invalido.
bool Jugador::usarObjeto(int indice) {
    if (indice < 0 || indice >= static_cast<int>(this->inventario.size())) {
        return false;
    }

    const Objeto& objeto = this->inventario[indice];
    bool seUso = false;
    switch (objeto.getTipo()) {
        case TipoObjeto::PocionDeVida:
            seUso = this->beberPocion(objeto);
            break;
        case TipoObjeto::Arma:
            this->equiparArma(objeto);
            seUso = true;
            break;
    }

    if (seUso) {
        this->inventario.erase(this->inventario.begin() + indice);
    }
    return seUso;
}

bool Jugador::beberPocion(const Objeto& pocion) {
    if (this->vida == this->vidaMaxima) {
        std::cout << "Ya tienes la vida al maximo." << std::endl;
        return false;   // la pocion no se gasta
    }

    int vidaAntes = this->vida;
    this->curar(pocion.getValor());
    std::cout << this->nombre << " bebe " << pocion.getNombre() << " y recupera "
              << (this->vida - vidaAntes) << " puntos de vida (vida " << this->vida << "/"
              << this->vidaMaxima << ")." << std::endl;
    return true;
}

void Jugador::equiparArma(const Objeto& arma) {
    this->bonusAtaque = arma.getValor();   // reemplaza el bonus anterior, no se acumula
    std::cout << this->nombre << " equipa " << arma.getNombre() << ". Ataque total: "
              << (this->ataque + this->bonusAtaque) << "." << std::endl;
}

void Jugador::ganarExperiencia(int xp) {
    int xpGanada = (xp < 0) ? 0 : xp;
    if (xpGanada > 0) {
        std::cout << this->nombre << " gana " << xpGanada << " puntos de experiencia." << std::endl;
    }
    this->experiencia += xpGanada;
    // while y no if: con mucha XP de golpe se podrian subir varios niveles.
    while (this->experiencia >= XP_POR_NIVEL) {
        this->experiencia -= XP_POR_NIVEL;
        this->subirNivel();
    }
}

void Jugador::subirNivel() {
    this->nivel++;
    this->vidaMaxima += BONO_VIDA_NIVEL;
    this->ataque += BONO_ATAQUE_NIVEL;   // sube el ataque base; el bonus del arma va aparte
    this->curar(BONO_VIDA_NIVEL);        // curar respeta el tope de la nueva vida maxima
    std::cout << "!" << this->nombre << " sube al nivel " << this->nivel << "! Vida maxima: "
              << this->vidaMaxima << ", ataque base: " << this->ataque << "." << std::endl;
}

// Se devuelve una referencia const: Juego puede leer el inventario pero no cambiarlo.
const std::vector<Objeto>& Jugador::getInventario() const {
    return this->inventario;
}

int Jugador::getBonusAtaque() const {
    return this->bonusAtaque;
}

int Jugador::getNivel() const {
    return this->nivel;
}

int Jugador::getExperiencia() const {
    return this->experiencia;
}

void Jugador::setUbicacion(Habitacion* habitacion) {
    this->ubicacion = habitacion;
}

Habitacion* Jugador::getUbicacion() const {
    return this->ubicacion;
}
