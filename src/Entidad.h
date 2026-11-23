#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <string>

/**
 * @class Entidad
 * @brief Clase base abstracta de todo lo que puede pelear: tiene nombre, vida y ataque.
 *
 * Relaciones: HERENCIA. Es la base de Jugador y de Enemigo.
 * Para sustentar: "por que Entidad es abstracta", "que es un metodo virtual puro" y
 * "por que el destructor es virtual".
 *
 * PILAR - ABSTRACCION: define QUE puede hacer algo que pelea (atacar), pero no COMO.
 * No existe una "entidad generica": no se pueden crear objetos de esta clase.
 * Los atributos son protected para que las clases derivadas puedan usarlos.
 */
class Entidad {
protected:
    std::string nombre;
    int vida;          // vida actual (nunca < 0 ni > vidaMaxima)
    int vidaMaxima;
    int ataque;        // ataque base

public:
    Entidad(const std::string& nombre, int vida, int ataque);

    // Destructor virtual: al hacer delete desde un puntero a la base se llama
    // tambien al destructor del tipo real (Orco, Dragon, Jugador...).
    virtual ~Entidad();

    // Metodo virtual puro (= 0): cada derivada esta obligada a implementarlo.
    // No es const porque Dragon y Nigromante cambian su contador al atacar.
    virtual void atacar(Entidad& objetivo) = 0;

    void recibirDanio(int danio);
    void curar(int cantidad);
    bool estaVivo() const;

    std::string getNombre() const;
    int getVida() const;
    int getVidaMaxima() const;
    int getAtaque() const;
};

#endif //ENTIDAD_H
