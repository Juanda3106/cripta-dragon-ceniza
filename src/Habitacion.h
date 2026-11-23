#ifndef HABITACION_H
#define HABITACION_H

#include <map>
#include <string>
#include <vector>

#include "Objeto.h"

// Forward declaration: solo se guardan punteros a Enemigo; el include va en el .cpp.
class Enemigo;

/**
 * @class Habitacion
 * @brief Lugar del mapa: tiene descripcion, salidas, enemigos y objetos en el suelo.
 *
 * Relaciones: ASOCIACION consigo misma (salidas a otras habitaciones), AGREGACION con
 * Enemigo (los registra pero no los libera), COMPOSICION con Objeto (objetos en el suelo,
 * por valor). Juego la posee (COMPOSICION).
 * Para sustentar: "diferencia entre agregacion y composicion", "por que Habitacion no
 * hace delete de los enemigos" y "por que std::map para las salidas".
 *
 * No tiene destructor propio porque no es duena de nada que este en el Heap.
 */
class Habitacion {
private:
    std::string nombre;
    std::string descripcion;
    std::map<std::string, Habitacion*> salidas;   // ASOCIACION (auto-asociacion): "norte" -> otra Habitacion
    std::vector<Enemigo*> enemigos;               // AGREGACION: apunta, NO libera
    std::vector<Objeto> objetos;                  // COMPOSICION por valor: objetos en el suelo

    void mostrarEnemigos() const;
    void mostrarObjetos() const;
    void mostrarSalidas() const;

public:
    Habitacion(const std::string& nombre, const std::string& descripcion);

    // Salida en un solo sentido: para ir y volver hay que conectar las dos habitaciones.
    void conectar(const std::string& direccion, Habitacion* destino);
    const std::map<std::string, Habitacion*>& getSalidas() const;

    void agregarEnemigo(Enemigo* enemigo);
    // Saca del vector a los derrotados; NO hace delete porque no es su duena.
    void retirarEnemigosDerrotados();
    bool hayEnemigosVivos() const;
    const std::vector<Enemigo*>& getEnemigos() const;

    void agregarObjeto(const Objeto& objeto);
    // Devuelve el objeto y lo quita del suelo. Quien llama garantiza un indice valido.
    Objeto retirarObjeto(int indice);
    const std::vector<Objeto>& getObjetos() const;

    std::string getNombre() const;
    void describir() const;
};

#endif //HABITACION_H
