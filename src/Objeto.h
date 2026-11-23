#ifndef OBJETO_H
#define OBJETO_H

#include <string>

// Tipos de objeto. Se usa un tipo y no una jerarquia de clases porque el inventario es
// std::vector<Objeto> por valor: una clase derivada guardada asi se "rebanaria" (slicing).
enum class TipoObjeto { PocionDeVida, Arma };

/**
 * @class Objeto
 * @brief Item que se puede recoger y usar: una pocion de vida o un arma.
 *
 * Relaciones: COMPOSICION. Forma parte del inventario de Jugador y del suelo de
 * Habitacion; vive dentro de ellos (por valor) y se destruye con ellos.
 * Para sustentar: "por que std::vector<Objeto> por valor y no punteros" y
 * "por que Objeto no tiene clases hijas".
 *
 * PILAR - ENCAPSULAMIENTO: atributos privados que solo se leen con getters.
 */
class Objeto {
private:
    std::string nombre;
    std::string descripcion;
    TipoObjeto tipo;
    int valor;        // PocionDeVida: vida que cura. Arma: bonus de ataque.

public:
    Objeto(const std::string& nombre, const std::string& descripcion, TipoObjeto tipo, int valor);

    std::string getNombre() const;
    std::string getDescripcion() const;
    TipoObjeto getTipo() const;
    int getValor() const;
};

#endif //OBJETO_H
